//
// Created by musiek on 4/16/21.
//

#include "Wheel.h"

Wheel::Wheel(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot, GLdouble r,
             GLdouble width) : SceneObject(x, y, z, xRot, yRot, zRot), r(r), width(width) {}

void Wheel::draw() {
    glPushMatrix();

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glRotatef(zRot, 0, 0, 1);

    glTranslatef(x, y, z);


    double xTmp, yTmp, alpha, PI = 3.14;
    double currentH;

    //rysowanie dolnej podstawy
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(x, y, z);
    glColor3d(0, 1, 0);
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0)
    {
        xTmp = r*sin(alpha);
        yTmp = r*cos(alpha);
        glVertex3d(x + xTmp, y + yTmp, z);
    }
    glVertex3d(x, y + r, z);
    glEnd();


    double colorStep = 0;
    double hMax = width / 10;
    for (currentH = z; currentH < z + width; currentH += hMax) {
        glBegin(GL_TRIANGLE_STRIP);
        for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 20.0)
        {
            xTmp = r*sin(alpha);
            yTmp = r* cos(alpha);
            glColor3d(0, 1 - colorStep, colorStep);
            glVertex3d(x + xTmp, y + yTmp, currentH);
            glColor3d(0, 1 - (colorStep + 1.0 / (width / hMax)), colorStep + 1.0 / (width / hMax));
            glVertex3d(x + xTmp, y + yTmp, currentH + hMax);
        }
        xTmp = r*sin(0);
        yTmp = r* cos(0);
        glColor3d(0, 1 - colorStep, colorStep);
        glVertex3d(x + xTmp, y + yTmp, currentH);
        glColor3d(0, 1 - (colorStep + 1.0 / hMax), colorStep + 1.0 / hMax);
        glVertex3d(x + xTmp, y + yTmp, currentH + hMax);

        colorStep += 1.0 / (width / hMax);
        glEnd();
    }

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(x, y, z + width);
    glColor3d(0, 0.0, 1);
    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 20.0)
    {
        xTmp = r*sin(alpha);
        yTmp = r*cos(alpha);
        glVertex3d(x + xTmp, y + yTmp, z + width);
    }
    glVertex3d(x, y + r, z + width);
    glEnd();

    glPopMatrix();
}

