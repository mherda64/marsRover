#include "Afterburner.h"

Afterburner::Afterburner(const Point& position, const Rotation& rotation, GLdouble topRadius, GLdouble bottomRadius, GLdouble height, GLdouble innerRadius)
	: SceneObject(position, rotation), topRadius(topRadius), bottomRadius(bottomRadius), height(height),innerRadius(innerRadius)
{

}

void Afterburner::draw()
{
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);

    glRotatef(rotation.xRot, 1, 0, 0);
    glRotatef(rotation.yRot, 0, 1, 0);
    glRotatef(rotation.zRot, 0, 0, 1);

    double alpha;
    double zTmp, xTmp;

    /*
    * drawing afterburner external ring
    */
    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1, 0.0, 0);
    /* adding new verticels */
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0)
    {
        glColor3d(0, 1, 0);
        xTmp = topRadius * sin(alpha);
        zTmp = topRadius * cos(alpha);
        glVertex3d(xTmp, height, zTmp);

        glColor3d(1, 0.0, 0);
        xTmp = bottomRadius * sin(alpha);
        zTmp = bottomRadius * cos(alpha);
        glVertex3d(xTmp, 0, zTmp);
    }
    /* adding 2 last verticles to eliminate space between start and end of strip*/

    glColor3d(0, 1, 0);
    xTmp = topRadius * sin(alpha);
    zTmp = topRadius * cos(alpha);
    glVertex3d(xTmp, height, zTmp);
    glColor3d(1, 0.0, 0);
    xTmp = bottomRadius * sin(alpha);
    zTmp = bottomRadius * cos(alpha);
    glVertex3d(xTmp, 0, zTmp);

    glEnd();


    /*
    * drawing afterburner inner ring
    */
    glBegin(GL_TRIANGLE_STRIP);
    /* adding new verticels */
    for (alpha = 2 * PI; alpha >= 0; alpha -= PI / 20.0)
    {
        
        glColor3d(0, 0.5, 0.5);
        xTmp = innerRadius * sin(alpha);
        zTmp = innerRadius * cos(alpha);
        glVertex3d(xTmp, height / 3, zTmp);

        glColor3d(1, 0, 0);
        xTmp = bottomRadius * sin(alpha);
        zTmp = bottomRadius * cos(alpha);
        glVertex3d(xTmp, 0, zTmp);
    }
    /* adding 2 last verticles to eliminate space between start and end of strip*/
    glColor3d(0, 0.5, 0.5);
    xTmp = innerRadius * sin(2 * PI);
    zTmp = innerRadius * cos(2 * PI);
    glVertex3d(xTmp, height / 3, zTmp);
    glColor3d(1, 0, 0);
    xTmp = bottomRadius * sin(2 * PI);
    zTmp = bottomRadius * cos(2 * PI);
    glVertex3d(xTmp, 0, zTmp);

    glEnd();


    /*drawing bottom of afterburner*/
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0, 0.0, 0.7);
    /* adding central vertice*/
    glVertex3d(0, height / 3, 0);
    glColor3d(0, 0.5, 0.5);
    /* adding new verticels */
    for (alpha = 2 * PI; alpha >= 0; alpha -= PI / 20.0)
    {
        xTmp = innerRadius * sin(alpha);
        zTmp = innerRadius * cos(alpha);
        glVertex3d(xTmp, height / 3, zTmp);
    }
    /*adding last verticle to eliminate space between start and end of fan*/
    xTmp = innerRadius * sin(2 * PI);
    zTmp = innerRadius * cos(2 * PI);
    glVertex3d(xTmp, height / 3, zTmp);
    glEnd();


    glPopMatrix();
}
