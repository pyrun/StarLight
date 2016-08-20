#include "entity.h"

EntityList::EntityList( Graphic* graphic) {
    m_entity = NULL;
    // Erstelle Cell liste ( Grafikschnitstelle und zwischenspeicher)
    if( s_cell == NULL) {
    s_cell = new Cell( cell, graphic);
    s_mothercell = new Cell( mothercell, graphic);
    s_collector = new Cell( collector, graphic);
    s_decomposers = new Cell( decomposers, graphic);
    s_feed = new Cell( feed, graphic);
    }
    int rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    // Makierkreiß erstellen
    SDL_Surface* surface_circle = SDL_CreateRGBSurface( 0, ENTITY_MARK_CRICLE_SIZE, ENTITY_MARK_CRICLE_SIZE, 32, rmask, gmask, bmask, amask);
    //graphic->set_pixel( surface_circle, 0, 0, 0x66FF0000 );
    graphic->fill_circle( surface_circle, ENTITY_MARK_CRICLE_SIZE/2, ENTITY_MARK_CRICLE_SIZE/2, ENTITY_MARK_CRICLE_SIZE/2-1, 0xAAFFFF00);
    m_circle = SDL_CreateTextureFromSurface( graphic->GetDisplay()->GetRenderer(), surface_circle);
    SDL_FreeSurface( surface_circle);
}
EntityList::~EntityList() {
    deleteAll(m_entity);
    if( s_cell != NULL) {
        delete s_cell;
        delete s_mothercell;
        delete s_collector;
        delete s_decomposers;
        delete s_feed;
    }
    SDL_DestroyTexture( m_circle);
}
void EntityList::createEntity( CellName id, float pos_x, float pos_y, Entity_team team) {
    Entity *t_entity;
    Entity* attach;
    t_entity = new Entity( id, pos_x, pos_y, team);
    // erstellt
    printf( "CreateEntity: Erstellt %d %d\n", (int)t_entity->GetX(), (int)t_entity->GetY());
    // Baumende suchen
    if( m_entity == NULL)
        m_entity = t_entity;
    else {
        attach = m_entity;
        while( attach->m_next != NULL)
            attach = attach->m_next;
        attach->m_next = t_entity;
    }
}
void EntityList::editData( int index, int wert, int wert2, Entity *entity) {
   switch( index ) {
       case 0: entity->SetMark( (bool)wert); break;
   }
}
void EntityList::editRectData( int x1, int y1, int x2, int y2, int index, int wert, int wert2, Entity *entity) {
    if( entity == NULL)
        return;
    if( entity->m_next != NULL)
        editRectData( x1, y1, x2, y2, index, wert, wert2, entity->m_next);
    // falls im rahmen
    float pos_x = entity->GetX();
    float pos_y = entity->GetY();
    if( x1 < pos_x && y1 < pos_y && x1+x2 > pos_x && y1+y2 > pos_y)
        editData( index, wert, wert2, entity);
}
void EntityList::editifdata( int index, int wert, int wert2, int setindex, int setwert, int setwert2, Entity* entity) {
    if( entity == NULL)
        return;
    if( entity->m_next != NULL)
        editifdata( index, wert, wert2, setindex, setwert, setwert2, entity);
    // switch
    switch( index ) {
        case 0:  break;
    }
    // Wert
    editData( setindex, setwert, setwert2, entity);
}
void EntityList::earseAll( int index, int wert, int wert2, Entity* entity) {
    if( entity == NULL)
        return;
    if( entity->m_next != NULL)
        earseAll( index, wert, wert2, entity->m_next);
    editData( index, wert, wert2, entity);
}
void EntityList::drawAll( Graphic* graphic) {
    drawEntity( m_entity, graphic);
}
void EntityList::drawEntity( Entity* entity, Graphic* graphic) {
    // Falls nicht addresiert nichts machen
    if( entity == NULL)
        return;
    if( entity->m_next != NULL)
        drawEntity( entity->m_next, graphic);
    Cell* tmp_cell;
    switch( entity->GetCellName() ) {
        case mothercell: tmp_cell = s_mothercell; break;
        case collector: tmp_cell = s_collector; break;
        case decomposers: tmp_cell = s_decomposers; break;
        case feed: tmp_cell = s_feed; break;
        default: tmp_cell = s_cell; break;
    }
    int color = GetTeamColor( entity->GetTeam());
    SDL_Texture* circle = m_circle;
    if( entity->IsMarked() == false)
        circle = NULL;

    tmp_cell->Draw( entity->GetX(), entity->GetY(), color, graphic, circle, ENTITY_MARK_CRICLE_SIZE);
}

void EntityList::deleteAll( Entity* entity) {
    // Falls nicht addresiert nichts machen
    if( entity == NULL)
        return;
    // bevor löschen erst sein kind löschen
    if( entity->m_next != NULL)
        deleteAll( entity->m_next);
    printf("DeleteAll: Loschen des Entity %d %d\n", (int)entity->GetX(), (int)entity->GetY());
    // selbst löschen und wert reseten für zunküftige bearbeitung
    delete entity;
    entity = NULL;
}

int GetTeamColor( Entity_team team) {
    switch( team) {
        case red: return 0xff0000ff;
        case blue: return 0x00ff00ff;
        case yellow: return 0x0000ffff;
        case green: return 0xffff00ff;
    }
    return ((((55 << 24) & 0xFF000000) + (66 << 16) & 0x00FF0000) + ((77 << 8) & 0x0000FF00) + (127 & 0x000000FF));
}
