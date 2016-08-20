#ifndef CELL_H
#define CELL_H

#include "graphic.h"
#include "cell_image.h"

#define CELL_RANGE 50.f

enum CellName{ cell = 1, mothercell, collector, decomposers, feed};

class Cell {
public:
    Cell( CellName cell, Graphic* m_graphic);
    virtual ~Cell();
    void Draw( float pos_x, float pos_y, int colour, Graphic* m_graphic, SDL_Texture* circle, int circle_size);
    void CreateTexture( Graphic* m_graphic);
    CellName GetName() { return m_cell; }

    Cell *c_right;
    Cell *c_left;
protected:
private:
    CellName m_cell;
    int cell_size;
    SDL_Texture* m_tex;
};

extern Cell* s_feed;
extern Cell* s_cell;
extern Cell* s_mothercell;
extern Cell* s_collector;
extern Cell* s_decomposers;

#endif // CELL_H
