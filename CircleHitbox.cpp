//
// Created by musiek on 21.06.2021.
//

#include <iostream>
#include "CircleHitbox.h"

using namespace std;

bool CircleHitbox::collides(CircleHitbox *otherHitbox) {
    float dist = glm::length((*position - *otherHitbox->position));

//    cout << "dist:" << dist << "\n";

    if (dist < (this->radius + otherHitbox->radius)) {
        return true;
    }
    return false;
}

CircleHitbox::CircleHitbox(float radius, glm::vec3 *position) : radius(radius), position(
        const_cast<glm::vec3 *>(position)) {}

float CircleHitbox::approximateRadius(Model *model) {
    glm::vec3 maxVex = model->getMaxVec();
    glm::vec3 minVec = model->getMinVec();

    glm::vec3 tmp = maxVex - minVec;

    float radius = glm::length(tmp) / 2.0f;
    return radius;
}
