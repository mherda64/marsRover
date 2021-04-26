//
// Created by musiek on 4/16/21.
//

#include "Wheel.h"

Wheel::Wheel(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot, GLdouble r,
             GLdouble width) : SceneObject(x, y, z, xRot, yRot, zRot), r(r), width(width) {}


Wheel::Wheel(const Point &position, const Rotation &rotation, GLdouble r, GLdouble width) : SceneObject(position,
                                                                                                        rotation), r(r),
                                                                                            width(width) {}

void Wheel::draw() {
    glPushMatrix();

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);

    glTranslatef(position.x, position.y, position.z);


    double xTmp, yTmp, alpha, PI = 3.14;
    double currentH;

    //rysowanie dolnej podstawy
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(position.x, position.y, position.z);
    glColor3d(0, 1, 0);
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0)
    {
        xTmp = r*sin(alpha);
        yTmp = r*cos(alpha);
        glVertex3d(position.x + xTmp, position.y + yTmp, position.z);
    }
    glVertex3d(position.x, position.y + r, position.z);
    glEnd();


    double colorStep = 0;
    double hMax = width / 10;
    for (currentH = position.z; currentH < position.z + width; currentH += hMax) {
        glBegin(GL_TRIANGLE_STRIP);
        for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 20.0)
        {
            xTmp = r*sin(alpha);
            yTmp = r* cos(alpha);
            glColor3d(0, 1 - colorStep, colorStep);
            glVertex3d(position.x + xTmp, position.y + yTmp, currentH);
            glColor3d(0, 1 - (colorStep + 1.0 / (width / hMax)), colorStep + 1.0 / (width / hMax));
            glVertex3d(position.x + xTmp, position.y + yTmp, currentH + hMax);
        }
        xTmp = r*sin(0);
        yTmp = r* cos(0);
        glColor3d(0, 1 - colorStep, colorStep);
        glVertex3d(position.x + xTmp, position.y + yTmp, currentH);
        glColor3d(0, 1 - (colorStep + 1.0 / hMax), colorStep + 1.0 / hMax);
        glVertex3d(position.x + xTmp, position.y + yTmp, currentH + hMax);

        colorStep += 1.0 / (width / hMax);
        glEnd();
    }

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(position.x, position.y, position.z + width);
    glColor3d(0, 0.0, 1);
    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 20.0)
    {
        xTmp = r*sin(alpha);
        yTmp = r*cos(alpha);
        glVertex3d(position.x + xTmp, position.y + yTmp, position.z + width);
    }
    glVertex3d(position.x, position.y + r, position.z + width);
    glEnd();

    glPopMatrix();
}


