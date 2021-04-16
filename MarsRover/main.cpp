#include <GL/glut.h>
#include <cstdio>
#include "basicFigures.h"

GLdouble fov = 90.0;
GLdouble dist = -30.0;
GLdouble rotX = 0.0;
GLdouble rotY = 0.0;
GLdouble rotZ = 0.0;

void drawBox(void)
{
    cylinderZHeight(5, 10, -50, 10);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);

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
void changeSize(int w, int h)
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
    gluPerspective( fov, aspect, 1.0, 400.0 );


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    display();
}

void keyboard( unsigned char key, int x, int y )
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

    changeSize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
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
    changeSize(w, h);

    glutDisplayFunc(display);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyboard);

    init();
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}