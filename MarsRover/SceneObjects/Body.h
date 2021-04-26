//
// Created by musiek on 26.04.2021.
//

#ifndef MARSROVER_BODY_H
#define MARSROVER_BODY_H


#include "SceneObject.h"

class Body : public SceneObject {
public:
    GLdouble width;
    GLdouble length;
    GLdouble height;

    Body(const Point &position, const Rotation &rotation, GLdouble width, GLdouble length, GLdouble height);

    void draw() override;
};


#endif //MARSROVER_BODY_H
