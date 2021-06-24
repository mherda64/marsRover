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

    modelMat = glm::rotate(modelMat, glm::radians(rotation.y), glm::vec3(0,1,0));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.x), glm::vec3(1,0,0));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.z), glm::vec3(0,0,1));



    modelMat = glm::scale(modelMat, glm::vec3(1,1,1));

    shader.setMat4("model", modelMat);

    model.draw(shader);

}

Rover::Rover(const glm::vec3 &position, const float &velocity, const glm::vec3 &color,
                       const glm::vec3 &lightColor, glm::vec3 rotation, string path, HeightMap* heightMap, float radius) : position(position),
                                                                                          velocity(velocity),
                                                                                          color(color),
                                                                                          lightColor(lightColor),
                                                                                          rotation(rotation), model(path),
                                                                                          heightMap(heightMap),
                                                                                          hitbox(radius, &this->position){
    // Uncomment to auto radius hitbox
//    this->hitbox.radius = hitbox.approximateRadius(&model);

    leftTrackPos = model.getOrigin("Left_Middle_Wheel_Cylinder.001") + position;
    rightTrackPos = model.getOrigin("Right_Middle_Wheel_Cylinder.007") + position;

    this->position.x = (leftTrackPos.x + rightTrackPos.x) / 2;
    this->position.y = (leftTrackPos.y + rightTrackPos.y) / 2;
    this->position.z = (leftTrackPos.z + rightTrackPos.z) / 2;

    front = glm::vec3(-1,0,0);


    distBetweenWheelsX = (model.getOrigin("Left_Back_Wheel_Cylinder.008") - model.getOrigin("Left_Middle_Wheel_Cylinder.001")).x;
    distBetweenWheelsZ =(model.getOrigin("Left_Middle_Wheel_Cylinder.001") - model.getOrigin("Right_Middle_Wheel_Cylinder.007")).z;
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

void Rover::updatePos() {

    if (checkCollisions()) {
        leftVelocity = -leftVelocity;
        rightVelocity = -rightVelocity;
    }

    if (leftVelocity != 0 || rightVelocity != 0) {

        glm::vec3 leftTrackVector = front * leftVelocity;
        glm::vec3 rightTrackVector = front * rightVelocity;

        glm::vec3 rightVec = glm::cross(front, glm::vec3(0,1,0));
        leftTrackPos = -rightVec * (distBetweenWheelsZ / 2) + position;
        rightTrackPos = rightVec * (distBetweenWheelsZ / 2) + position;

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

        updateRotation();

        updateWheelPositions();

        float leftFrontHeight = heightMap->getHeight(glm::vec2(leftFrontWheelPos.x, leftFrontWheelPos.z));
        float rightFrontHeight = heightMap->getHeight(glm::vec2(rightFrontWheelPos.x, rightFrontWheelPos.z));

        float leftBackHeight = heightMap->getHeight(glm::vec2(leftBackWheelPos.x, leftBackWheelPos.z));
        float rightBackHeight = heightMap->getHeight(glm::vec2(rightBackWheelPos.x, rightBackWheelPos.z));

        position.y = (leftFrontHeight + rightFrontHeight + leftBackHeight + rightBackHeight) / 4;


        float leftPitch = rotation.z;
        float rightPitch = rotation.z;

        if (leftFrontHeight > leftBackHeight)
        {
            if (position.y < leftFrontHeight)
                leftPitch = -glm::degrees(atan((leftFrontHeight - leftBackHeight) / (distBetweenWheelsX * 2)));
            else leftPitch = 0.f;
        }
        else if (leftBackHeight > leftFrontHeight)
        {
            if (position.y < leftBackHeight)
                leftPitch = -glm::degrees(atan((leftFrontHeight - leftBackHeight) / (distBetweenWheelsX * 2)));
            else leftPitch = 0.f;
        }
        else leftPitch = 0.f;

        if (rightFrontHeight > rightBackHeight)
        {
            if (position.y < rightFrontHeight)
                rightPitch = -glm::degrees(atan((rightFrontHeight - rightBackHeight) / (distBetweenWheelsX * 2)));
            else rightPitch = 0.f;
        }
        else if (rightBackHeight > rightFrontHeight)
        {
            if (position.y < rightBackHeight)
                rightPitch = -glm::degrees(atan((rightFrontHeight - rightBackHeight) / (distBetweenWheelsX * 2)));
            else rightPitch = 0.f;
        }
        else rightPitch = 0.f;

        rotation.z = (leftPitch + rightPitch) / 2;

        float frontRoll = rotation.x;
        float backRoll = rotation.x;

        if (leftFrontHeight > rightFrontHeight)
        {
            if (position.y < leftFrontHeight)
                frontRoll = -glm::degrees(atan((leftFrontHeight - rightFrontHeight) / distBetweenWheelsZ));
            else frontRoll = 0.f;
        }
        else if (rightFrontHeight > leftFrontHeight)
        {
            if (position.y < rightFrontHeight)
                frontRoll = -glm::degrees(atan((leftFrontHeight - rightFrontHeight) / distBetweenWheelsZ));
            else frontRoll = 0.f;
        }
        else frontRoll = 0.f;

        if (leftBackHeight > rightBackHeight)
        {
            if (position.y < leftBackHeight)
                backRoll = -glm::degrees(atan((leftBackHeight - rightBackHeight) / distBetweenWheelsZ));
            else backRoll = 0.f;
        }
        else if (rightBackHeight > leftBackHeight)
        {
            if (position.y < rightBackHeight)
                backRoll = -glm::degrees(atan((leftBackHeight - rightBackHeight) / distBetweenWheelsZ));
            else backRoll = 0.f;
        }
        else backRoll = 0.f;

        rotation.x = (frontRoll + backRoll) / 2;

        if (abs(rotation.x) < 1) rotation.x = 0;
        if (abs(rotation.z) < 1) rotation.z = 0;
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

void Rover::updateWheelPositions() {
    leftFrontWheelPos = leftTrackPos + front * distBetweenWheelsX;
    leftBackWheelPos = leftTrackPos - front * distBetweenWheelsX;

    rightFrontWheelPos = rightTrackPos + front * distBetweenWheelsX;
    rightBackWheelPos = rightTrackPos - front * distBetweenWheelsX;
}

void Rover::addStaticObject(StaticObject *objPtr) {
    staticObjects.push_back(objPtr);
}

bool Rover::checkCollisions() {
    for (StaticObject* obj : staticObjects) {
        if (this->hitbox.collides(&obj->hitbox)) {
//            cout << "KOLIZJA" << "\n";
            return true;
        }
    }
    return false;
}

