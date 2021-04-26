//
// Created by musiek on 27.04.2021.
//

#ifndef MARSROVER_TURRETBASE_H
#define MARSROVER_TURRETBASE_H

#include "cmath"
#include "SceneObject.h"

class TurretBase : public SceneObject {
public:
    GLdouble topRadius;
    GLdouble bottomRadius;
    GLdouble height;

    TurretBase(const Point &position, const Rotation &rotation, GLdouble topRadius, GLdouble bottomRadius, GLdouble height);

    void draw() override;

};


#endif //MARSROVER_TURRETBASE_H
