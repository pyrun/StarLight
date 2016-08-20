#include "entity.h"

EntityList::EntityList( Graphic* graphic) {
    int rmask, gmask, bmask, amask;
    m_entity = NULL;

    // Byte Oder
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

    // Erstelle Cell liste ( Grafikschnitstelle und zwischenspeicher)
    if( s_cell == NULL) {
        s_cell = new Cell( cell, graphic);
        s_mothercell = new Cell( mothercell, graphic);
        s_collector = new Cell( collector, graphic);
        s_decomposers = new Cell( decomposers, graphic);
        s_feed = new Cell( feed, graphic);
    }

    // Makierkreiﬂ erstellen
    SDL_Surface* surface_circle = SDL_CreateRGBSurface( 0, ENTITY_MARK_CRICLE_SIZE, ENTITY_MARK_CRICLE_SIZE, 32, rmask, gmask, bmask, amask);

    // Zeichnen
    for( int x = 0; x < 16; x++ )
        for( int y = 0; y < 16; y++ )
            graphic->set_pixel( surface_circle, x, y, 0x66FF0000 );

    // als texture umwandeln
    m_circle = SDL_CreateTextureFromSurface( graphic->GetDisplay()->GetRenderer(), surface_circle);
    SDL_FreeSurface( surface_circle);

    // Index
    m_number_index = 0;
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
Entity* EntityList::createEntity( CellName id, float pos_x, float pos_y, Entity_team team) {
    Entity *t_entity;
    Entity* attach;
    m_number_index++;
    t_entity = new Entity( id, m_number_index, pos_x, pos_y, team);
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
    return t_entity;
}
bool EntityList::createTeamEntity( CellName id, float pos_x, float pos_y, Entity* t_teamentity) {
    Entity *t_entity;
    Entity *attach;

    // erstellt
    //printf( "createTeamEntity: Erstellt %d %d\n", (int)t_entity->GetX(), (int)t_entity->GetY());

    // Baumende suchen
    if( t_teamentity == NULL) {
        printf( "createTeamEntity: dont found t_teamentity\n");
        return false;
    } else {
        if( t_teamentity->m_right == NULL || t_teamentity->m_left == NULL);
        else {
            printf( "createTeamEntity: no space for new team entity\n");
            return false;
        }
        // Erstellen
        t_entity = createEntity( id, pos_x, pos_y, t_teamentity->GetTeam());

        t_entity->m_previously = t_teamentity;

        if( t_teamentity->m_right == NULL)
            t_teamentity->m_right = t_entity;
        else
            t_teamentity->m_left = t_entity;
        return true;
    }
}
float EntityList::getAngle( int pos_x1, int pos_y1, int pos_x2, int pos_y2) {
    float angle = atan2(pos_y2 - pos_y1 , pos_x2 - pos_x1);
    return angle;
}
float EntityList::getDistance( int pos_x1, int pos_y1, int pos_x2, int pos_y2) {
    float distance = ((pos_x2-pos_x1)*(pos_x2-pos_x1))+((pos_y2-pos_y1)*(pos_y2-pos_y1));
    distance = sqrt( distance);
    return distance;
}
bool EntityList::checkDistanceTeam ( Entity* obj, float distance, CellName ignorCell) {
    bool b_return = false;
    Entity* tree = getTree();
    do {
        // gleiches team suchen
        if( tree->GetCellName() != ignorCell)
            if( tree->GetTeam() == obj->GetTeam() && obj->getNumber() != tree->getNumber()) {
                if( getDistance( obj->GetX(), obj->GetY(), tree->GetX(), tree->GetY()) < distance ) {
                    b_return = true;
                }
            }
        tree = tree->m_next;
    } while( tree != NULL);
    return b_return;
}
Entity* EntityList::findDistanceTeam ( Entity* obj, CellName id, float distance) {
    bool b_return = true;
    Entity* tree = m_entity;
    Entity* found = NULL;
    do {
        // gleiches team suchen
        if( tree->GetTeam() == obj->GetTeam())
            if( getDistance( obj->GetX(), obj->GetY(), tree->GetX(), tree->GetY()) < distance )
                if( tree->GetCellName() == id ) {
                    if( found == NULL)
                        found = tree;
                    else if( getDistance( obj->GetX(), obj->GetY(), tree->GetX(), tree->GetY()) < getDistance( obj->GetX(), obj->GetY(), found->GetX(), found->GetY()))
                        found = tree;
                }
        tree = tree->m_next;
    } while( tree != NULL);
    return found;
}

void EntityList::process() {
    Entity* obj = getTree();
    // Schleife
    do {
        // to pos
        if( obj->getProcess() == process_toposition) {
            float angle = getAngle( obj->GetX(), obj->GetY(), obj->getToX(), obj->getToY());
            float distance = getDistance( obj->GetX(), obj->GetY(), obj->getToX(), obj->getToY());
            //printf( "%d %d\n", (int)distance, checkDistanceTeam( obj, 100));
             if( !checkDistanceTeam( obj, CELL_RANGE, cell)) {
                Entity* e_find = findDistanceTeam( obj, collector, CELL_RANGE+5.f);
                if( e_find == NULL)
                    e_find = findDistanceTeam( obj, mothercell, CELL_RANGE+5.f);

                if( e_find != NULL) {
                    // teammember erstellen falls es geht
                    if(createTeamEntity( collector, obj->GetX(), obj->GetY(), e_find)) {
                    }
                }
                deleteEntity( obj, getTree());
                return;
            }
            if( distance < obj->getSpeed()) {
                obj->setPos( obj->getToX(), obj->getToY());
                // process abgeschlossen
                obj->getProcess() = process_nothing;
            } else
                obj->moveAngle( angle); // langsam zum ziel
        }
        obj = obj->m_next;
    } while( obj != NULL);
}
void EntityList::editData( int index, int wert, int wert2, Entity *entity) {
   switch( index ) {
       case 0: entity->setMark( (bool)wert); break;
       case 1: entity->getProcess() = process_toposition; entity->setToPos( wert, wert2); break;
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
void EntityList::earseAll( int index, int wert, int wert2, Entity* entity) {
    if( entity == NULL)
        return;
    if( entity->m_next != NULL)
        earseAll( index, wert, wert2, entity->m_next);
    editData( index, wert, wert2, entity);
}
void EntityList::drawAll( Graphic* graphic, Front* front) {
    drawEntity( m_entity, graphic, front);
}
void EntityList::drawEntity( Entity* entity, Graphic* graphic, Front* front) {
    // Falls nicht addresiert nichts machen
    if( entity == NULL)
        return;
    if( entity->m_next != NULL)
        drawEntity( entity->m_next, graphic, front);
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

    // hex to rgb
    int c_red = ((color >> 24) & 0xFF);
    int c_green = ((color >> 16) & 0xFF);
    int c_blue = ((color >> 8) & 0xFF);
    int c_alpha = ((color) & 0xFF);

    // set color
    graphic->setdrawColor( c_red, c_green, c_blue, c_alpha);
    // Verbinden falls Entity angehˆrige hat
    if( entity->m_right != NULL) {
        graphic->drawLine( entity->GetX(), entity->GetY(), entity->m_right->GetX(), entity->m_right->GetY());
    }
    if( entity->m_left != NULL) {
        graphic->drawLine( entity->GetX(), entity->GetY(), entity->m_left->GetX(), entity->m_left->GetY());
    }
    char text[256];
    sprintf( text, "%d", entity->getNumber());
    front->drawSentence( graphic, text, entity->GetX(), entity->GetY());
}
void EntityList::deleteAll( Entity* entity) {
    // Falls nicht addresiert nichts machen
    if( entity == NULL)
        return;
    // bevor lˆschen erst sein kind lˆschen
    if( entity->m_next != NULL)
        deleteAll( entity->m_next);
    printf("DeleteAll: Loschen des Entity %d %d\n", (int)entity->GetX(), (int)entity->GetY());
    // selbst lˆschen und wert reseten f¸r zunk¸ftige bearbeitung
    delete entity;
    entity = NULL;
}
void EntityList::deleteEntity( Entity* entity, Entity* tree) {
    Entity* found = tree, *tmp_found;

    // falls tree gelˆscht wird
    if( getTree() == entity) {
        if( getTree()->m_next != NULL)
            tmp_found = getTree()->m_next;
        else
            tmp_found = NULL;
        delete getTree();
        m_entity = tmp_found;
        return;
    }

    do {
        /*if( found->m_next == entity) {
            if( found->m_next->m_next != NULL)
                tmp_found = found->m_next->m_next;
            else
                tmp_found = NULL;
            // Entity gefunden und restlos entfernen
            printf( "EntityList::deleteEntity %d\n", found->m_next->getNumber());
            delete found->m_next;
            found->m_next = tmp_found;
            return;
        }*/
        if( found->m_next != NULL && found->m_next == entity) {
            if( found->m_next->m_next != NULL)
                tmp_found = found->m_next->m_next;
            else
                tmp_found = NULL;
            delete found->m_next;
            found->m_next = tmp_found;
        }
        found = found->m_next;
    } while( found != NULL);

    /*while( found->m_next != NULL ) {
        if( found->m_next == entity) {
            if( found->m_next->m_next != NULL)
                tmp_found = found->m_next->m_next;
            else
                tmp_found = NULL;
            // Entity gefunden und restlos entfernen
            printf( "EntityList::deleteEntity %d\n", found->m_next->getNumber());
            delete found->m_next;
            found->m_next = tmp_found;
            return;
        }
        //
        found = found->m_next;
    }*/
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
