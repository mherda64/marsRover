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

    //Translation and rotation of the single bar
    glTranslatef(position.x, position.y, position.z);

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);

    double xTmp, yTmp, alpha, PI = 3.14;

    //calculating the distance between beginning and end point in the z axis.
    double distance = abs(beginningPoint.z - endPoint.z);

    //drawing bottom basis of the bar
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

    //creating temporary variables for the current position of the drawing point
    double currentX = beginningPoint.x;
    double currentY = beginningPoint.y;
    double currentZ = beginningPoint.z;

    //calculating step in each axis that the drawing point is going to pass
    double xStep = endPoint.x / 10;
    double yStep = endPoint.y / 10;
    double zStep = endPoint.z / 10;

    //drawing side walls of the bar between beginning and end points
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

        //moving the drawing point
        currentX += xStep;
        currentY += yStep;
        currentZ += zStep;
    }

    //drawing the top basis of the bar
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