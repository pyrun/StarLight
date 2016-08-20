#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

struct s_mouse {
    int m_x;
    int m_y;
    float c_x;
    float c_y;
};

class InputMap {
public:
    s_mouse MousePos;

    bool Up;
    bool Down;
    bool Right;
    bool Left;

    bool Inventory;
    bool Jump;
    bool Shift;

    bool Place;
    bool Destory;

    bool MouseGrab;
protected:
private:
};

class Input {
public:
    Input();
    virtual ~Input();

    void Reset();
    bool Handle( int W, int H, SDL_Window *Win, int pos_x_cam, int pos_y_cam);

    InputMap Map;
    InputMap MapOld;

    int NewW, NewH;
protected:
private:
    bool GrabMouse;
    SDL_Event m_event;
};

#endif // INPUT_H
