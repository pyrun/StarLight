#include "control.h"

#include <SDL2/SDL_image.h>

Control::Control( Graphic *graphic) {
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

    // Bild erstellen mark
    SDL_Surface* surface_cell = SDL_CreateRGBSurface( 0, 1, 1, 32, rmask, gmask, bmask, amask);
    graphic->set_pixel( surface_cell, 0, 0, 0x66FF0000 );
    m_blue = SDL_CreateTextureFromSurface( graphic->GetDisplay()->GetRenderer(), surface_cell);
    SDL_FreeSurface( surface_cell);
}

Control::~Control() {
    SDL_DestroyTexture( m_blue);
}

void Control::Handle( Input *input, EntityList *entity) {
    if( m_mouse_old_click == false && input->Map.Destory && !input->MapOld.Destory ) {
        m_mouse_oldpos_x = input->Map.MousePos.m_x;
        m_mouse_oldpos_y = input->Map.MousePos.m_y;
        m_mouse_old_click = true;
    }
    if( m_mouse_old_click == true) {
        m_pos_x = (int)m_mouse_oldpos_x;
        m_pos_y = (int)m_mouse_oldpos_y;
        if( input->Map.MousePos.m_x-m_mouse_oldpos_x > 0)
            m_pos_w = input->Map.MousePos.m_x-m_mouse_oldpos_x;
        else {
            m_pos_w = m_mouse_oldpos_x-input->Map.MousePos.m_x;
            m_pos_x = m_pos_x+input->Map.MousePos.m_x-m_mouse_oldpos_x;
        }
        if( input->Map.MousePos.m_y-m_mouse_oldpos_y > 0)
            m_pos_h = input->Map.MousePos.m_y-m_mouse_oldpos_y;
        else {
            m_pos_h = m_mouse_oldpos_y-input->Map.MousePos.m_y;
            m_pos_y = m_pos_y+input->Map.MousePos.m_y-m_mouse_oldpos_y;
        }

        //loslassen
        if( !input->Map.Destory) {
            m_mouse_old_click = false;
            // davor alle makierungen entfernen
            entity->earseAll( 0, 0, 0, entity->getTree());
            // alle makieren die da darin sind
            entity->editRectData( m_pos_x, m_pos_y, m_pos_w, m_pos_h, 0, 1, 0, entity->getTree());
        }
    }
    if( input->Map.Place && !input->MapOld.Place)
        printf( "left click\n");

}

void Control::Draw( Graphic *graphic) {
    if( m_mouse_old_click == true)
        graphic->draw( m_blue, m_pos_x, m_pos_y, m_pos_w, m_pos_h, 0, 0, false);
}
