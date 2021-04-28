//
// Created by musiek on 27.04.2021.
//

#ifndef MARSROVER_TURRETBASE_H
#define MARSROVER_TURRETBASE_H

#include "cmath"
#include "SceneObject.h"

/**
 * Class representing a turret base - cone like base that holds the turret barrel.
 * Extends SceneObject.
 */
class TurretBase : public SceneObject {
public:
    /**
     * Top radius of the base.
     */
    GLdouble topRadius;

    /**
     * Bottom radius of the base.
     */
    GLdouble bottomRadius;

    /**
     * Height of the base.
     */
    GLdouble height;

    /**
     * Constructor of the TurretBase class.
     * @param position Position of the base.
     * @param rotation Rotation of the base.
     * @param topRadius Top radius of the base.
     * @param bottomRadius Bottom radius of the base.
     * @param height Height of the base.w
     */
    TurretBase(const Point &position, const Rotation &rotation, GLdouble topRadius, GLdouble bottomRadius, GLdouble height);

    void draw() override;

};


#endif //MARSROVER_TURRETBASE_H
