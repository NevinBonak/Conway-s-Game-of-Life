//
// Created by Patrick Niccolai on 2019-12-03.
//

#ifndef FINAL_MAJOR_DEADCELL_H
#define FINAL_MAJOR_DEADCELL_H

#include "Cell.h"


class DeadCell : public Cell {
public:
    DeadCell(point center, unsigned int width, unsigned int height);

    void draw() const override;
    bool change(Cell &TopLeft, Cell &Top, Cell &TopRight, Cell &Right, Cell &BottomRight, Cell &Bottom, Cell &BottomLeft, Cell&Left) const override;
    bool cellType() const override;
};


#endif //FINAL_MAJOR_DEADCELL_H
