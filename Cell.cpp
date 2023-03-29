//
// Created by Patrick Niccolai on 2019-12-03.
//

#include "Cell.h"

Cell::Cell(){
    fill = {0, 0, 0};
    center = {0, 0};
    width = 50;
    height = 50;
}
Cell::Cell(color fill, point center, unsigned int width, unsigned int height){
    this->fill = fill;
    this->center = center;
    this->width = width;
    this->height = height;
}

int Cell::getCenterX() const {
    return center.x;
}

int Cell::getLeftX() const {
    return center.x - (width / 2);
}

int Cell::getRightX() const {
    return center.x + (width / 2);
}

int Cell::getCenterY() const {
    return center.y;
}

int Cell::getTopY() const {
    return center.y - (height / 2);
}

int Cell::getBottomY() const {
    return center.y + (height / 2);
}

point Cell::getCenter() const {
    return center;
}

unsigned int Cell::getWidth() const {
    return width;
}

unsigned int Cell::getHeight() const {
    return height;
}


void Cell::draw() const {
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getRightX(), getBottomY());
    glVertex2i(getRightX(), getTopY());
    glEnd();
}

bool Cell::isOverlapping(int x, int y) const {

        if(x > getLeftX() && x < getRightX() && y > getTopY() && y < getBottomY()) {
            return true;
        }
        return false;

}

void Cell::hover() {
    this->fill = hoverFill;
}

void Cell::unHover() {
    this->fill = originalFill;
}


