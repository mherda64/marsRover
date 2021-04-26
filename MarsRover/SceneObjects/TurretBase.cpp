//
// Created by musiek on 27.04.2021.
//

#include "TurretBase.h"

TurretBase::TurretBase(const Point &position, const Rotation &rotation, GLdouble topRadius, GLdouble bottomRadius, GLdouble height)
        : SceneObject(position, rotation), topRadius(topRadius), bottomRadius(bottomRadius), height(height) {}

void TurretBase::draw() {
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);

    double alpha, PI = 3.14;
    double zTmp, xTmp;

    //bottom
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(0, 0, 0);
    glColor3d(0, 1, 0);
    for (alpha = 2 * PI; alpha >= 0; alpha -= PI / 20.0)
    {
        xTmp = bottomRadius*sin(alpha);
        zTmp = bottomRadius*cos(alpha);
        glVertex3d(xTmp,0, zTmp);
    }
    glVertex3d(0, 0, bottomRadius);
    glEnd();

    //side
    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1, 0.0, 0);

    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0)
    {
        glColor3d(0, 1, 0);
        xTmp = topRadius*sin(alpha);
        zTmp = topRadius*cos(alpha);
        glVertex3d( xTmp, height, zTmp);

        glColor3d(1, 0.0, 0);
        xTmp = bottomRadius*sin(alpha);
        zTmp = bottomRadius*cos(alpha);
        glVertex3d( xTmp,  0, zTmp);
    }
    glColor3d(0, 1, 0);
    xTmp = topRadius*sin(alpha);
    zTmp = topRadius*cos(alpha);
    glVertex3d( xTmp, height, zTmp);
    glColor3d(1, 0.0, 0);
    xTmp = bottomRadius*sin(alpha);
    zTmp = bottomRadius*cos(alpha);
    glVertex3d( xTmp,  0, zTmp);

    glEnd();

    //top
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(0, height, 0);
    glColor3d(0, 1, 0);
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0)
    {
        xTmp = topRadius*sin(alpha);
        zTmp = topRadius*cos(alpha);
        glVertex3d( xTmp,height, zTmp);
    }
    glVertex3d(0, height, topRadius);
    glEnd();

    glPopMatrix();
}
