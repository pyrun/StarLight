#ifndef FRONT_H
#define FRONT_H

#include "../engine/graphic.h"
#include "front_image.h"

class Front {
public:
    Front( Graphic* graphic);
    virtual ~Front();
    void drawSentence( Graphic* graphic, char* text, int pos_x, int pos_y) {
        for( int i = 0; i <= (int)strlen( text);i++) {
            drawLetter( graphic, text[i], pos_x+(i*(front_text_width/2.25) ), pos_y);
        }
    }
    void drawLetter( Graphic* graphic, char letter, int pos_x, int pos_y) {
        int x = (int)letter; // -32
        int y = 0;
        int amount_width = front_bitmap_width/front_text_width;
        // zeichen finden
        while( x >= amount_width) {
            x -= amount_width;
            y++;
        }
        // zeichnen
        graphic->draw( m_bitmap, pos_x, pos_y, front_text_width, front_text_height, x, y, false);
    }
protected:
private:
    SDL_Texture* m_bitmap;
};

#endif // FRONT_H
