//
// Created by Patrick Niccolai on 2019-12-03.
//

#ifndef FINAL_MAJOR_CELL_H
#define FINAL_MAJOR_CELL_H

#include "GameOfLife.h"
using namespace std;

struct color {
    double red;
    double green;
    double blue;
};

struct point {
    int x;
    int y;
};

class Cell {
protected:
    color fill, originalFill, hoverFill;
    point center;
    unsigned int width;
    unsigned int height;

    Cell();
    Cell(color fill, point center, unsigned int width, unsigned int height);

    int getCenterX() const;
    int getLeftX() const;
    int getRightX() const;
    int getCenterY() const;
    int getTopY() const;
    int getBottomY() const;
    point getCenter() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

public:
    virtual void draw() const;
    virtual bool change(Cell &TopLeft, Cell &Top, Cell &TopRight, Cell &Right, Cell &BottomRight, Cell &Bottom, Cell &BottomLeft, Cell&Left) const = 0;
    virtual bool cellType() const = 0;
    bool isOverlapping(int x, int y) const;
    void hover();
    void unHover();
};


#endif //FINAL_MAJOR_CELL_H
