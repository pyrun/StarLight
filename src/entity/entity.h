#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>

#include "cell.h"
#include "../front/front.h"

#define ENTITY_MARK_CRICLE_SIZE 16
#define ENTITY_SPEED 2.f

enum Entity_team { red = 0, yellow, green, blue};
enum Entity_process { process_nothing = 0, process_toposition, process_collect};

extern int GetTeamColor( Entity_team team);


/*
Data        Wert1   Wert2
0   marked  Setzen  NA
1   goto    posX    posY
2
3

*/

class Entity {
public:
    Entity( CellName id, int number, float pos_x, float pos_y, Entity_team team) {
        m_name = id;
        m_next = NULL;
        m_x = pos_x;
        m_y = pos_y;
        m_team = team;
        m_number = number;

        m_previously = NULL;
        m_right = NULL;
        m_left = NULL;

        m_process = process_nothing;

        m_mark = false;
    }
    virtual ~Entity() {}

    Entity* m_next;

    // Team
    Entity* m_previously;
    Entity* m_right;
    Entity* m_left;

    CellName GetCellName() { return m_name; }
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    float getToX() { return m_tox; }
    float getToY() { return m_toy; }
    Entity_process& getProcess() { return m_process; }
    float getSpeed() { return ENTITY_SPEED; }
    int getNumber() { return m_number; }
    Entity_team GetTeam() { return m_team; }
    bool IsMarked() { return m_mark; }
    void setMark( bool set) { m_mark = set; }
    void setToPos( int t_tox, int t_toy) {
        m_tox = t_tox;
        m_toy = t_toy;
        printf( "Entity::setToPos set to %d %d\n", m_tox, m_toy);
    }
    void setPos( int pos_x, int pos_y) {
        m_x = pos_x;
        m_y = pos_y;
        printf( "Entity::setPos set to %d %d\n", pos_x, pos_y);
    }
    void moveAngle( float angle) {
        m_x += cos( angle ) * getSpeed();
        m_y += sin( angle ) * getSpeed();
    }
protected:
private:
    int m_number;
    CellName m_name;
    float m_x, m_y;
    bool m_mark;
    Entity_team m_team;
    Entity_process m_process;
    int m_tox, m_toy;
};

class EntityList {
public:
    EntityList( Graphic* graphic);
    ~EntityList();

    Entity* createEntity( CellName id, float pos_x, float pos_y, Entity_team team);
    bool createTeamEntity( CellName id, float pos_x, float pos_y, Entity* t_teamentity);
    float getAngle( int pos_x1, int pos_y1, int pos_x2, int pos_y2);
    float getDistance( int pos_x1, int pos_y1, int pos_x2, int pos_y2);
    void process();
    void editData( int index, int wert, int wert2, Entity *entity);
    void editRectData( int x1, int y1, int x2, int y2, int index, int wert, int wert2, Entity *entity);
    void earseAll( int index, int wert, int wert2, Entity* entity);
    void drawAll( Graphic* graphic, Front* front);
    void drawEntity( Entity* entity, Graphic* graphic, Front* front);
    void deleteAll( Entity* entity);
    void deleteEntity( Entity* entity, Entity* tree);
    bool checkDistanceTeam ( Entity* obj, float distance, CellName ignorCell);
    Entity* findDistanceTeam ( Entity* obj, CellName id,float distance);
    Entity* getTree() { return m_entity; }
    int getAmountEntity() {
        Entity *ent = getTree();
        int amount = 0;
        while( ent->m_next != NULL) {
            ent = ent->m_next;
            amount++;
        }
        return amount;
    }

    bool m_bussy;

    Entity* findEntityMarked( Entity* t_entity) {
        if( t_entity->IsMarked())
            return t_entity;
        else if( t_entity->m_next != NULL )
            return findEntityMarked( t_entity->m_next);
        return NULL;
    }
protected:
private:
    int m_number_index;
    Entity* m_entity;
    SDL_Texture* m_circle;
};
#endif // ENTITY_H
