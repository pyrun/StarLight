#ifndef ENGINE_H
#define ENGINE_H

#include "../NetNight/NetNight.hpp"

#include "graphic.h"
#include "framenrate.h"
#include "input.h"
#include "entity.h"
#include "control.h"
#include "../front/front.h"

#define ENGINE_STARTFRAMENRATE 60

class Engine {
public:
    Engine();
    virtual ~Engine();
    void Process();
protected:
private:
    bool m_quit;

    std::string m_ip;
    bool m_server;


    Graphic* m_graphic;
    Framenrate* m_framenrate;
    Input m_input;
    EntityList* m_entity;
    Control *m_control;
    Front* m_front;
    SDL_TimerID m_network_thrend;
    SDL_TimerID m_entity_thrend;
};

#endif // ENGINE_H
