#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

#include "camera.h"

class Display {
public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void Clear(int color_r, int color_g, int color_b, int color_a);
    void SwapBuffers();
    void SetTitle( std::string& title);

    inline int GetWidth() { return m_width; }
	inline int GetHeight() { return m_height; }

	inline int GetTilesetWidth() { return 1024; }
	inline int GetTilesetHeight() { return 1024; }

	inline SDL_Window* GetWindow() { return m_window; }
	inline SDL_Renderer* GetRenderer() { return m_renderer; }

protected:
private:
    int m_width;
	int m_height;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};

#endif // DISPLAY_H
