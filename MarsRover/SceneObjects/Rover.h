//
// Created by musiek on 4/17/21.
//

#ifndef MARSROVER_ROVER_H
#define MARSROVER_ROVER_H


#include "SceneObject.h"
#include "Wheel.h"
#include "SuspensionBar.h"
#include "Body.h"
#include "TurretBase.h"
#include "Antenna.h"
#include "Afterburner.h"

/**
 * Class representing a whole rover object. It utilizes composition to create various parts of the rover,
 * together creating a whole vehicle.
 * Extends SceneObject.
 */
class Rover : public SceneObject {
private:
    /*
     * An array of pointers to all the 6 wheels of the rover.
     */
    Wheel* wheels[6];

    /**
     * An array of pointers to all the 6 suspension bars connecting wheels to the body.
     */
    SuspensionBar* suspensionBars[6];

    /**
     * Pointer to the rover's body.
     */
    Body* body;

    /**
     * Pointer to the rover's turret base.
     */
    TurretBase* turretBase;

    /**
     * Pointer to the rover's turret, created using already existing SuspensionBar class.
     */
    SuspensionBar* turret;

    /**
     * An array of antennas.
     */
    Antenna* antennas[2];

    Afterburner* afterburner;

public:
    /**
     * Distance between the rover's wheels.
     */
    GLdouble wheelDist;

    virtual ~Rover();


public:

    Rover(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot, GLdouble wheelDist);

    /**
     * Rover class constructor.
     * @param position Position of the rover.
     * @param rotation Rotation of the rover.
     * @param wheelDist Distance between the rover's wheels.
     */
    Rover(const Point &position, const Rotation &rotation, GLdouble wheelDist);

    void draw() override;
};


#endif //MARSROVER_ROVER_H
