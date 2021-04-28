//
// Created by musiek on 4/16/21.
//

#include "Wheel.h"

Wheel::Wheel(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot, GLdouble r,
             GLdouble width, GLdouble valueOverFloor) : SceneObject(x, y, z, xRot, yRot, zRot), r(r), width(width), valueOverFloor(valueOverFloor) {
    this->position.y += valueOverFloor;
}


Wheel::Wheel(const Point &position, const Rotation &rotation, GLdouble r, GLdouble width, GLdouble valueOverFloor) : SceneObject(position,
                                                                                                        rotation), r(r),
                                                                                            width(width),valueOverFloor(valueOverFloor) {
    this->position.y += valueOverFloor;
}

void Wheel::draw() {
    glPushMatrix();

    //Translation and rotation of a single wheel
    glTranslatef(position.x, position.y, position.z);

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);


    double xTmp, yTmp, alpha, PI = 3.14;
    double currentH;

    //drawing bottom basis of the cylinder
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(0, 0, 0);
    glColor3d(0, 1, 0);
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0)
    {
        xTmp = r*sin(alpha);
        yTmp = r*cos(alpha);
        glVertex3d( xTmp,  yTmp, 0);
    }
    glVertex3d(0, r, 0);
    glEnd();


    //drawing side walls of the cylinder
    double colorStep = 0;
    double hMax = width / 10;
    for (currentH = 0; currentH < width; currentH += hMax) {
        glBegin(GL_TRIANGLE_STRIP);
        for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 20.0)
        {
            xTmp = r*sin(alpha);
            yTmp = r* cos(alpha);
            glColor3d(0, 1 - colorStep, colorStep);
            glVertex3d(xTmp, yTmp, currentH);
            glColor3d(0, 1 - (colorStep + 1.0 / (width / hMax)), colorStep + 1.0 / (width / hMax));
            glVertex3d(xTmp, yTmp, currentH + hMax);
        }
        xTmp = r*sin(0);
        yTmp = r* cos(0);
        glColor3d(0, 1 - colorStep, colorStep);
        glVertex3d(xTmp, yTmp, currentH);
        glColor3d(0, 1 - (colorStep + 1.0 / hMax), colorStep + 1.0 / hMax);
        glVertex3d(xTmp, yTmp, currentH + hMax);

        colorStep += 1.0 / (width / hMax);
        glEnd();
    }

    //drawing top basis of the cylinder
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(0, 0, width);
    glColor3d(0, 0.0, 1);
    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 20.0)
    {
        xTmp = r*sin(alpha);
        yTmp = r*cos(alpha);
        glVertex3d(xTmp, yTmp, width);
    }
    glVertex3d(0, r, width);
    glEnd();

    glPopMatrix();
}


