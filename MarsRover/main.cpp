#include <GL/glut.h>
#include <cstdio>
#include "math.h"

GLdouble fov = 90.0;
GLdouble dist = -30.0;
GLdouble rotX = 0.0;
GLdouble rotY = 0.0;
GLdouble rotZ = 0.0;

float sinDeg(int angle) {
    return sin((float) (angle) / 360 * 2 * 3.14);
}

float cosDeg(int angle) {
    return cos((float) (angle) / 360 * 2 * 3.14);
}

void szescian(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    {
        // Parametry wierzcholkow

        GLfloat sa[3] = { 0.0f,0.0f,0.0f };
        GLfloat sb[3] = { 10.0f,0.0f,0.0f };
        GLfloat sc[3] = { 10.0f,10.0f,0.0f };
        GLfloat sd[3] = { 0.0f,10.0f,0.0f };
        GLfloat se[3] = { 0.0f,0.0f,-10.0f };
        GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
        GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
        GLfloat sh[3] = { 0.0f,10.0f,-10.0f };

        GLfloat sa_[3] = { 0.0f,
                           0.0f,
                           0.0f };
        GLfloat sb_[3] = { 10 * cosDeg(45) ,
                           -10 * sinDeg(45),
                           0.0f };
        GLfloat sc_[3] = { 10 * cosDeg(45) + 10 * sinDeg(45),
                           -10 * sinDeg(45) + 10 * cosDeg(45),
                           0.0f };
        GLfloat sd_[3] = { 10 * sinDeg(45) ,
                           10 * cosDeg(45),
                           0.0f };
//         Sciany skladowe
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3fv(sa_);
        glVertex3fv(sb_);
        glVertex3fv(sc_);
        glVertex3fv(sd_);
        glEnd();

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3fv(sb);
        glVertex3fv(sf);
        glVertex3fv(sg);
        glVertex3fv(sc);
        glEnd();

        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex3fv(sf);
        glVertex3fv(se);
        glVertex3fv(sh);
        glVertex3fv(sg);
        glEnd();

        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3fv(se);
        glVertex3fv(sa);
        glVertex3fv(sd);
        glVertex3fv(sh);
        glEnd();

        glColor3f(0.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex3fv(sd);
        glVertex3fv(sc);
        glVertex3fv(sg);
        glVertex3fv(sh);
        glEnd();

        glColor3f(1.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex3fv(sa);
        glVertex3fv(sb);
        glVertex3fv(sf);
        glVertex3fv(se);
        glEnd();
    }
}

void walec(double r, double h)
{
    double x, y, alpha, PI = 3.14;
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.8, 0.0, 0);
    glVertex3d(0, 0, 0);
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 40.0)
    {
        x = r*sin(alpha);
        y = r*cos(alpha);
        glVertex3d(x, y, 0);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 40.0)
    {
        x = r*sin(alpha);
        y = r* cos(alpha);
        glVertex3d(x, y, 0);
        glVertex3d(x, y, h);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0, 0, h);
    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 40.0)
    {
        x = r*sin(alpha);
        y = r*cos(alpha);
        glVertex3d(x, y, h);
    }
    glEnd();
}

void drawBox(void)
{
    walec(5, 5);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0, 0, dist);
    glRotatef(rotX, 1, 0,0);
    glRotatef(rotY, 0, 1,0);
    glRotatef(rotZ, 0, 0,1);

    drawBox();

    // Flush drawing commands
    glFlush();
    glutSwapBuffers();
//    glutPostRedisplay();
}

void init(void)
{

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    //glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
    // Black brush
    glColor3f(0.0,0.0,0.0);

}

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;
    GLfloat fAspect;
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    fAspect=(GLfloat)w/(GLfloat)h;
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble aspect = 1;
    if( h > 0 )
        aspect = w /( GLdouble ) h;

    // rzutowanie perspektywiczne
    gluPerspective( fov, aspect, 1.0, 100.0 );


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    display();
}

void Keyboard( unsigned char key, int x, int y )
{
    //fov
    if( key == 'z' && fov < 180 )
        fov++;
    else if( key == 'x' && fov > 0 )
        fov--;
    //distance
    else if( key == 'c')
        dist+= 1;
    else if( key == 'v')
        dist-= 1;
    //x rotation
    else if( key == 'i')
        rotX += 5;
    else if( key == 'o')
        rotX -= 5;
    //y rotation
    else if( key == 'k')
        rotY += 5;
    else if( key == 'l')
        rotY -= 5;
    //z rotation
    else if( key == ',')
        rotZ += 5;
    else if( key == '.')
        rotZ -= 5;

    ChangeSize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(800,20);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mars Rover");

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    ChangeSize(w, h);

    glutDisplayFunc(display);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);

    init();
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}