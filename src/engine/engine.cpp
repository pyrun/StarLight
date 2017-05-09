#include "engine.h"

NetFight *m_network;

Uint32 thrNetwork(Uint32 interval, void *param) {
    double timeStep = interval/1000.0;
    if( m_network)
        m_network->Process();
    return interval;
}

Uint32 thrProcess(Uint32 interval, void *param) {
    EntityList *m_entity = (EntityList*)param;

    if( m_entity) {
        m_entity->m_bussy = true;
        m_entity->process();
        m_entity->m_bussy = false;
    }



    return interval;
}

Engine::Engine() {
    m_ip = "localhost";
    m_graphic = new Graphic( 1024, 800);
    m_framenrate = new Framenrate();
    m_framenrate->Set( ENGINE_STARTFRAMENRATE);
    m_entity = new EntityList( m_graphic);
    m_control = new Control( m_graphic);
    m_front = new Front( m_graphic);
    // Start einstelungen
    m_quit = false;
    m_server = true;

    // Network
    if( false) {
        printf( "NetFight: Network wird gestartet\n");
        m_network = new NetFight(); // Netzwerk erstllen
        if( m_server)
            m_network->StartServer();
        else
            m_network->Connect( m_ip);
    }
    m_network_thrend = SDL_AddTimer( 10, thrNetwork, NULL); // SDL Create Thrend
    if (NULL == m_network_thrend) {
        printf("SDL_CreateThread failed: %s", SDL_GetError());
    }

    // Entity
    m_entity_thrend = SDL_AddTimer( 10, thrProcess, m_entity); // SDL Create Thrend
    if (NULL == m_entity_thrend) {
        printf("SDL_CreateThread failed: %s", SDL_GetError());
    }

}

Engine::~Engine() {
    SDL_RemoveTimer( m_entity_thrend);
    SDL_RemoveTimer( m_network_thrend);
    delete m_entity;
    delete m_framenrate;
    delete m_graphic;
}

void Engine::ControlMove() {
    bool t_mouse =  m_input.Map.Place;
    bool t_mouse_old =  m_input.MapOld.Place;

    if( t_mouse && !t_mouse_old) {
        m_mouse_x = m_input.Map.MousePos.m_x + m_graphic->GetCamera()->GetX();
        m_mouse_y = m_input.Map.MousePos.m_y + m_graphic->GetCamera()->GetY();
        m_move_camera = true;
        m_input.grabMouse( true, m_graphic->GetWindow(), m_graphic->GetWidth()/2, m_graphic->GetHeight()/2);
    }

    if( m_move_camera) {
        float t_factor = 800;
        m_graphic->GetCamera()->move( (m_input.Map.MousePos.c_x*t_factor), (m_input.Map.MousePos.c_y*t_factor));
    }

    if( !t_mouse && t_mouse_old) {
        m_input.grabMouse( false, m_graphic->GetWindow(), m_mouse_x, m_mouse_y);
        m_move_camera = false;
    }
}

void Engine::Process() {

    Entity* t_ent = m_entity->createEntity( mothercell, 300, 300, red);
    //m_entity->createTeamEntity( collector, 350, 350, t_ent);
    //m_entity->createTeamEntity( collector, 300, 350, t_ent);

    t_ent = m_entity->createEntity( mothercell, 400, 300, red);


    m_entity->createEntity( mothercell, 100, 200, blue);

    m_entity->createEntity( mothercell, 200, 100, yellow);

    m_entity->createEntity( cell, 325, 300, red);
    m_entity->createEntity( cell, 300, 325, red);
    m_entity->createEntity( cell, 325, 325, red);

    m_entity->deleteEntity( t_ent, m_entity->getTree());

    // Hauptschleife
    while( !m_quit ) {
        // Framenrate startet zum Zählen
        m_framenrate->StartCount();
        // Input erfassen und darauf reagieren
        m_input.Reset(); // davor reseten
        m_quit = !m_input.Handle( m_graphic->GetWidth(), m_graphic->GetHeight(), m_graphic->GetWindow(), m_graphic->GetCamera()->GetX(), m_graphic->GetCamera()->GetY());
        m_control->Handle( &m_input, m_entity);
        // Camera move
        float d_x = 0, d_y = 0;
        if( m_input.Map.Up)
            d_y -= 1;
        if( m_input.Map.Down)
            d_y += 1;
        if( m_input.Map.Right)
            d_x += 1;
        if( m_input.Map.Left)
            d_x -= 1;
        ControlMove();
        m_graphic->GetCamera()->move( -d_x, -d_y);
        // Render entity
        m_control->Draw( m_graphic);
        //if( m_entity->m_bussy == false )
            //SDL_Delay( 1);
        m_entity->drawAll( m_graphic, m_front);
        // Rendern
        m_graphic->GetDisplay()->SwapBuffers();
        m_graphic->GetDisplay()->Clear( 0, 0, 0, 0 );
        // Framenrate anwenden und begrenzen
        m_framenrate->EndCount();
        m_framenrate->CalcDelay();
    }
}
