//
// Created by musiek on 4/17/21.
//

#ifndef MARSROVER_ROVER_H
#define MARSROVER_ROVER_H


#include "SceneObject.h"

class Rover : public SceneObject {

public:
    Rover(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot);


    Rover(const Point &position, const Rotation &rotation, GLdouble wheelDist);

    void draw() override;
};


#endif //MARSROVER_ROVER_H
