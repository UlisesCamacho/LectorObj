
//librería para utilizar operaciones matemáticas
#include<glut.h>

#include <stdlib.h>
#include <string>
#include <fstream>  //Biblioteca para lectura y escritura de archivos 
#include <sstream>
#include <iostream>
#include <list>

using namespace std;
using std::ifstream;

// Estructura vertice: Almacena los puntos de un vertice y id guarda el numero de vertice
struct Vertex
{
	float x;	//Punto en x
	float y;	//Punto en y
	float z;	//Punto en z	
	int idVertex;		//Numero de Punto
};

struct INT
{
	int indVer;
};
// EEstructura Cara: Al
struct Face
{
	int idFace;					//Nunero de cara
	list<INT> listIndVert;		//Lista de indices  de vertices que forman la cara
	list<Vertex> listV;
};

struct Shape
{
	list<Vertex> listVert;	//Lista de vertices de objeto
	list <Face> listFaces;		//Lista de caras del objeto
	string nameShape;			//Nombre de la figura
	int idShape;				//Numero de figura
};

char namefile[80]; //Guarda el nombre del archivo 
void CreateShape();
void CreaFace();
void CreaVertex();
void ReadFile();
void PrintDataObject();
void Capture();
void DrawShape();
list<Shape> Shapes;
Shape auxShape;
string dataRead;
int contFig, contVer, contFace;
Vertex auxVertex;
Face auxFace;



static GLfloat spin = 0.0;

