//
// Created by angel on 2022-01-13.
//
/*!
 * @file Shape.cpp
 *
 * @brief Shape.cpp implementerar klassen Shape
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */

#include "Shape.h"

void Shape::setShape(shapes fig) {
    switch(fig){
        case I_shape:
            coords[0] = QPoint(0,0);
            coords[1] = QPoint(0, 1);
            coords[2] = QPoint(0, 2);
            coords[3] = QPoint(0, 3);
            break;
        case J_shape:
            coords[0] = QPoint(1,0);
            coords[1] = QPoint(0,0);
            coords[2] = QPoint(0,1);
            coords[3] = QPoint(0,2);
            break;
        case Z_shape:
            coords[0] = QPoint(-1,0);
            coords[1] = QPoint(0,0);
            coords[2] = QPoint(0,1);
            coords[3] = QPoint(1,1);
            break;
        case S_shape:
            coords[0] = QPoint(1,0);
            coords[1] = QPoint(0,0);
            coords[2] = QPoint(0,1);
            coords[3] = QPoint(-1,1);
            break;
        case O_shape:
            coords[0] = QPoint(0,0);
            coords[1] = QPoint(1,0);
            coords[2] = QPoint(0,1);
            coords[3] = QPoint(1,1);
            break;
        case T_shape:
            coords[0] = QPoint(0,0);
            coords[1] = QPoint(0,1);
            coords[2] = QPoint(1,1);
            coords[3] = QPoint(-1,1);
            break;
        case L_shape:
            coords[0] = QPoint(-1,0);
            coords[1] = QPoint(0,0);
            coords[2] = QPoint(0,1);
            coords[3] = QPoint(0,2);
            break;
        default:
            break;
    }
    figure = fig;
}

/*!
 * Returnerar rotated, en Shape, vars koordinater är samma som instansens - fast roterad 90 grader åt höger
 * @return rotated, en Shape
 */
Shape Shape::rotate_right() const {
    Shape rotated;
    rotated.figure = this->figure;
    for(int i = 0; i < 4; i++){
        int x = this->getCoords()[i].y();
        int y = -this->getCoords()[i].x();
        rotated.coords[i] = QPoint(x, y);
    }
    return rotated;
}

/*!
 * Returnerar rotaded, en Shape, vars koordinater är samma som instansens - fast roterad 90 grader åt vänster
 * @return rotated, en Shape
 */
Shape Shape::rotate_left() const {
    Shape rotated;
    rotated.figure = this->figure;
    for(int i = 0; i < 4; i++){
        int x = -this->getCoords()[i].y();
        int y = this->getCoords()[i].x();
        rotated.coords[i] = QPoint(x, y);
    }
    return rotated;
}