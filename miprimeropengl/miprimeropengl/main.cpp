#include <glut.h>

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_TRIANGLES);

	// Dibujamos un cuadrado
	//glColor3f(1.0, 2.0, 0.0);
	// Color para el cuadrado
	//glVertex3f(-0.5, 0.5, -2.5);
	// Coordenadas del primer vértice (superior-izquierda)
	//glVertex3f(-0.5, -0.5, 0.5);
	// Coordenadas del segundo vértice (inferior-izquierda)
	//glVertex3f(0.5, -0.5, 0.5);
	// Coordenadas del primer vértice (inferior-derecha)
	//glVertex3f(0.5, 0.5, -2.5); //-0-5
	// Coordenadas del primer vértice (superior-derecha)
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);

	glVertex3f(-3.0, -1.0, -3.0);
	glVertex3f(4.0, -1.0, -3.0);      // P1 es rojo     // P2 es verde
	glVertex3f(4.0, -1.5, -3.0);      // P3 es azul
	glVertex3f(-3.0, -1.5, -3.0);     // P4 es morado

	glEnd();

	// LADO TRASERO: lado blanco
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);

	glVertex3f(-3.0, -1.0, -3.0);     // P1 es rojo
	glVertex3f(4.0, -1.0, -3.0);      // P2 es verde
	glVertex3f(4.0, -1.5, -3.0);     // P3 es azul
	glVertex3f(-3.0, -1.5, -3.0);     // P4 es morado
	glEnd();

	// LADO DERECHO: lado morado
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);

	glVertex3f(4.0, -1.0, -3.0);
	glVertex3f(4.0, -1.5, -3.0);
	glVertex3f(4.0, -1.5, 4.0);
	glVertex3f(4.0, -1.0, 4.0);
	glEnd();

	// LADO IZQUIERDO: lado verde
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);

	glVertex3f(-3.0, -1.0, -3.0);
	glVertex3f(-3.0, -1.5, -3.0);
	glVertex3f(-3.0, -1.5, 4.0);
	glVertex3f(-3.0, -1.0, 4.0);
	glEnd();

	// LADO SUPERIOR: lado azul
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);

	glVertex3f(-3.0, -1.0, -3.0);
	glVertex3f(4.0, -1.0, -3.0);
	glVertex3f(4.0, -1.0, 4.0);
	glVertex3f(-3.0, -1.0, 4.0);
	glEnd();

	// LADO INFERIOR: lado rojo
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);

	glVertex3f(-3.0, -1.5, -3.0);
	glVertex3f(4.0, -1.5, -3.0);
	glVertex3f(4.0, -1.5, 4.0);
	glVertex3f(-3.0, -1.5, 4.0);
	glEnd();

	glFlush();
	glutSwapBuffers();

		
		
	//glEnd();
	//glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(1000, 700);
	glutCreateWindow("Hello world!");
	glutDisplayFunc(displayMe);
	glutMainLoop();
	


	return 0;
}