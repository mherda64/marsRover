//
// Created by musiek on 26.04.2021.
//

#ifndef MARSROVER_SUSPENSIONBAR_H
#define MARSROVER_SUSPENSIONBAR_H


#include "../BasicStructures/Point.h"
#include "SceneObject.h"
#include "cmath"

/**
 * Class representing a suspension bar - a piece of metal that connects the wheel with the rover's base.
 * The bar is created between two points.
 * Extends SceneObject.
 */
class SuspensionBar : public SceneObject {
public:
    /**
     * The beginning point of the bar
     */
    Point beginningPoint;

    /**
     * The end point of the bar
     */
    Point endPoint;

    /**
     * Radius of the bar
     */
    GLdouble radius;

    /**
     * Constructor of the SuspensionBar class.
     * @param position Position of the bar.
     * @param rotation Rotation of the bar.
     * @param beginningPoint Beginning point of the bar in the inertial frame or reference. The way this class was written,
     * you probably want to use Point(0,0,0), then later use position and rotation to move the bar.
     * @param endPoint End point of the bar in the inertial frame or reference. The way this class was written,
     * you probably want to use a Point that represents the bar's length in xyz, then move the bar later using position and rotation.
     * @param radius Radius of the bar.
     */
    SuspensionBar(const Point &position, const Rotation &rotation, const Point &beginningPoint, const Point &endPoint,
                  GLdouble radius);

    void draw()     override;

};


#endif //MARSROVER_SUSPENSIONBAR_H
