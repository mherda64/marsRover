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
                                          zRot), wheelDist(wheelDist)
                                          {
    wheels[0] = new Wheel(x, y, z - wheelDist / 2, 0, 0, 0, 10, 5);
    wheels[1] = new Wheel(x, y, z + wheelDist / 2,  0, 0, 0, 10, 5);
    wheels[2] = new Wheel(x + 20, y, z - wheelDist / 2,  0, 0, 0, 10, 5);
    wheels[3] = new Wheel(x + 20, y, z + wheelDist / 2, 0, 0, 0, 10, 5);
    wheels[4] = new Wheel(x - 20, y, z - wheelDist / 2,  0, 0, 0, 10, 5);
    wheels[5] = new Wheel(x - 20, y, z + wheelDist / 2,  0, 0, 0, 10, 5);
}

void Rover::draw() {
    glPushMatrix();

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glRotatef(zRot, 0, 0, 1);

    glTranslatef(x, y, z);

    for (int i = 0; i < 6; i++) {
        wheels[i]->draw();
    }

    glPopMatrix();
}

Rover::~Rover() {
    for (int i = 0; i < 6; i++) {
        delete wheels[i];
    }
}
