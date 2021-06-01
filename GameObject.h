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
    glm::vec3 leftTrackPos;
    glm::vec3 rightTrackPos;
    float velocity;
    float maxVelocity = 0.5;

    float leftVelocity = 0;
    float rightVelocity = 0;

    float getLeftVelocity() const;

    void setLeftVelocity(float leftVelocity);

    float getRightVelocity() const;

    void setRightVelocity(float rightVelocity);

    glm::vec3 color;
    glm::vec3 lightColor;
    glm::vec3 rotation;
    glm::vec3 front;

    Model model;

    virtual void draw(Shader &shader);

    GameObject(const glm::vec3 &position, const float &velocity, const glm::vec3 &color,
               const glm::vec3 &lightColor, glm::vec3 rotation, string path);

    void updateFrontVec();

    void goForward(float multiplier);

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    const float &getVelocity() const;

    void setVelocity(const float velocity);

    const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);

    const glm::vec3 &getLightColor() const;

    void setLightColor(const glm::vec3 &lightColor);

    const glm::vec3 &getRotation() const;

    void setRotation(const glm::vec3 &rotation);

    const Model &getModel() const;

    void setModel(const Model &model);

    void updatePos();

    void updateRotation();
};


#endif //MARSROVER_GAMEOBJECT_H
