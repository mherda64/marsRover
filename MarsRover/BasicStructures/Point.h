//
// Created by musiek on 26.04.2021.
//

#ifndef MARSROVER_POINT_H
#define MARSROVER_POINT_H


#include <GL/freeglut.h>

/**
 * Structure-like class representing a single point in 3d space.
 */
class Point {
public:
    /**
     * The x position
     */
    GLdouble x;

    /**
     * The y position
     */
    GLdouble y;

    /**
     * The z position
     */
    GLdouble z;

    Point(GLdouble x, GLdouble y, GLdouble z);
};


#endif //MARSROVER_POINT_H
