//
// Created by musiek on 21.06.2021.
//

#ifndef MARSROVER_CIRCLEHITBOX_H
#define MARSROVER_CIRCLEHITBOX_H


#include <vec3.hpp>
#include "Model.h"

class CircleHitbox {
public:
    float radius;
    glm::vec3 *position;

    CircleHitbox(float radius, glm::vec3 *position);

    bool collides(CircleHitbox* otherHitbox);

    static float approximateRadius(Model* model);
};


#endif //MARSROVER_CIRCLEHITBOX_H
