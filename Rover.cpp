//
// Created by musiek on 27.05.2021.
//

#include <gtc/matrix_transform.hpp>
#include "Rover.h"

void Rover::draw(Shader &shader) {
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

Rover::Rover(const glm::vec3 &position, const float &velocity, const glm::vec3 &color,
                       const glm::vec3 &lightColor, glm::vec3 rotation, string path, HeightMap* heightMap) : position(position),
                                                                                          velocity(velocity),
                                                                                          color(color),
                                                                                          lightColor(lightColor),
                                                                                          rotation(rotation), model(path),
                                                                                          heightMap(heightMap){
    leftTrackPos = model.getLeftMiddleWheelOrigin() + position;
    rightTrackPos = model.getRightMiddleWheelOrigin() + position;

    this->position.x = (leftTrackPos.x + rightTrackPos.x) / 2;
    this->position.y = (leftTrackPos.y + rightTrackPos.y) / 2;
    this->position.z = (leftTrackPos.z + rightTrackPos.z) / 2;

    front = glm::vec3(-1,0,0);
}

const glm::vec3 &Rover::getPosition() const {
    return position;
}

void Rover::setPosition(const glm::vec3 &position) {
    Rover::position = position;
}

const float &Rover::getVelocity() const {
    return velocity;
}

void Rover::setVelocity(const float velocity) {
    Rover::velocity = velocity;
}

const glm::vec3 &Rover::getColor() const {
    return color;
}

void Rover::setColor(const glm::vec3 &color) {
    Rover::color = color;
}

const glm::vec3 &Rover::getLightColor() const {
    return lightColor;
}

void Rover::setLightColor(const glm::vec3 &lightColor) {
    Rover::lightColor = lightColor;
}

const glm::vec3 &Rover::getRotation() const {
    return rotation;
}

void Rover::setRotation(const glm::vec3 &rotation) {
    Rover::rotation = rotation;
}

const Model &Rover::getModel() const {
    return model;
}

void Rover::setModel(const Model &model) {
    Rover::model = model;
}

void Rover::updateFrontVec() {
    front.x = -cos(glm::radians(rotation.y));
    front.z = sin(glm::radians(rotation.y));

    front = glm::normalize(front);
}

void Rover::goForward(float velocity) {
    if (this->velocity <= maxVelocity && this->velocity >= -maxVelocity)
        this->velocity += velocity;
}

void Rover::updatePos() {
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


//        leftVelocity *= 0.5;
//        rightVelocity *= 0.5;

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

        if (leftVelocity < 0.01 && leftVelocity > -0.01)
            leftVelocity = 0;

        if (rightVelocity < 0.01 && rightVelocity > -0.01)
            rightVelocity = 0;

        this->position.y = heightMap->getHeight(glm::vec2(position.x, position.z));

        updateRotation();

//        cout << front.x << ":" << front.z << ":" << rotation.y << "\n\n";
        cout << leftVelocity << ":" << rightVelocity << "\n";
//        cout << position.x << ":" << position.y << ":" << position.z << "\n";
//        cout << front.x << ":" << front.y << ":" << front.z << "\n\n";
    }


}

float Rover::getLeftVelocity() const {
    return leftVelocity;
}

void Rover::setLeftVelocity(float leftVelocity) {
    if (abs(leftVelocity) < MAX_SPEED)
        Rover::leftVelocity = leftVelocity;
}

float Rover::getRightVelocity() const {
    return rightVelocity;
}

void Rover::setRightVelocity(float rightVelocity) {
    if (abs(rightVelocity) < MAX_SPEED)
        Rover::rightVelocity = rightVelocity;
}

void Rover::updateRotation() {
    glm::vec3 orig(-1, 0,0);
    if (front.z > 0)
        rotation.y = glm::degrees(acos(glm::dot(orig, front) / ( glm::length(orig) * glm::length(front))));
    else
        rotation.y = glm::degrees(-acos(glm::dot(orig, front) / ( glm::length(orig) * glm::length(front))));
}
