//
// Created by musiek on 4/17/21.
//

#include "Rover.h"

Rover::Rover(GLdouble x,
             GLdouble y,
             GLdouble z,
             GLdouble xRot,
             GLdouble yRot,
             GLdouble zRot,
             GLdouble wheelDist) : SceneObject(x, y, z,
                                               xRot, yRot,
                                               zRot), wheelDist(wheelDist) {
    wheels[0] = new Wheel(0, 0, -wheelDist / 2, 0, 0, 0, 10, 5, 0);
    wheels[1] = new Wheel(0, 0, wheelDist / 2, 0, 180, 0, 10, 5, 0);
    wheels[2] = new Wheel(40, 0, -wheelDist / 2 - 10, 0, 0, 0, 10, 5, 0);
    wheels[3] = new Wheel(40, 0, wheelDist / 2 + 10, 180, 0, 0, 10, 5, 0);
    wheels[4] = new Wheel(-40, 0, -wheelDist / 2 - 10, 0, 0, 0, 10, 5, 0);
    wheels[5] = new Wheel(-40, 0, wheelDist / 2 + 10, 180, 0, 0, 10, 5, 0);

    suspensionBars[0] = new SuspensionBar(Point(wheels[0]->position.x,wheels[0]->position.y,wheels[0]->position.z + wheels[0]->width),
                                          Rotation(0, 0, 0),
                                          Point(0,0,0),
                                          Point(0,20 - wheels[0]->valueOverFloor,20), 3);

    suspensionBars[1] = new SuspensionBar(Point(wheels[1]->position.x,wheels[1]->position.y,wheels[1]->position.z - wheels[1]->width),
                                          Rotation(0, 180, 0),
                                          Point(0,0,0),
                                          Point(0,20 - wheels[1]->valueOverFloor,20), 3);

    suspensionBars[2] = new SuspensionBar(Point(wheels[2]->position.x,wheels[2]->position.y,wheels[2]->position.z + wheels[2]->width),
                                          Rotation(0, 0, 0),
                                          Point(0,0,0),
                                          Point(-20,20 - wheels[2]->valueOverFloor,30), 3);

    suspensionBars[3] = new SuspensionBar(Point(wheels[3]->position.x,wheels[3]->position.y,wheels[3]->position.z - wheels[3]->width),
                                          Rotation(0, 180, 0),
                                          Point(0,0,0),
                                          Point(+20,20 - wheels[3]->valueOverFloor,30), 3);

    suspensionBars[4] = new SuspensionBar(Point(wheels[4]->position.x,wheels[4]->position.y,wheels[4]->position.z + wheels[4]->width),
                                          Rotation(0, 0, 0),
                                          Point(0,0,0),
                                          Point(+20,20 - wheels[4]->valueOverFloor,30), 3);


    suspensionBars[5] = new SuspensionBar(Point(wheels[5]->position.x,wheels[5]->position.y,wheels[5]->position.z - wheels[5]->width),
                                          Rotation(0, 180, 0),
                                          Point(0,0,0),
                                          Point(-20,20 - wheels[5]->valueOverFloor,30), 3);

    body = new Body(Point(0,15,0), Rotation(0,0,0), 50, 80, 10);

    turretBase = new TurretBase(Point(0,25,0), Rotation(0,0,0), 10, 20, 10);

    turret = new SuspensionBar(Point(10,30,0), Rotation(0,90,0), Point(0,0,0), Point(0, 0, 50), 2);


    antennas[0] = new Antenna(Point(10, 40, 10),Rotation(0,0,0),0.5,1,100);
    antennas[1] = new Antenna(Point(10,40,-10),Rotation(0,0,0),0.5,1,200);

}

Rover::Rover(const Point &position, const Rotation &rotation, GLdouble wheelDist) : SceneObject(position, rotation),
                                                                                    wheelDist(wheelDist) {
    Rover(position.x, position.y, position.z, rotation.xRot, rotation.yRot, rotation.zRot, wheelDist);
}


void Rover::draw() {
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);


    for (int i = 0; i < 6; i++) {
        wheels[i]->draw();
        suspensionBars[i]->draw();
    }

    body->draw();
    turretBase->draw();
    turret->draw();

    for (int i = 0; i < sizeof(antennas)/sizeof(antennas[0]); i++) {
        antennas[i]->draw();
    }
    glPopMatrix();
}

Rover::~Rover() {
    for (int i = 0; i < 6; i++) {
        delete wheels[i];
        delete suspensionBars[i];
    }

    delete body;
    delete turretBase;
    delete turret;
}

