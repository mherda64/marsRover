//
// Created by musiek on 4/17/21.
//

#ifndef MARSROVER_ROVER_H
#define MARSROVER_ROVER_H


#include "SceneObject.h"
#include "Wheel.h"

//TODO keep wheel mount points in an array so it will be easier to draw rover's chassis in the future
//or even update each wheel's position depending on the terrain

class Rover : public SceneObject {
private:
    /*
     * An array of pointers to all the 6 wheels of the rover
     */
    Wheel* wheels[6];
public:
    /*
     * Distance between the wheels
     */
    GLdouble wheelDist;

    virtual ~Rover();


public:
    Rover(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot, GLdouble wheelDist);


    Rover(const Point &position, const Rotation &rotation, GLdouble wheelDist);

    void draw() override;
};


#endif //MARSROVER_ROVER_H
