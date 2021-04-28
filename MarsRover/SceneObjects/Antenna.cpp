#include "Antenna.h"

Antenna::Antenna(const Point& position, const Rotation& rotation, GLdouble r, GLdouble width, float speed):SceneObject(position,
    rotation),r(r),speed(speed),width(width)
{
	minDeviation = 1.5f;
	maxDeviation = 3.f;
	animationStep = minDeviation;
}

void Antenna::draw()
{
	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);

	glRotatef(rotation.xRot, 1, 0, 0);
	glRotatef(rotation.yRot, 0, 1, 0);
	glRotatef(rotation.zRot, 0, 0, 1);

	/* scale of antenna*/
	glScalef(2.5, 2.5, 2.5);

	double alpha,x,y,z;
	double baseHeight = 10; /**<height of the antenna base*/
	int stripCount = 4; /**<count of the strip in antenna base*/
	double oneStep = baseHeight / stripCount; /**<height of one strip*/

	
    /*
	* drawing antenna base
	*/
    glColor3d(.4f, .5f, 0.7f);
	for (double i = 0; i <= baseHeight; i += oneStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		// adding new verticels
		for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 20.0)
		{
			x = r * sin(alpha);
			z = r * cos(alpha);

			glVertex3d(x, i + oneStep, z);

			glVertex3d(x, i, z);
		}
		/*
		* adding 2 last verticles to eliminate space between start and end of strip
		*/
		x = r * sin(0);
		z = r * cos(0);
		glVertex3d(x, i + oneStep, z);
		glVertex3d(x, i,z);
		
		glEnd();
	}

	
	/*
	* drawing antenna spikie
	*/
	glBegin(GL_TRIANGLE_FAN);
	/* adding central vertice*/
	glVertex3d(0, baseHeight + oneStep*3, 0);
	/* adding new verticels */
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 10.0)
	{
		x = r * sin(alpha);
		z = r * cos(alpha);
		glVertex3d( x,  baseHeight + oneStep,  z);
	}
	/*adding last verticle to eliminate space between start and end of fan*/
	x = r * sin(0);
	z = r * cos(0);
	glVertex3d(x, baseHeight + oneStep, z);
	glEnd();

	double mantleR = r * 10; /**< radius of mantel*/
	bool changeColor = true; /**< variable that let us change betwen 2 colors*/

	/*
	* drawing inner mantle
	*/ 
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(.6f, .5f, 0);
	/* adding central vertice*/
	glVertex3d(0,  baseHeight + (oneStep*7/6) ,0);
	/* adding new vertices */
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 20.0,changeColor=!changeColor)
	{
		x = mantleR * sin(alpha);
		z = mantleR * cos(alpha);
		/*color change*/
		if (changeColor)
		{
			glColor3d(.6f, .5f, 0);
		}
		else
		{
			glColor3d(.8f, .5f, 0);
		}
		glVertex3d(x/animationStep, baseHeight + oneStep*animationStep, z/animationStep);
	}
	changeColor = !changeColor;
	/*adding last verticle to eliminate space between start and end of fan*/
	x = mantleR * sin(2 * PI + PI / 10.0);
	z = mantleR * cos(2 * PI + PI / 10.0);
	glVertex3d( x / animationStep,  baseHeight + oneStep * animationStep, z/animationStep);
	glEnd();

	/*
	* drawing external mantle
	*/
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(.6f, .5f, 0);
	/* adding central vertice*/
    glVertex3d(0,  baseHeight + oneStep ,0);
	/* adding new verticels */
    for (alpha = 2 * PI; alpha >= 0; alpha -= PI / 20.0,changeColor=!changeColor)
    {
        x = mantleR * sin(alpha);
        z = mantleR * cos(alpha);
		/*color change*/
        if (changeColor)
        {
            glColor3d(.6f, .5f, 0);
        }
        else
        {
            glColor3d(.8f, .5f, 0);
        }
        glVertex3d(x/animationStep, baseHeight + oneStep*animationStep, z/animationStep);
    }
    changeColor = !changeColor;
	/*adding last verticle to eliminate space between start and end of fan*/
    x = mantleR * sin(2 * PI - PI / 10.0);
    z = mantleR * cos(2 * PI + PI / 10.0);
    glVertex3d( x / animationStep,  baseHeight + oneStep * animationStep, z/animationStep);
    glEnd();

	/*
	* changing a direction that mantle move
	*/
	if (animationStep >= maxDeviation)
	{
		animationDirection = false;
	}
	if(animationStep<=minDeviation)
	{
		animationDirection = true;
	}
	/*
	* change of the factor that influence on mantle position
	*/
	if (animationDirection)
	{
		animationStep += 1 / speed;
	}
	else
	{
		animationStep -= 1 / speed;
	}

	/*
	* drawing sphere on the top of antenna spike
	*/
	glColor3d(.4f, .5f, 0);
	/*changing position of sphere to position of antenna spike*/
	glTranslatef(0,  baseHeight + oneStep * 3, 0);
	glutSolidSphere(0.5, 10, 10);

	glPopMatrix();
}
