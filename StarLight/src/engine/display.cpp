//#define GLEW_STATIC 1

#include "display.h"
#include <stdio.h>

Display::Display(int width, int height, const std::string& title) {
    m_width = width;
    m_height = height;
    Uint32 rmask, gmask, bmask, amask;
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
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Could not init SDL");
        return;
    }
    // SDL Init
    // Erstelle Fenster
	m_window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_RESIZABLE);
	if( m_window == NULL) {
        printf( "Display: Error\n");
	}
    // Renderer
    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED);
    if( m_renderer == NULL) {
        printf( "Display: Renderer could not be created! SDL Error \"%s\"", SDL_GetError());
    }

}

Display::~Display() {
    SDL_DestroyRenderer( m_renderer );
	SDL_DestroyWindow( m_window);
	SDL_Quit();
}

void Display::Clear(int color_r, int color_g, int color_b, int color_a) {
    // Reset Color
    SDL_SetRenderDrawColor( m_renderer, color_r, color_g, color_b, color_a);
    SDL_RenderClear( m_renderer);
}

void Display::SwapBuffers() {
	SDL_RenderPresent( m_renderer );
}

void Display::SetTitle( std::string& title) {
    SDL_SetWindowTitle( m_window, title.c_str());
}
