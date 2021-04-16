//
// Created by musiek on 4/16/21.
//

#include "basicFigures.h"

void cylinderZHeight(int r, int hMax, int zMin, int zMax) {
    double x, y, alpha, PI = 3.14;
    double currentH;

    //upewniamy się, że współrzędna zMin jest tą mniejszą współrzędną na osi Z
    if (zMin > zMax) {
        int tmp = zMax;
        zMax = zMin;
        zMin = tmp;
    }

    //rysowanie dolnej podstawy
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(0, 0, zMin);
    glColor3d(0, 1, 0);
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0)
    {
        x = r*sin(alpha);
        y = r*cos(alpha);
        glVertex3d(x, y, zMin);
    }
    //dodatkowy vertex dzięki któremu unikam "dziurawych" obiektów wynikajacych
    //z niedokładności przybliżenia liczby PI
    //punkt (0, r, zMin) jest punktem początkowym i końcowym rysowania podstawy
    glVertex3d(0, r, zMin);
    glEnd();

    //rysownaie ścian bocznych w częściach o maksymalnej długości hMax, od zMin do zMax
    //zakładamy że |zMin| + |zMax| jest wielokrotnością hMax
    double colorStep = 0;
    for (currentH = zMin; currentH < zMax; currentH += hMax) {
        glBegin(GL_TRIANGLE_STRIP);
        for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 20.0)
        {
            x = r*sin(alpha);
            y = r* cos(alpha);
            glColor3d(0, 1 - colorStep, colorStep);
            glVertex3d(x, y, currentH);
            glColor3d(0, 1 - (colorStep + 1.0 / ((abs(zMin) + abs(zMax)) / hMax)), colorStep + 1.0 / ((abs(zMin) + abs(zMax)) / hMax));
            glVertex3d(x, y, currentH + hMax);
        }
        //dodatkowe vertexy dzięki któremu unikam "dziurawych" obiektów wynikajacych
        //z niedokładności przybliżenia liczby PI
        x = r*sin(0);
        y = r* cos(0);
        glColor3d(0, 1 - colorStep, colorStep);
        glVertex3d(x, y, currentH);
        glColor3d(0, 1 - (colorStep + 1.0 / hMax), colorStep + 1.0 / hMax);
        glVertex3d(x, y, currentH + hMax);

        colorStep += 1.0 / ((abs(zMin) + abs(zMax)) / hMax);
        glEnd();
    }

    //rysowanie górnej podstawy
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 0.0, 0);
    glVertex3d(0, 0, zMax);
    glColor3d(0, 0.0, 1);
    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 20.0)
    {
        x = r*sin(alpha);
        y = r*cos(alpha);
        glVertex3d(x, y, zMax);
    }
    //dodatkowy vertex dzięki któremu unikam "dziurawych" obiektów wynikajacych
    //z niedokładności przybliżenia liczby PI
    //punkt (0, r, zMax) jest punktem początkowym i końcowym rysowania podstawy
    glVertex3d(0, r, zMax);
    glEnd();
}

