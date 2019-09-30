#include <iostream>
using std::cerr;
using std::endl;
#include <stdlib.h>
//using std::exit;
//#include <GL/glut.h> // GLUT stuff, includes OpenGL headers as well 
#include <windows.h>
#include <math.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <GLU.H>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include<glut.h>
#include<GL.H>
#include <Windows.h>


#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#include<glut.h>

int SCREEN_HEIGHT = 480;
// Keep track of times clicked, on 3 clicks draw.
int NUMPOINTS = 0;
double rotate_y = 0;
double rotate_x = 0;
// Point class to keep it a little cleaner.

class Point {
public:
	float x, y, z;
	void setxyz(float x2, float y2, float z2) { x = x2; y = y2; z = z2; }
	const Point & operator=(const Point &rPoint) {
		x = rPoint.x;
		y = rPoint.y;
		z = rPoint.z;

		return *this;
	}

};

Point abc[4];

void myInit() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void drawDot(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void drawLine(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);

	glEnd();
	glFlush();
}

// Calculate the next bezier point.
Point drawBezier(Point A, Point B, Point C, Point D, double t) {
	Point P;
	P.x = pow((1 - t), 3) * A.x + 3 * t * pow((1 - t), 2) * B.x + 3 * (1 - t) * pow(t, 2)* C.x + pow(t, 3)* D.x;
	P.y = pow((1 - t), 3) * A.y + 3 * t * pow((1 - t), 2) * B.y + 3 * (1 - t) * pow(t, 2)* C.y + pow(t, 3)* D.y;
	P.z = pow((1 - t), 3) * A.z + 3 * t * pow((1 - t), 2) * B.z + 3 * (1 - t) * pow(t, 2)* C.z + pow(t, 3)* D.z;
	return P;
}

void myMouse(int button, int state, int x, int y,int z) {
	// If left button was clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Store where the user clicked, note Y is backwards.
		abc[NUMPOINTS].setxyz((float)x, (float)(SCREEN_HEIGHT - y), (float)z);
		NUMPOINTS++;

		// Draw the red  dot.
		drawDot(x, SCREEN_HEIGHT - y);

		// If 3 points are drawn do the curve.
		if (NUMPOINTS == 4) {
		//	glColor3f(1.0, 1.0, 1.0);
			// Draw two legs of the triangle
			drawLine(abc[0], abc[1]);
			drawLine(abc[1], abc[2]);
			drawLine(abc[2], abc[3]);
			//drawLine(abc[3], abc[4]);
			Point POld = abc[0];
			/* Draw each segment of the curve.  Make t increment in
			smaller amounts for a more detailed curve. */
			for (double t = 0.0; t <= 1.0; t += 0.1) {
				Point P = drawBezier(abc[0], abc[1], abc[2], abc[3], t);
				drawLine(POld, P);
				POld = P;
			}
			glColor3f(1.0, 0.0, 0.0);
			NUMPOINTS = 0;
		}
	}
}

void myDisplay() {

		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glLoadIdentity();
		float x=50.0;
		float y=50.0;
		for (int i = 0; i <= 4; i++)
		{
			switch (i)
			{
			case 1: 
				abc[0].setxyz(50, 50,0);
				abc[1].setxyz(60,70,0);
				abc[2].setxyz(70,70,0);
				abc[3].setxyz(80,50,0);
				NUMPOINTS = 4;
				break;
			case 2:
				abc[0].setxyz(80,50,0);
				abc[1].setxyz(90,30,0);
				abc[2].setxyz(100,30,0);
				abc[3].setxyz(110,50,0);
				NUMPOINTS = 4;
				break;
			case 3:
				abc[0].setxyz(110,50,0);
				abc[1].setxyz(120,70,0);
				abc[2].setxyz(130,70,0);
				abc[3].setxyz(140,50,0);
				NUMPOINTS = 4;
				break;
			case 4:
				abc[0].setxyz(140,50,0);
				abc[1].setxyz(150,30,0);
				abc[2].setxyz(160,30,0);
				abc[3].setxyz(170,50,0);
				NUMPOINTS = 4;
				break;
			default:
				break;
			}
				
						// If 3 points are drawn do the curve.
			if (NUMPOINTS == 4) {
				glColor3f(0.0, 1.0, 0.0);
				// Draw two legs of the triangle
		//		drawLine(abc[0], abc[1]);
		//		drawLine(abc[1], abc[2]);
		//		drawLine(abc[2], abc[3]);
				//drawLine(abc[3], abc[4]);
				Point POld = abc[0];
				/* Draw each segment of the curve.  Make t increment in
				smaller amounts for a more detailed curve. */
				for (double t = 0.0; t <= 1.0; t += 0.1) {
					Point P = drawBezier(abc[0], abc[1], abc[2], abc[3], t);
					glColor3f(0.0, 0.0, 1.0);
					drawLine(POld, P);
					POld = P;
				}
				
				NUMPOINTS = 0;
			}	
		}
		glFlush();
		glutSwapBuffers();
}
int main(int argc, char *argv[]) 
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glEnable(GL_DEPTH_TEST);
	glutCreateWindow("Bezier Curve");
	

//       	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);


	myInit();
	glutMainLoop();

	return 0;
}