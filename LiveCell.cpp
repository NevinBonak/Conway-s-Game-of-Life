//
// Created by Patrick Niccolai on 2019-12-03.
//

#include "LiveCell.h"

LiveCell::LiveCell(point center, unsigned int width, unsigned int height) : Cell({255,255,255}, center, width, height){
    hoverFill = {100, 100, 100};
    originalFill = fill;
}

void LiveCell::draw() const {
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getRightX(), getBottomY());
    glVertex2i(getRightX(), getTopY());
    glEnd();
}

bool LiveCell::change(Cell &TopLeft, Cell &Top, Cell &TopRight, Cell &Right, Cell &BottomRight, Cell &Bottom, Cell &BottomLeft, Cell &Left) const{
    int numLiveNeighbors = 0;

    if(TopLeft.cellType() == true){
        numLiveNeighbors++;
    }
    if(Top.cellType() == true){
        numLiveNeighbors++;
    }
    if(TopRight.cellType() == true){
        numLiveNeighbors++;
    }
    if(Right.cellType() == true){
        numLiveNeighbors++;
    }
    if(BottomRight.cellType() == true){
        numLiveNeighbors++;
    }
    if(Bottom.cellType() == true){
        numLiveNeighbors++;
    }
    if(BottomLeft.cellType() == true){
        numLiveNeighbors++;
    }
    if(Left.cellType() == true){
        numLiveNeighbors++;
    }

    if(numLiveNeighbors == 2 || numLiveNeighbors == 3){
        return true;
    } else {
        return false;
    }
}

bool LiveCell::cellType() const{
    return true;
}