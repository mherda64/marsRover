//
// Created by musiek on 26.04.2021.
//

#include "SuspensionBar.h"



SuspensionBar::SuspensionBar(const Point &position, const Rotation &rotation, const Point &beginningPoint,
                             const Point &endPoint, GLdouble radius) : SceneObject(position, rotation),
                                                                       beginningPoint(beginningPoint),
                                                                       endPoint(endPoint), radius(radius) {}

void SuspensionBar::draw() {
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);



    double xTmp, yTmp, alpha, PI = 3.14;

    double distance = abs(beginningPoint.z - endPoint.z);

    //rysowanie dolnej podstawy
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(beginningPoint.x, beginningPoint.y, beginningPoint.z);
    glColor3d(0, 1, 0);
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0)
    {
        xTmp = radius*sin(alpha);
        yTmp = radius*cos(alpha);
        glVertex3d(beginningPoint.x + xTmp, beginningPoint.y + yTmp, beginningPoint.z);
    }
    glVertex3d(beginningPoint.x, beginningPoint.y + radius, beginningPoint.z);
    glEnd();

    double xStep = 1;
    double yStep = 1;
    double zStep = 1;
    double currentX = beginningPoint.x;
    double currentY = beginningPoint.y;
    double currentZ = beginningPoint.z;
    double currentPath = 0;

    double xDistance = endPoint.x;
    double yDistance = endPoint.y;
    double zDistance = endPoint.z;

    xStep = xDistance / 10;
    yStep = yDistance / 10;
    zStep = zDistance / 10;

    glColor3d(1, 0.0, 0);
    while (currentZ < endPoint.z) {
        glBegin(GL_TRIANGLE_STRIP);
        for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 20.0)
        {
            xTmp = radius*sin(alpha);
            yTmp = radius* cos(alpha);
            glVertex3d(currentX + xTmp, currentY + yTmp, currentZ);
            glVertex3d(currentX + xTmp + xStep, currentY + yTmp + yStep, currentZ + zStep);
        }
        xTmp = 0;
        yTmp = radius;
        glVertex3d(currentX + xTmp, currentY + yTmp, currentZ);
        glVertex3d(currentX + xTmp + xStep, currentY + yTmp + yStep, currentZ + zStep);

        glEnd();
        currentX += xStep;
        currentY += yStep;
        currentZ += zStep;
    }

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0, 0.0, 1);
    glVertex3d(currentX, currentY, currentZ);
    glColor3d(1, 0.0, 0);
    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 20.0)
    {
        xTmp = radius*sin(alpha);
        yTmp = radius*cos(alpha);
        glVertex3d(currentX + xTmp, currentY + yTmp, currentZ);
    }
    glVertex3d(currentX, currentY + radius, currentZ);
    glEnd();


    glPopMatrix();

}