#ifndef ENGINE_H
#define ENGINE_H

#include "../NetNight/NetNight.hpp"

#include "graphic.h"
#include "framenrate.h"
#include "input.h"
#include "../entity/entity.h"
#include "control.h"

#define ENGINE_STARTFRAMENRATE 60

class Engine {
public:
    Engine();
    virtual ~Engine();

    void ControlMove();

    void Process();
protected:
private:
    bool m_quit;

    std::string m_ip;
    bool m_server;

    bool m_move_camera;
    int m_mouse_x;
    int m_mouse_y;


    Graphic* m_graphic;
    Framenrate* m_framenrate;
    Input m_input;
    EntityList* m_entity;
    Control *m_control;
    SDL_TimerID m_network_thrend;
};

#endif // ENGINE_H
