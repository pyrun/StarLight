#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "display.h"

#define RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

class Graphic {
public:
    Graphic( int Width = 640, int Height = 400);
    virtual ~Graphic();

    int GetWidth() {
        return m_display->GetWidth();
    }
    int GetHeight() {
        return m_display->GetHeight();
    }
    SDL_Window* GetWindow() {
        if(m_display->GetWindow() == NULL) printf( "GetWindow dont exist\n");
        return m_display->GetWindow();
    }
    Display * GetDisplay() {
        if(m_display == NULL) printf( "GetDisplay dont exist\n");
        return m_display;
    }
    //inline Shader* GetShadowShader() { return m_shadow; }
    inline Camera* GetCamera() { if(m_camera == NULL) printf( "GetCamera dont exist\n"); return m_camera; }
    //void setColor( int c_r, int c_g, int c_b, int c_a) { SDL_SetRenderDrawColor( m_display->GetRenderer(), c_r, c_g, c_b, c_a); }
    void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
        Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
        *(Uint32 *)target_pixel = pixel;
    }

    SDL_Surface* LoadSurface(std::string File);
    SDL_Texture* LoadTexture(std::string File);
    void setdrawColor( char color_red, char color_green, char color_blue, char color_alpha);
    void draw( SDL_Texture* Image, double X, double Y, int W, int H, int SpriteX, int SpriteY, bool Flip);
    void drawLine( int pos_x1, int pos_y1, int pos_x2, int pos_y2);
    void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);
    void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);
    void SaveImageBMP( std::string File);
protected:
private:
    Camera *m_camera;
    Display* m_display;
};

#endif // GRAPHIC_H
