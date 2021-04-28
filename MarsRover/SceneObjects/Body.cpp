//
// Created by musiek on 26.04.2021.
//

#include "Body.h"

Body::Body(const Point &position, const Rotation &rotation, GLdouble width, GLdouble length, GLdouble height)
        : SceneObject(position, rotation), width(width), length(length), height(height) {}

void Body::draw() {
    glPushMatrix();

    //translation and rotation of a single rover body
    glTranslatef(position.x, position.y, position.z);

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);

    //bottom face
    glColor3d(0.9, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(-length /2 , 0, width / 2);
    glVertex3d(-length /2 , 0, -width / 2);
    glVertex3d(length /2 , 0, width / 2);
    glVertex3d(length /2 , 0, -width / 2);

    glEnd();

    //top face
    glColor3d(0.8, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(-length /2 , height, -width / 2);
    glVertex3d(-length /2 , height, width / 2);
    glVertex3d(length / 3 , height, -width / 2);
    glVertex3d(length / 3, height, width / 2);

    glEnd();

    //front  face
    glColor3d(0.7, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(length / 3 , height, -width / 2);
    glVertex3d(length / 3 , height, width / 2);
    glVertex3d(length / 2 , 0, -width / 2);
    glVertex3d(length / 2, 0, width / 2);

    glEnd();

    //left face
    glColor3d(0.6, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(-length / 2 , 0, -width / 2);
    glVertex3d(-length / 2 , height, -width / 2);
    glVertex3d(length / 3 , 0, -width / 2);
    glVertex3d(length / 3, height, -width / 2);
    glVertex3d(length / 2 , 0, -width / 2);

    glEnd();

    //right face
    glColor3d(0.6, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(-length / 2 , height, width / 2);
    glVertex3d(-length / 2 , 0, width / 2);
    glVertex3d(length / 3, height, width / 2);
    glVertex3d(length / 3 , 0, width / 2);
    glVertex3d(length / 2 , 0, width / 2);

    glEnd();

    //back face
    glColor3d(0.8, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(-length / 2 , 0, -width / 2);
    glVertex3d(-length / 2 , 0, width / 2);
    glVertex3d(-length / 2 , height, -width / 2);
    glVertex3d(-length / 2 , height, width / 2);

    glEnd();

    glPopMatrix();
}
