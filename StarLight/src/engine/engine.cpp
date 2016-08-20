#include "engine.h"

NetFight *m_network;

Uint32 thrProcess(Uint32 interval, void *param) {
    double timeStep = interval/1000.0;
    if( m_network)
        m_network->Process();
    return interval;
}

Engine::Engine() {
    m_ip = "localhost";
    m_graphic = new Graphic( 1024, 800);
    m_framenrate = new Framenrate();
    m_framenrate->Set( ENGINE_STARTFRAMENRATE);
    m_entity = new EntityList( m_graphic);
    m_control = new Control( m_graphic);
    // Start einstelungen
    m_quit = false;
    m_server = true;

    // move Camera
    m_move_camera = false;
}

Engine::~Engine() {
    SDL_RemoveTimer( m_network_thrend);
    delete m_entity;
    delete m_framenrate;
    delete m_graphic;
}

void Engine::ControlMove() {
    if( m_input.Map.Place && !m_input.MapOld.Place) {
        m_mouse_x = m_input.Map.MousePos.m_x + m_graphic->GetCamera()->GetX();
        m_mouse_y = m_input.Map.MousePos.m_y + m_graphic->GetCamera()->GetY();
        m_move_camera = true;
        m_input.grabMouse( true, m_graphic->GetWindow(), m_graphic->GetWidth()/2, m_graphic->GetHeight()/2);
    }

    if( m_move_camera) {
        float t_factor = 800;
        m_graphic->GetCamera()->move( -m_input.Map.MousePos.c_x*t_factor, -m_input.Map.MousePos.c_y*t_factor);
    }

    if( !m_input.Map.Place && m_input.MapOld.Place) {
        m_input.grabMouse( false, m_graphic->GetWindow(), m_mouse_x, m_mouse_y);
        m_move_camera = false;
    }
}

void Engine::Process() {

    m_entity->createEntity( feed, 300, 300, red);
    m_entity->createEntity( collector, 100, 200, blue);
    m_entity->createEntity( mothercell, 200, 100, yellow);
    m_entity->createEntity( decomposers, 200, 200, green);

    // Network
    bool t_network_start;
    if( true) {
        printf( "NetFight: Network wird gestartet\n");
        m_network = new NetFight(); // Netzwerk erstllen
        if( m_server)
            t_network_start = m_network->StartServer();
        else
            t_network_start = m_network->Connect( m_ip);
    }
    m_network_thrend = SDL_AddTimer( 10, thrProcess, NULL); // SDL Create Thrend
    if (NULL == m_network_thrend) {
        printf("SDL_CreateThread failed: %s\n", SDL_GetError());
    }
    if( t_network_start)
        m_quit = true;

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
        m_entity->drawAll( m_graphic);
        // Rendern
        m_graphic->GetDisplay()->SwapBuffers();
        m_graphic->GetDisplay()->Clear( 0, 0, 0, 0 );
        // Framenrate anwenden und begrenzen
        m_framenrate->EndCount();
        m_framenrate->CalcDelay();
    }
}
