//
// Created by musiek on 26.04.2021.
//

#include "SuspensionBar.h"



SuspensionBar::SuspensionBar(const Rotation &rotation, const Point &beginningPoint,
                             const Point &endPoint, GLdouble radius) : SceneObject(beginningPoint, rotation),
                                                                       beginningPoint(beginningPoint),
                                                                       endPoint(endPoint), radius(radius) {}

void SuspensionBar::draw() {
    glPushMatrix();

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);

    glTranslatef(position.x, position.y, position.z);

    double xTmp, yTmp, alpha, PI = 3.14;
    double currentH;

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


//    double hMax = distance / 10;
//    for (currentH = position.z; currentH < position.z + width; currentH += hMax) {
//        glBegin(GL_TRIANGLE_STRIP);
//        for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 20.0)
//        {
//            xTmp = r*sin(alpha);
//            yTmp = r* cos(alpha);
//            glColor3d(0, 1 - colorStep, colorStep);
//            glVertex3d(position.x + xTmp, position.y + yTmp, currentH);
//            glColor3d(0, 1 - (colorStep + 1.0 / (width / hMax)), colorStep + 1.0 / (width / hMax));
//            glVertex3d(position.x + xTmp, position.y + yTmp, currentH + hMax);
//        }
//        xTmp = r*sin(0);
//        yTmp = r* cos(0);
//        glColor3d(0, 1 - colorStep, colorStep);
//        glVertex3d(position.x + xTmp, position.y + yTmp, currentH);
//        glColor3d(0, 1 - (colorStep + 1.0 / hMax), colorStep + 1.0 / hMax);
//        glVertex3d(position.x + xTmp, position.y + yTmp, currentH + hMax);
//
//        colorStep += 1.0 / (width / hMax);
//        glEnd();
//    }
//
//    glBegin(GL_TRIANGLE_FAN);
//    glColor3d(1, 0.0, 0);
//    glVertex3d(position.x, position.y, position.z + width);
//    glColor3d(0, 0.0, 1);
//    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 20.0)
//    {
//        xTmp = r*sin(alpha);
//        yTmp = r*cos(alpha);
//        glVertex3d(position.x + xTmp, position.y + yTmp, position.z + width);
//    }
//    glVertex3d(position.x, position.y + r, position.z + width);
//    glEnd();

}