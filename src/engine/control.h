#ifndef CONTROL_H
#define CONTROL_H

#include "graphic.h"
#include "input.h"
#include "entity.h"


class Control {
public:
    Control( Graphic *graphic);
    virtual ~Control();
    void Handle( Input *input, EntityList *entity);
    void Draw( Graphic *graphic);
protected:
private:
    SDL_Texture* m_blue;
    int m_mouse_oldpos_x = 0;
    int m_mouse_oldpos_y = 0;
    bool m_mouse_old_click = false;

    int m_pos_x;
    int m_pos_y;
    int m_pos_w, m_pos_h;
};

#endif // CONTROL_H
