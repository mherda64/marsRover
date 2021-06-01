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

GameObject::GameObject(const glm::vec3 &position, const float &velocity, const glm::vec3 &color,
                       const glm::vec3 &lightColor, glm::vec3 rotation, string path) : position(position),
                                                                                          velocity(velocity),
                                                                                          color(color),
                                                                                          lightColor(lightColor),
                                                                                          rotation(rotation), model(path) {
    leftTrackPos = model.getLeftMiddleWheelOrigin() + position;
    rightTrackPos = model.getRightMiddleWheelOrigin() + position;

    this->position.x = (leftTrackPos.x + rightTrackPos.x) / 2;
    this->position.y = (leftTrackPos.y + rightTrackPos.y) / 2;
    this->position.z = (leftTrackPos.z + rightTrackPos.z) / 2;

    front = glm::vec3(-1,0,0);
}

const glm::vec3 &GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(const glm::vec3 &position) {
    GameObject::position = position;
}

const float &GameObject::getVelocity() const {
    return velocity;
}

void GameObject::setVelocity(const float velocity) {
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

void GameObject::goForward(float velocity) {
    if (this->velocity <= maxVelocity && this->velocity >= -maxVelocity)
        this->velocity += velocity;
}

void GameObject::updatePos() {
//    position += front * velocity;
//    velocity = 0.8 * velocity;
//    cout << velocity << "\n";
//    if (velocity < 0.05 && velocity > -0.05) velocity = 0;

// Potem
//    position.x = (leftTrackPos.x + rightTrackPos.x) / 2;
//    position.y = (leftTrackPos.y + rightTrackPos.y) / 2;
//    position.z = (leftTrackPos.z + rightTrackPos.z) / 2;

    if (leftVelocity == 0 && rightVelocity == 0) {

    } else {
//        front = glm::cross(position, glm::vec3(0,1,0));
//        front = glm::normalize(front);
//
//        position += front * 0.1f;


        leftVelocity *= 0.5;
        rightVelocity *= 0.5;

        glm::vec3 leftTrackVector = front * leftVelocity;
        glm::vec3 rightTrackVector = front * rightVelocity;

        leftTrackPos += leftTrackVector;
        rightTrackPos += rightTrackVector;

        glm::vec3 diffVector;

        if (leftVelocity > rightVelocity) {
            diffVector = leftTrackPos - rightTrackPos;
            front = glm::cross(diffVector, glm::vec3(0,1,0));
            front = glm::normalize(front);
        } else if (leftVelocity < rightVelocity) {
            diffVector = rightTrackPos - leftTrackPos;
            front = - glm::cross(diffVector, glm::vec3(0,1,0));
            front = glm::normalize(front);
        }

        // Calculate new position
        this->position.x = (leftTrackPos.x + rightTrackPos.x) / 2;
        this->position.y = (leftTrackPos.y + rightTrackPos.y) / 2;
        this->position.z = (leftTrackPos.z + rightTrackPos.z) / 2;

        //update velocity
        leftVelocity *= 0.9;
        rightVelocity *= 0.9;

        if (leftVelocity < 0.05 && leftVelocity > -0.05)
            leftVelocity = 0;

        if (rightVelocity < 0.05 && rightVelocity > -0.05)
            rightVelocity = 0;

        updateRotation();
        cout << front.x << ":" << front.z << ":" << rotation.y << "\n\n";

//        cout << position.x << ":" << position.y << ":" << position.z << "\n";
//        cout << front.x << ":" << front.y << ":" << front.z << "\n\n";
    }


}

float GameObject::getLeftVelocity() const {
    return leftVelocity;
}

void GameObject::setLeftVelocity(float leftVelocity) {
    GameObject::leftVelocity = leftVelocity;
}

float GameObject::getRightVelocity() const {
    return rightVelocity;
}

void GameObject::setRightVelocity(float rightVelocity) {
    GameObject::rightVelocity = rightVelocity;
}

void GameObject::updateRotation() {
    glm::vec3 orig(-1, 0,0);
    if (front.z > 0)
        rotation.y = glm::degrees(acos(glm::dot(orig, front) / ( glm::length(orig) * glm::length(front))));
    else
        rotation.y = glm::degrees(-acos(glm::dot(orig, front) / ( glm::length(orig) * glm::length(front))));
}
