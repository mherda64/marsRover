//
// Created by musiek on 27.05.2021.
//

#ifndef MARSROVER_ROVER_H
#define MARSROVER_ROVER_H


#include <vec3.hpp>
#include "Model.h"
#include "HeightMap.h"
#include "CircleHitbox.h"
#include "StaticObject.h"

#define MAX_SPEED 2

class Rover {
public:
    // Wskaźnik na heightmapę z obiektu Terrain
    HeightMap* heightMap;
    // Wszystkie obiekty, z którymi będzie kolidował łazik
    vector<StaticObject*> staticObjects;

    // Pozycja łazika oraz jego gąsienic
    glm::vec3 position;
    glm::vec3 leftTrackPos;
    glm::vec3 rightTrackPos;

    // Pozycje skrajnych kół łazika
    glm::vec3 leftFrontWheelPos;
    glm::vec3 rightFrontWheelPos;
    glm::vec3 leftBackWheelPos;
    glm::vec3 rightBackWheelPos;

    // Dystans pomiędzy kołami w osi X oraz Z
    float distBetweenWheelsX;
    float distBetweenWheelsZ;

    // Aktualna prędkość łazika
    float velocity;

    // Prędkość łazika na każdej z gąsienic
    float leftVelocity = 0;
    float rightVelocity = 0;

    // Dane dotyczące położenia łazika w przestrzeni oraz jego koloru
    glm::vec3 color;
    glm::vec3 lightColor;
    glm::vec3 rotation;
    glm::vec3 front;

    // Model łazika
    Model model;
    // Hitbox łazika
    CircleHitbox hitbox;

    Rover(const glm::vec3 &position, const float &velocity, const glm::vec3 &color,
          const glm::vec3 &lightColor, glm::vec3 rotation, string path, HeightMap* heightMap, float radius);

    virtual void draw(Shader &shader);
    void addStaticObject(StaticObject* objPtr);
    bool checkCollisions();

    void updatePos();
    void updateRotation();
    void updateWheelPositions();

    float getLeftVelocity() const;

    void setLeftVelocity(float leftVelocity);

    float getRightVelocity() const;

    void setRightVelocity(float rightVelocity);

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

};


#endif //MARSROVER_ROVER_H
