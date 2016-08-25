#include "graphic.h"

#include <SDL2/SDL_image.h>
#include "math.h"

Graphic::Graphic( int Width, int Height) {
    m_display = new Display( Width, Height, "Start game...");
    // camera
    m_camera = new Camera();
    m_camera->set( 0,0);
}
Graphic::~Graphic() {
    delete m_camera;
    delete m_display;
}
SDL_Surface* Graphic::LoadSurface(std::string File) {
    // Laden der Datei
    SDL_Surface* loaded = IMG_Load(File.c_str());
	if( loaded == NULL ) {
        printf( "Unable to load image %s!", File.c_str() ); // Fehler
        printf( "%s", SDL_GetError() );
        return NULL;
    } else {
        // Color key ferstlegen
        //SDL_SetColorKey( loaded, true, SDL_MapRGB( loaded->format, 200, 191, 231));
    }
    return loaded;
}
SDL_Texture* Graphic::LoadTexture(std::string File) {
    // Laden der Datei
    SDL_Surface* loaded = LoadSurface( File);
    // Wandle die datei in eine Texture um
    SDL_Texture* texture = SDL_CreateTextureFromSurface( m_display->GetRenderer(), loaded);
    // geb den speicher wieder frei
    SDL_FreeSurface( loaded);
    return texture;
}
void Graphic::setdrawColor( char color_red, char color_green, char color_blue, char color_alpha) {
    SDL_SetRenderDrawColor( m_display->GetRenderer(), color_red, color_green, color_blue, color_alpha);
}
void Graphic::draw( SDL_Texture* Image, double pos_x, double pos_y, int image_w, int image_h, int SpriteX, int SpriteY, bool Flip) {
    SDL_Rect destination;
    // Camera
    pos_x += m_camera->GetX();
    pos_y += m_camera->GetY();
    // Recheck auf dem Renderer
    destination.x = (int)pos_x;
    destination.y = (int)pos_y;
    destination.w = image_w;
    destination.h = image_h;
    // Rechteck auf dem Bild ( Image)
    SDL_Rect source;
    source.x = SpriteX*image_w;
    source.y = SpriteY*image_h;
    source.w = image_w;
    source.h = image_h;
    if( Image == NULL ) // Todo bessere fehlerbehandlung
        printf( "Graphic::draw: image nicht gefunden\n");
    SDL_RenderCopy( m_display->GetRenderer(), Image, &source, &destination);
}
void Graphic::drawLine( int pos_x1, int pos_y1, int pos_x2, int pos_y2) {
    // Camera
    pos_x1 += m_camera->GetX();
    pos_y1 += m_camera->GetY();
    pos_x2 += m_camera->GetX();
    pos_y2 += m_camera->GetY();
    // Line
    SDL_RenderDrawLine( m_display->GetRenderer(), pos_x1, pos_y1, pos_x2, pos_y2);
}
void Graphic::draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)  {
    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y) {
        set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);

        if (x != 0) {
            set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }
        if (y != 0) {
            set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }
        if (x != 0 && y != 0) {
            set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0) {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void Graphic::fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{
    // Note that there is more to altering the bitrate of this
    // method than just changing this value.  See how pixels are
    // altered at the following web page for tips:
    //   http://www.libsdl.org/intro.en/usingvideo.html
    static const int BPP = 4;

    double r = (double)radius;

    for (double dy = 0; dy <= r; dy += 1.0)
    {
        // This loop is unrolled a bit, only iterating through half of the
        // height of the circle.  The result is used to draw a scan line and
        // its mirror image below it.

        // The following formula has been simplified from our original.  We
        // are using half of the width of the circle because we are provided
        // with a center and we need left/right coordinates.

        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        int x = cx-1 - dx;

        // Grab a pointer to the left-most pixel for each half of the circle
        Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;

        for (; x <= cx + dx; x++)
        {
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
        }
    }
}

void Graphic::SaveImageBMP( std::string File) {
    // Save Image
    File = File + ".png";
    /*SDL_RWops *file = SDL_RWFromFile( File.c_str(), "wb");
    SDL_SaveBMP_RW( m_display->GetSurface(), file, 0);
    file->close(file);*/
    /*if( IMG_SavePNG( m_display->GetSurface(), File.c_str())) {
        printf("Unable to save png -- %s\n", SDL_GetError());
    }*/
}
