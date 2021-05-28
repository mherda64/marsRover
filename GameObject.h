//
// Created by musiek on 27.05.2021.
//

#ifndef MARSROVER_GAMEOBJECT_H
#define MARSROVER_GAMEOBJECT_H


#include <vec3.hpp>
#include "Model.h"

class GameObject {

public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 color;
    glm::vec3 lightColor;
    glm::vec3 rotation;
    glm::vec3 front;

    Model model;

    virtual void draw(Shader &shader);

    GameObject(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &color,
               const glm::vec3 &lightColor, glm::vec3 rotation, string path);

    void updateFrontVec();

    void goForward(float multiplier);

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getVelocity() const;

    void setVelocity(const glm::vec3 &velocity);

    const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);

    const glm::vec3 &getLightColor() const;

    void setLightColor(const glm::vec3 &lightColor);

    const glm::vec3 &getRotation() const;

    void setRotation(const glm::vec3 &rotation);

    const Model &getModel() const;

    void setModel(const Model &model);

};


#endif //MARSROVER_GAMEOBJECT_H
