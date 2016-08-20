#include "cell.h"

#include "stdint.h"
#include "SDL2/SDL.h"

Cell* s_feed = NULL;
Cell* s_cell = NULL;
Cell* s_mothercell = NULL;
Cell* s_collector = NULL;
Cell* s_decomposers = NULL;

Cell::Cell( CellName cell, Graphic* m_graphic) {
    m_cell = cell;
    CreateTexture( m_graphic);
}

Cell::~Cell() {
    printf("Cell::~Cell destroyed\n");
    SDL_DestroyTexture( m_tex);
}

void Cell::Draw( float pos_x, float pos_y, int colour, Graphic* m_graphic, SDL_Texture* circle, int circle_size) {
    int r = colour >> 24 & 0xFF;
    int g = colour >> 16 & 0xFF;
    int b = colour >> 8 & 0xFF;
    int a = colour & 0xFF;

    SDL_SetTextureColorMod( m_tex, r, g, b);
    m_graphic->draw( m_tex, pos_x-cell_size, pos_y-cell_size, cell_size*2, cell_size*2, 0, 0, false);
    // falls cricle mitzeichnen
    if( circle != NULL)
        m_graphic->draw( circle, pos_x-circle_size/2, pos_y-circle_size/2, circle_size, circle_size, 0, 0, false);
}

void Cell::CreateTexture( Graphic* m_graphic) {
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
    // Cell einstelungen
    switch( m_cell) {
        case mothercell:
            cell_size = 128;
        break;
        case collector:
        case decomposers:
            cell_size = 32;
        break;
        case feed:
            cell_size = 8;
        break;
        default:
            cell_size = 16;
        break;
    }
    // Bild erstellen
    SDL_Surface* surface_cell = SDL_CreateRGBSurface( 0, cell_size*2, cell_size*2, 32, rmask, gmask, bmask, amask);
    // Zeichnen
    switch( m_cell) {
        case mothercell:
            m_graphic->fill_circle( surface_cell, cell_size, cell_size, cell_size/4, 0xffffffff );
        break;
        case collector:
            m_graphic->draw_circle( surface_cell, cell_size, cell_size, 5, 0xffffffff );
        break;
        case decomposers:
            m_graphic->fill_circle( surface_cell, cell_size, cell_size, 5, 0xffffffff );
        break;
        case feed:
            m_graphic->fill_circle( surface_cell, cell_size, cell_size, cell_size/2, 0xffffffff );
        break;
        default:
        break;
    }
    m_graphic->draw_circle( surface_cell, cell_size, cell_size, cell_size/2, 0xffffffff );
    //
    m_tex = SDL_CreateTextureFromSurface( m_graphic->GetDisplay()->GetRenderer(), surface_cell);
    SDL_FreeSurface( surface_cell);
}