/*typedef struct {
float x,y,z;
}Vertex;

typedef struct {
Vertex ver[4];
}Face;

Face cube[6];

void CreateCube()
{
//Face 1
cube[0].ver[0].x = 1.0; cube[0].ver[0].y = -1.0; cube[0].ver[0].z = -1.0;
cube[0].ver[1].x = 1.0; cube[0].ver[1].y = -1.0; cube[0].ver[1].z = 1.0;
cube[0].ver[2].x = -1.0; cube[0].ver[2].y = -1.0; cube[0].ver[2].z = 1.0;
cube[0].ver[3].x = -1.0; cube[0].ver[3].y = -1.0; cube[0].ver[3].z = -1.0;
//Face 2
cube[1].ver[0].x = 1.0; cube[1].ver[0].y = 1.0; cube[1].ver[0].z = -1.0;
cube[1].ver[1].x = -1.0; cube[1].ver[1].y = 1.0; cube[1].ver[1].z = -1.0;
cube[1].ver[2].x = -1.0; cube[1].ver[2].y = 1.0; cube[1].ver[2].z = 1.0;
cube[1].ver[3].x = 1.0; cube[1].ver[3].y = 1.0; cube[1].ver[3].z = 1.0;
//Face 3
cube[2].ver[0].x = 1.0; cube[2].ver[0].y = -1.0; cube[2].ver[0].z = -1.0;
cube[2].ver[1].x = 1.0; cube[2].ver[1].y = 1.0; cube[2].ver[1].z = -1.0;
cube[2].ver[2].x = 1.0; cube[2].ver[2].y = 1.0; cube[2].ver[2].z = 1.0;
cube[2].ver[3].x = 1.0; cube[2].ver[3].y = -1.0; cube[2].ver[3].z = 1.0;
//Face 4
cube[3].ver[0].x = 1.0; cube[3].ver[0].y = -1.0; cube[3].ver[0].z = 1.0;
cube[3].ver[1].x = 1.0; cube[3].ver[1].y = 1.0; cube[3].ver[1].z = 1.0;
cube[3].ver[2].x = -1.0; cube[3].ver[2].y = 1.0; cube[3].ver[2].z = 1.0;
cube[3].ver[3].x = -1.0; cube[3].ver[3].y = -1.0; cube[3].ver[3].z = 1.0;
//Face 5
cube[4].ver[0].x = -1.0; cube[4].ver[0].y = -1.0; cube[4].ver[0].z = 1.0;
cube[4].ver[1].x = -1.0; cube[4].ver[1].y = 1.0; cube[4].ver[1].z = 1.0;
cube[4].ver[2].x = -1.0; cube[4].ver[2].y = 1.0; cube[4].ver[2].z = -1.0;
cube[4].ver[3].x = -1.0; cube[4].ver[3].y = -1.0; cube[4].ver[3].z = -1.0;
//Face 1
cube[5].ver[0].x = 1.0; cube[5].ver[0].y = 1.0; cube[5].ver[0].z = -1.0;
cube[5].ver[1].x = 1.0; cube[5].ver[1].y = -1.0; cube[5].ver[1].z = -1.0;
cube[5].ver[2].x = -1.0; cube[5].ver[2].y = -1.0; cube[5].ver[2].z = -1.0;
cube[5].ver[3].x = -1.0; cube[5].ver[3].y = 1.0; cube[5].ver[3].z = -1.0;
}*/
void display(void)
{
	int f, v;
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);
	//glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	//glColor3f(1.0, 1.0, 1.0);
	//glRectf(-25.0, -25.0, 25.0, 25.0);
	//glPopMatrix();
	//glutSwapBuffers();
	/*  draw white polygon (rectangle) with corners at
	*  (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
	*/
	glColor3f(1.0, 1.0, 1.0);
	DrawShape();
	//glutSolidCube(0.5);

	/*  don't wait!
	*  start processing buffered OpenGL routines
	*/
	glFlush();
}
void spinDisplay(void)
{
	spin = spin + 1.0;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

void init(void)
{
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0); //Aqui son unidades no pixels
	glRotatef(50.0, 1.0, 1.0, 1.0);
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

/*
*  Declare initial window size, position, and display mode
*  (single buffer and RGBA).  Open window with "hello"
*  in its title bar.  Call initialization routines.
*  Register callback function to display graphics.
*  Enter main loop and process events.
*/

int main(int argc, char** argv)
{
	//CreateCube();
	Capture();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Cube");
	init();
	glutDisplayFunc(display);
	// glutReshapeFunc(reshape); 
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;   /* ISO C requires main to return int. */
}

void Capture()
{
	cout << "Nombre del archivo: "; //Pide el nombre del archivo
	cin >> namefile;		    //Guarda el nombre del archivo en namefile	
	ReadFile();		            //Empieza a leer las lineas del archivo
	system("pause");
	PrintDataObject();
}

void ReadFile()
{
	int separator = 0;
	int tamline;
	contFig = 1;
	contVer = 1;
	contFace = 1;

	ifstream file(namefile, ios::in); //Creacion del objeto para abrir el fichero 
									  //Si no se puede abrir el archivo
	if (!file)
	{
		cout << "El archivo no puede ser abierto \n";
		EXIT_FAILURE;
			
		//exit(0);
	}

	while (getline(file, dataRead))
	{
		//Copia la cadena desde la posicion 0 con un limite de 2 caracteres y compara si es igual 
		//a la cadena 
		if (dataRead.substr(0, 2) == "o ")
		{
			if (separator < contFig)
			{
				Shapes.push_back(auxShape);
				separator++;
			}
			//Inicializa campos de figura
			tamline = dataRead.length();
			auxShape.listFaces.clear();
			auxShape.listVert.clear();
			auxShape.idShape = contFig; //Asigna numero de Figura
			auxShape.nameShape = dataRead.substr(2, tamline); //Copia nombre de figura y lo asigna
			contFig++; //Incremento de contador figura
		}
		else if (dataRead.substr(0, 2) == "v ")
		{
			CreaVertex();
		}
		else if (dataRead.substr(0, 2) == "f ")
		{
			CreaFace();
		}
	}
	Shapes.push_back(auxShape);
	file.close();
}

void CreaVertex()
{
	int posRead = 2;

	if (dataRead.substr(posRead, 1) == "-")
	{
		posRead = 3;
		auxVertex.x = atof((dataRead.substr(posRead, 8)).c_str());
		auxVertex.x = auxVertex.x * (-1);
	}
	else
	{
		posRead = 2;
		auxVertex.x = atof((dataRead.substr(posRead, 8)).c_str());
	}
	posRead += 9;
	if (dataRead.substr(posRead, 1) == "-")
	{
		posRead++;
		auxVertex.y = atof((dataRead.substr(posRead, 8)).c_str());
		auxVertex.y = auxVertex.y * (-1);
	}
	else
	{
		auxVertex.y = atof((dataRead.substr(posRead, 8)).c_str());
	}
	posRead += 9;
	if (dataRead.substr(posRead, 1) == "-")
	{
		posRead++;
		auxVertex.z = atof((dataRead.substr(posRead, 8)).c_str());
		auxVertex.z = auxVertex.z * (-1);
	}
	else
	{
		auxVertex.z = atof((dataRead.substr(posRead, 8)).c_str());
	}
	auxVertex.idVertex = contVer;  //Asigna numero de vertice de la figura
	contVer++;		           //Incremente el numero de vertice 
	auxShape.listVert.push_back(auxVertex); //Agrega Vertice a la lista de vertices de la figura
}
void CreaFace()
{
	int posRead = 0;
	INT auxEnt;
	stringstream auxString;
	string auxs;
	auxString.str(dataRead);

	getline(auxString, auxs, ' ');
	auxFace.listIndVert.clear();
	while (getline(auxString, auxs, ' '))
	{
		auxEnt.indVer = atoi(auxs.c_str());
		auxFace.listIndVert.push_back(auxEnt);
	}
	auxFace.idFace = contFace;
	contFace++;
	auxShape.listFaces.push_back(auxFace);
}

void PrintDataObject()
{
	bool separator = true;
	list<Face>::iterator i3;   //Iterador para recorrer la lista de Caras
	list<INT>::iterator i4;    //Iterador para recorrer la lista de enteros
	list<Shape>::iterator i1; //Iterador para recorrer la lista de figuras
	list<Vertex>::iterator i2; //Iterador para recorrer la lista de vertices

	for (i1 = Shapes.begin(); i1 != Shapes.end(); i1++)
	{
		cout << "o " << i1->nameShape << "\n";
		if (separator == true)
		{
			cout << "\n";
		}
		//Ciclo de impresion de datos de vertices
		for (i2 = i1->listVert.begin(); i2 != i1->listVert.end(); i2++)
		{
			cout << "v " << i2->x << "  " << i2->y << "  " << i2->z << "\n";
		}
		if (separator == true)
		{
			cout << "\n";
		}
		//Ciclo de impresion de datos de Caras
		for (i3 = i1->listFaces.begin(); i3 != i1->listFaces.end(); i3++)
		{
			separator = false;
			cout << "f ";
			for (i4 = i3->listIndVert.begin(); i4 != i3->listIndVert.end(); i4++)
			{
				cout << i4->indVer << "  ";
			}
			cout << "\n";
		}
	}
}
void DrawShape()
{
	list<Face>::iterator i3;   //Iterador para recorrer la lista de Caras
	list<INT>::iterator i4;    //Iterador para recorrer la lista de enteros
	list<Shape>::iterator i1; //Iterador para recorrer la lista de figuras
	list<Vertex>::iterator i2; //Iterador para recorrer la lista de vertices

	for (i1 = Shapes.begin(); i1 != Shapes.end(); i1++)
	{
		for (i3 = i1->listFaces.begin(); i3 != i1->listFaces.end(); i3++)
		{
			glBegin(GL_LINE_LOOP);
			for (i4 = i3->listIndVert.begin(); i4 != i3->listIndVert.end(); i4++)
			{

				for (i2 = i1->listVert.begin(); i2 != i1->listVert.end(); i2++)
				{
					if (i2->idVertex == i4->indVer)
					{
						glVertex3f(i2->x, i2->y, i2->z);
						break;
					}

				}

			}
			glEnd();
		}
	}
}
