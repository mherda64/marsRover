//
// Created by musiek on 26.04.2021.
//

#ifndef MARSROVER_BODY_H
#define MARSROVER_BODY_H


#include "SceneObject.h"

/**
 * Class representing a simple body of the rover.
 * Body can be adjusted by setting the width, length and height.
 * Extends SceneObject.
 */
class Body : public SceneObject {
public:
    /**
     * Width of the body.
     */
    GLdouble width;

    /**
     * Length of the body.
     */
    GLdouble length;

    /**
     * Height of the body.
     */
    GLdouble height;

    /**
     * Body of the rover.
     * @param position Position of the body.
     * @param rotation Rotation of the body.
     * @param width Width of the body.
     * @param length Length of the body.
     * @param height Height of the body.
     */
    Body(const Point &position, const Rotation &rotation, GLdouble width, GLdouble length, GLdouble height);

    void draw() override;
};


#endif //MARSROVER_BODY_H
