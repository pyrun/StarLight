#include "input.h"

#include "stdio.h"
#include "math.h"

Input::Input() {
    GrabMouse = false;
    Reset(); // anfangswerte reseten
    Reset(); // 2te mal um auch altemap reset durchzuführen
}
Input::~Input() {

}
void Input::Reset() {
    MapOld = Map; // Merken als alt
    // richtungspfeile
    Map.Up = false;
    Map.Down = false;
    Map.Right = false;
    Map.Left = false;
    // Invetory
    Map.Inventory = false;
    Map.Jump = false;
    Map.Shift = false;

    Map.Place = false;
    Map.Destory = false;

    Map.MouseGrab = false;
}
bool Input::Handle( int W, int H, SDL_Window *Win, int pos_x_cam, int pos_y_cam) {
    int X, Y;
    Uint32 State;
    NewW = 0;
    NewH = 0;
    const Uint8* Keys = SDL_GetKeyboardState( NULL );
    // Pull all keys
    while( SDL_PollEvent(&m_event) ) {
        if(m_event.type == SDL_QUIT)
            return false;
        if( m_event.type == SDL_WINDOWEVENT && m_event.window.event == SDL_WINDOWEVENT_RESIZED) {
            NewW = m_event.window.data1;
            NewH = m_event.window.data2;
            printf( "%d %d resize\n", NewH, NewW);
        }
    }
    // Maus eingabe greifen
    State = SDL_GetMouseState( &X, &Y);
    Map.MousePos.m_x = X-pos_x_cam;
    Map.MousePos.m_y = Y-pos_y_cam;
    if( GrabMouse) { // Maus winkel erechnen
        Map.MousePos.c_x = (float)X;
        Map.MousePos.c_y = (float)Y;
        Map.MousePos.c_x /= W;
        Map.MousePos.c_y /= H;
        Map.MousePos.c_x -= 0.5;
        Map.MousePos.c_y -= 0.5;
        if( fabs (Map.MousePos.c_x) < 0.001 && fabs(Map.MousePos.c_y) < 0.001 ) {// Rundungsfehler
            Map.MousePos.c_x = 0;
            Map.MousePos.c_y = 0;
        }
        SDL_WarpMouseInWindow( Win, W/2, H/2); // Maus in die mitte ziehen
    } else {
        Map.MousePos.c_x = 0;
        Map.MousePos.c_y = 0;
    }
    // Mauskeys
    if( State & SDL_BUTTON(SDL_BUTTON_LEFT) || Keys[SDL_SCANCODE_2]) {
        Map.Destory = true;
    }
    if( State & SDL_BUTTON(SDL_BUTTON_RIGHT) || Keys[SDL_SCANCODE_1]) {
        Map.Place = true;
    }
    // Richtungstasten
    if( Keys[SDL_SCANCODE_LEFT] | Keys[SDL_SCANCODE_A] )
        Map.Left = true;
    if( Keys[SDL_SCANCODE_RIGHT] | Keys[SDL_SCANCODE_D] )
        Map.Right = true;
    if( Keys[SDL_SCANCODE_UP] | Keys[SDL_SCANCODE_W] )
        Map.Up = true;
    if( Keys[SDL_SCANCODE_DOWN] | Keys[SDL_SCANCODE_S] )
        Map.Down = true;
    // Sondertasten
    if( Keys[SDL_SCANCODE_ESCAPE] )
        Map.MouseGrab = true;
    if( Keys[SDL_SCANCODE_SPACE] |Keys[SDL_SCANCODE_R] )
        Map.Jump = true;
    if( Keys[SDL_SCANCODE_F] )
        Map.Shift = true;
    if( Keys[SDL_SCANCODE_E] || Keys[SDL_SCANCODE_I] )
        Map.Inventory = true;
    if( Map.MouseGrab && !MapOld.MouseGrab ) {
        GrabMouse = !GrabMouse;
        //SDL_ShowCursor( !GrabMouse);
    }
    return true;
}
