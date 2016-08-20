#include "front.h"

Front::Front( Graphic* graphic) {
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

    // Bild erstellen
    SDL_Surface* surface_front = SDL_CreateRGBSurface( 0, front_bitmap_width, front_bitmap_height, 32, rmask, gmask, bmask, amask);

    // get pixel and set
    for( int x = 0; x < front_bitmap_width; x++ ) {
        for( int y = 0; y < front_bitmap_height; y++ ) {
            int r = 0xFF - front_bitmap[ x+(y*front_bitmap_width)];
            int color = RGB32BIT( r, r, r, 0xFF);
            // set pixel
            graphic->set_pixel( surface_front, x, y, color);
        }
    }

    // erstellt textur aus surface
    m_bitmap = SDL_CreateTextureFromSurface( graphic->GetDisplay()->GetRenderer(), surface_front);
    SDL_FreeSurface( surface_front);
}

Front::~Front() {
    // free Tex
    SDL_DestroyTexture( m_bitmap);
}
