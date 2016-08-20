#include "framenrate.h"
#include <stdio.h>

Framenrate::Framenrate() {
    m_start = 0;
    m_end = 0;
    m_rate = 16;
    List.SetMax( FRAMENRATE_LIST);
}

Framenrate::~Framenrate() {

}

void Framenrate::Set( int Hz) {
    m_rate = 1.0f/Hz*1000; // 1/f -> sec benötigen aber ms -> *1000
}

void Framenrate::StartCount() {
    m_start = SDL_GetTicks();
}

void Framenrate::EndCount() {
    m_end = SDL_GetTicks();
}

void Framenrate::CalcDelay() {
    // Falls counter kein ende hat einen setzten
    if( m_end == 0)
        EndCount();
    // Zeit ausrechnen
    int m_delay = m_end - m_start;
    // Zeit zu hoch
    if( m_delay > m_rate)
        return;
    SDL_Delay( (int)m_rate - m_delay); // Abwarten
    float m_fps = (float)1000.0f/( SDL_GetTicks() - m_start);
    List.AddTime( (int)m_fps);
    // Reset
    m_start = 0;
    m_end = 0;
}

float Framenrate::GetFramenrate() {
    return List.GetTime();
}
