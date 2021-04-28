//
// Created by musiek on 4/16/21.
//

#ifndef MARSROVER_SCENEOBJECT_H
#define MARSROVER_SCENEOBJECT_H

#include <GL/freeglut.h>
#include "../BasicStructures/Point.h"
#include "../BasicStructures/Rotation.h"
#include <cmath>

/**
 * Abstract class representing a single 3d object in a scene.
 * Used for creating various 3d objects, which should implement virtual draw() method.
 */
class SceneObject {
public:
    /**
     * Position of the object
     */
    Point position;

    /**
     * Rotation of the object
     */
    Rotation rotation;

    /**
     * Constant PI definition
     */
    const double PI = 3.14;

    /**
     * Constructor setting the position and rotation of the object
     * @param position
     * @param rotation
     */
    SceneObject(const Point &position, const Rotation &rotation);

    /**
     * Constructor that allows to create the object without using the Point and Rotation classes
     * @param x
     * @param y
     * @param z
     * @param xRot
     * @param yRot
     * @param zRot
     */
    SceneObject(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot);

    /**
     * Virtual method used for the object drawing.
     * Classes extending the SceneObject class should implement this method.
     */
    virtual void draw() = 0;

};


#endif //MARSROVER_SCENEOBJECT_H
