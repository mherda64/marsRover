//
// Created by musiek on 27.05.2021.
//

#include <gtc/matrix_transform.hpp>
#include "GameObject.h"

void GameObject::draw(Shader &shader) {
    // be sure to activate shader when setting uniforms/drawing objects
    shader.use();
    shader.setVec3("objectColor", color);
    shader.setVec3("lightColor",  lightColor);

    // world transformation
    glm::mat4 modelMat = glm::mat4(1.0f);

    modelMat = glm::translate(modelMat, position);

    modelMat = glm::rotate(modelMat, glm::radians(rotation.x), glm::vec3(1,0,0));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.y), glm::vec3(0,1,0));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.z), glm::vec3(0,0,1));

    modelMat = glm::scale(modelMat, glm::vec3(1,1,1));

    shader.setMat4("model", modelMat);

    model.draw(shader);

}

GameObject::GameObject(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &color,
                       const glm::vec3 &lightColor, glm::vec3 rotation, string path) : position(position),
                                                                                          velocity(velocity),
                                                                                          color(color),
                                                                                          lightColor(lightColor),
                                                                                          rotation(rotation), model(path) {}

const glm::vec3 &GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(const glm::vec3 &position) {
    GameObject::position = position;
}

const glm::vec3 &GameObject::getVelocity() const {
    return velocity;
}

void GameObject::setVelocity(const glm::vec3 &velocity) {
    GameObject::velocity = velocity;
}

const glm::vec3 &GameObject::getColor() const {
    return color;
}

void GameObject::setColor(const glm::vec3 &color) {
    GameObject::color = color;
}

const glm::vec3 &GameObject::getLightColor() const {
    return lightColor;
}

void GameObject::setLightColor(const glm::vec3 &lightColor) {
    GameObject::lightColor = lightColor;
}

const glm::vec3 &GameObject::getRotation() const {
    return rotation;
}

void GameObject::setRotation(const glm::vec3 &rotation) {
    GameObject::rotation = rotation;
}

const Model &GameObject::getModel() const {
    return model;
}

void GameObject::setModel(const Model &model) {
    GameObject::model = model;
}

void GameObject::updateFrontVec() {
    front.x = -cos(glm::radians(rotation.y));
    front.z = sin(glm::radians(rotation.y));

    front = glm::normalize(front);
}

void GameObject::goForward(float multiplier) {
    position -= front * multiplier;
}
