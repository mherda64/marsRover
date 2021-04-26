//
// Created by musiek on 26.04.2021.
//

#ifndef MARSROVER_SUSPENSIONBAR_H
#define MARSROVER_SUSPENSIONBAR_H


#include "../BasicStructures/Point.h"
#include "SceneObject.h"
#include "cmath"

class SuspensionBar : public SceneObject {
public:
    Point beginningPoint;
    Point endPoint;

    GLdouble radius;

    SuspensionBar(const Point &position, const Rotation &rotation, const Point &beginningPoint, const Point &endPoint,
                  GLdouble radius);

    void draw()     override;

};


#endif //MARSROVER_SUSPENSIONBAR_H
