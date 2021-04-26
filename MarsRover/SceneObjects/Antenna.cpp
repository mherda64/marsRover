#include "Antenna.h"

Antenna::Antenna(const Point& position, const Rotation& rotation, GLdouble r, GLdouble width, float speed):SceneObject(position,
    rotation),r(r),speed(speed),width(width)
{

}

void Antenna::draw()
{
	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);

	glRotatef(rotation.xRot, 1, 0, 0);
	glRotatef(rotation.yRot, 0, 1, 0);
	glRotatef(rotation.zRot, 0, 0, 1);

	glScalef(5, 5, 5);

	double alpha,x,y,z;
	double baseHeight = 10;
	int stripCount = 4;
	double oneStep = baseHeight / stripCount;

	
    
    glColor3d(.4f, .5f, 0.7f);
	for (double i = 0; i <= baseHeight; i += oneStep)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 20.0)
		{
			x = r * sin(alpha);
			z = r * cos(alpha);

			glVertex3d(x, i + oneStep, z);

			glVertex3d(x, i, z);
		}
		x = r * sin(0);
		z = r * cos(0);
		glVertex3d(x, i,z);
		glVertex3d(x, i + oneStep,z);
		glEnd();
	}

	double animationR = r * 10;
	

	glBegin(GL_TRIANGLE_FAN);
	//glColor3d(.4f, .5f, 0);
	glVertex3d(0, baseHeight + oneStep*3, 0);
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 10.0)
	{
		x = r * sin(alpha);
		z = r * cos(alpha);
		glVertex3d( x,  baseHeight + oneStep,  z);
	}
	glVertex3d(0, r, 0);
	glEnd();

	//kaptur góra
	bool changeColor = true;
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(.6f, .5f, 0);
	glVertex3d(0,  baseHeight + oneStep ,0);
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0,changeColor=!changeColor)
	{
		x = animationR * sin(alpha);
		z = animationR * cos(alpha);
		if (changeColor)
		{
			glColor3d(.6f, .5f, 0);
		}
		else
		{
			glColor3d(.8f, .5f, 0);
		}
		glVertex3d(x/speed, baseHeight + oneStep*speed, z/speed);
	}
	changeColor = !changeColor;
	x = animationR * sin(2 * PI + PI / 10.0);
	z = animationR * cos(2 * PI + PI / 10.0);
	glVertex3d( x / speed,  baseHeight + oneStep * speed, z/speed);
	glEnd();

	//kaptur dół
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(.6f, .5f, 0);
    glVertex3d(0,  baseHeight + oneStep ,0);
    for (alpha = 2 * PI; alpha >= 0; alpha -= PI / 20.0,changeColor=!changeColor)
    {
        x = animationR * sin(alpha);
        z = animationR * cos(alpha);
        if (changeColor)
        {
            glColor3d(.6f, .5f, 0);
        }
        else
        {
            glColor3d(.8f, .5f, 0);
        }
        glVertex3d(x/speed, baseHeight + oneStep*speed, z/speed);
    }
    changeColor = !changeColor;
    x = animationR * sin(2 * PI - PI / 10.0);
    z = animationR * cos(2 * PI + PI / 10.0);
    glVertex3d( x / speed,  baseHeight + oneStep * speed, z/speed);
    glEnd();

	if (speed >= 3.f)
	{
		animationDirection = false;
	}
	if(speed<=1.f)
	{
		animationDirection = true;
	}
	if (animationDirection)
	{
		speed += speed / 200;
	}
	else
	{
		speed -= speed / 200;
	}

	glColor3d(.4f, .5f, 0);
	glTranslatef(0,  baseHeight + oneStep * 3, 0);
	glutSolidSphere(0.5, 10, 10);

	glPopMatrix();
}
