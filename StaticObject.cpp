//
// Created by musiek on 21.06.2021.
//

#include <gtc/matrix_transform.hpp>
#include "StaticObject.h"

StaticObject::StaticObject(const vec3 &position, const vec3 &rotation, const vec3 &color, const vec3 &lightColor, const vec3 &scale, string path, float radius) : position(position),
                                                                                                 rotation(rotation),
                                                                                                 lightColor(lightColor),
                                                                                                 model(path),
                                                                                                 color(color),
                                                                                                 scale(scale),
                                                                                                 hitbox(radius, &this->position){
    // Uncomment for auto hitbox radius
//    this->hitbox.radius = hitbox.approximateRadius(&model);
}

void StaticObject::draw(Shader &shader) {
    shader.use();
    shader.setVec3("objectColor", color);
    shader.setVec3("lightColor",  lightColor);

    // world transformation
    glm::mat4 modelMat = glm::mat4(1.0f);

    modelMat = glm::translate(modelMat, position);

    modelMat = glm::rotate(modelMat, glm::radians(rotation.y), glm::vec3(0,1,0));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.x), glm::vec3(1,0,0));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.z), glm::vec3(0,0,1));

    modelMat = glm::scale(modelMat, scale);

    shader.setMat4("model", modelMat);

    model.draw(shader);
}
