//
// Created by musiek on 21.06.2021.
//

#ifndef MARSROVER_STATICOBJECT_H
#define MARSROVER_STATICOBJECT_H


#include <vec3.hpp>
#include "Model.h"
#include "CircleHitbox.h"

class StaticObject {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 color;
    glm::vec3 lightColor;

    CircleHitbox hitbox;

    Model model;

    virtual void draw(Shader &shader);

    StaticObject(const vec3 &position, const vec3 &rotation, const vec3 &color, const vec3 &lightColor, string path, float radius);
};


#endif //MARSROVER_STATICOBJECT_H
