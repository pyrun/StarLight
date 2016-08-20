#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>

#include "cell.h"

#define ENTITY_MARK_CRICLE_SIZE 16

enum Entity_team { red = 0, yellow, green, blue};

extern int GetTeamColor( Entity_team team);

class Entity {
public:
    Entity( CellName id, float pos_x, float pos_y, Entity_team team) {
        m_name = id;
        m_next = NULL;
        m_x = pos_x;
        m_y = pos_y;
        m_team = team;
    }
    virtual ~Entity() {}
    Entity* m_next;
    CellName GetCellName() { return m_name; }
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    Entity_team GetTeam() { return m_team; }
    bool IsMarked() { return m_mark; }
    void SetMark( bool set) { m_mark = set; }
protected:
private:
    CellName m_name;
    float m_x, m_y;
    Entity_team m_team;
    bool m_mark;
};

class EntityList {
public:
    EntityList( Graphic* graphic);
    ~EntityList();

    void createEntity( CellName id, float pos_x, float pos_y, Entity_team team);
    void editData( int index, int wert, int wert2, Entity *entity);
    void editRectData( int x1, int y1, int x2, int y2, int index, int wert, int wert2, Entity *entity);
    void editifdata( int index, int wert, int wert2, int setindex, int setwert,  int setwert2, Entity* entity);
    void earseAll( int index, int wert, int wert2, Entity* entity);
    void drawAll( Graphic* graphic);
    void drawEntity( Entity* entity, Graphic* graphic);
    void deleteAll( Entity* entity);
    Entity* getTree() { return m_entity; }
protected:
private:
    Entity* m_entity;
    SDL_Texture* m_circle;
};
#endif // ENTITY_H
