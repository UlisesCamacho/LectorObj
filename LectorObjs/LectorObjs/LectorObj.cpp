#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include<glut.h>
#include<GL.H>
#include <Windows.h>
#include "LectorObj.h"

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#include<glut.h>




//
/* Ancho de la ventana de visualizacion */
#define ANCHO 400

/* Alto de la ventana de visualizacion */
#define ALTO 400 

/* Coordenada X del origen de la ventana,
* esquina superior izquierda */
#define ORIGENX 100 

/* Coordenada Y del origen de la ventana,
* esquina superior izquierda */
#define ORIGENY 100 


// ----------------------------------------------------------
// Variables globales
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;
int bandera = 0;


using namespace std;

class faces {
public:
	//atributos 

	int ind1, ind2, ind3; // see guardan los indices
	//constructor
	faces(int, int, int);
};
faces::faces(int i1, int i2, int i3)
{
	ind1 = i1;
	ind2 = i2;
	ind3 = i3;
}
//atributos
class vertex {
public:
	//atributos
	float x, y, z;
	//constructor
	vertex(float, float, float);
};
vertex::vertex(float vx, float vy, float vz)
{
	x = vx;
	y = vy;
	z = vz;
}
class Objeto {
public:
	//aributos
	string archivo;
	vector <vertex> vertices; //lista de vertices mejor usamos vectores
	vector <faces> indicesface; // lista de los indices de las caras
	int cont;
	/*lista de vertices y lista de faces, para las caras se guarda el primer numero de cada indice */
	//metodos
	void ObtenIndicesF();
	void GuardaVertices();
	void imprimir(int);
	void imprimeDatos();
	void draw();
	
//	int Dibujar(void);//realmente se lee el archivo y se divide 
						//contructor
	Objeto(string);
};
//constructor
Objeto::Objeto(string nom)
{
	archivo = nom;
}
Objeto o = Objeto("");
//en este metodo se genera la lectura del archivo obj original y se crea otro dependiendo de la opcion 
//donde se guardara el de vertices o face
void Objeto::imprimir(int opc)
{
	ifstream a;
	ofstream arch;
	string texto;
	string verifica;
	string cp1;
	int opcion = opc;
	string cp;
	string nuevo;
	vector<string> linea;
	cont = 0;
	switch (opcion)
	{
	case 1: cp = "v ";// para la v y la f hay que agregar un espacio en blanco
		nuevo = "vertices.obj";
		//cont = 8; //caso del cubo que tiene 8 v
		break;
	case 2:  cp = "f ";// para la v y la f hay que agregar un espacio en blanco
		nuevo = "face.obj";
		//cont = 12;// caso del cubo tiene 12 f
		break;
	//case 3: cp = "vn";// para la v y la f hay que agregar un espacio en blanco 
	//	break;
	}
	a.open(archivo);

	if (a.fail()) {
		cout << "No se puedo abrir archivo"; // dos veces para los vertices y las caras
		exit(1);
	}
	while (!a.eof())
	{
		getline(a, texto);
		cout << texto << endl;
	}
	a.close();

	a.open(archivo, ios::in);//se abre el archivo en modo lectura 
	if (a.fail())
	{
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	while (!a.eof())//mientras que no sea el final del texto 
	{
		getline(a, texto);//se copia todo o que contiene el archivo
		int i = 0;
		if (i == 0)
		{
			verifica = texto[i];
			cp1 = cp[i];
			if (verifica.compare(cp1) == 0)
			{
				i = 1;
				verifica = texto[i];
				cp1 = cp[i];
				if (verifica.compare(cp1) == 0)
				{
					//cout << texto << endl;
					linea.push_back(texto);
					cont = cont + 1;
				}
			}
		}
		
	}
	//se separan vertices y caras
	arch.open(nuevo, ios::out);
	if (arch.fail())
	{
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	//el 8 es porque tiene 8 vertices y cont esta igualado a 8 en el switch y en este caso se guardan las 8 lineas
	for (int i = 0; i <cont; i++)
	{
		arch << linea[i];
		arch << "\n";
	}
	arch.close();
	a.close();
}

void Objeto::imprimeDatos()
{
	cout << "<---" << archivo << "--->" << endl;
	cout << "<-----Vertices----->" << endl;
	for (int i = 0; i < vertices.size(); i++)
	{
		cout << "V" << i << "(" << vertices[i].x << "," << vertices[i].y << "," << vertices[i].z << ")" << endl;
	}
	cout << "<-----Caras----->" << endl;
	for (int j = 0; j < indicesface.size(); j++)
	{
		cout << "F" << j << "(" << indicesface[j].ind1 << "," << indicesface[j].ind2 << "," << indicesface[j].ind3 << ")" << endl;
	}
	
}

void Objeto::GuardaVertices()
{

	ifstream a;
	vector<string> result;
	string token;
	int tam;
	char espacio = ' ';
	a.open("vertices.obj", ios::in);//se abre el archivo en modo lectura 
	if (a.fail())
	{
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	while (!a.eof())//mientras que no sea el final del texto 
	{
		
		//aqui se esta dividiendo por espacios pero hay que tener en cuenta como esta el archivo
		getline(a, token, espacio);
		//se agrega un token el token es la seccion del string despues del espacio 
		if (token.compare("") != 0)
			result.push_back(token);

	}
	//imprime lo que hay en result 
	tam = result.size();//tamaño del vector 
						/*for (int i = 0; i < tam; i++)
						{
						cout << result[i] << endl;
						}*/
						//ahora agregamos los valores en el vector de vertices
						//convertimos de string a float 
	vector <float> valores;
	string valorAux;
	float valor;
	for (int i = 0; i < tam; i++)
	{
		valorAux = result[i];
		valor = strtof((valorAux).c_str(), 0);
		valores.push_back(valor);

	}
	//int ta = valores.size();
	int pos = 1;
	//ta = ta /3;
	for (int i = 0; i < cont; i++)
	{

		vertex v = vertex(valores[pos], valores[pos + 1], valores[pos + 2]);
		vertices.push_back(v);
		pos = pos + 3;

	}


	
	//tambien hay que checar cuantos vertices tiene el objeto porque hay que cambiar el numero en el guardado
	// esta cargado el 8 para el cube

	/*impresion de los flotantes
	int tam2 = valores.size();
	for (int i = 0; i < tam2; i++)
	{
	cout << valores[i] << endl;
	}*/

}
/*---------------------------------empezamos con los indices de las caras f------------------------------*/
void Objeto::ObtenIndicesF()
{

	ifstream a;
	vector<string> result;
	string token;
	int tam;
	char espacio = ' ';
	a.open("face.obj", ios::in);//se abre el archivo en modo lectura 
	if (a.fail())
	{
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	while (!a.eof())//mientras que no sea el final del texto 
	{
		//aqui se esta dividiendo por espacios pero hay que tener en cuenta como esta el archivo
		getline(a, token, espacio);
		//se agrega un token el tojen es la seccion del string despues del espacio 
		if (token.compare("") != 0)
			result.push_back(token);

	}
	//imprime lo que hay en result 
	tam = result.size();//tamaño del vector 
						/*for (int i = 0; i < tam; i++)
						{
						cout << result[i] << endl;
						}*/
						//ahora agregamos los valores en el vector de vertices
						//convertimos de string a int
	vector <int> valores;
	vector<int> aux;
	string valorAux;
	int valor;
	for (int i = 0; i < tam; i++)
	{
		
		valorAux = result[i];
		valor = atoi(valorAux.c_str());
		valores.push_back(valor);
	}
	int ite = 0;
	for (int x = 0; x < valores.size(); x++)
	{
		if (valores[x]==0)
		{
			cout << valores[x] << endl;
		}
		else
		{
			aux.push_back(valores[x]);
		}
		
		
	}
	for (int i = 0; i < aux.size(); i++)
	{
		cout << "aux";
		cout << aux[i] << endl;
	}
	//int ta = valores.size();
	int pos = 0;
	//ta = ta /3;
	for (int i = 0; i < cont; i++)
	{

		faces f = faces(aux[pos] - 1, aux[pos + 1] - 1, aux[pos + 2] - 1);
		indicesface.push_back(f);
		pos = pos + 3; //3
	}


	//la conversion es correcta, solo que cierra valores por ejemplo 999 se convierte 1000
	//tambien hay que checar cuantos vertices tiene el objeto porque hay que cambiar el numero en el guardado
	// esta cargado el 8 para el cube

	/*impresion de los flotantes
	int tam2 = valores.size();
	for (int i = 0; i < tam2; i++)
	{
	cout << valores[i] << endl;
	}*/

}
void Objeto::draw()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);
	glLoadIdentity();

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

		for (int i = 0; i < indicesface.size(); i++)
		{
			glBegin(GL_POLYGON);
			glColor3f(0.0, 1.0, 0.0);

			glVertex3f(vertices[indicesface[i].ind1].x, vertices[indicesface[i].ind1].y, vertices[indicesface[i].ind1].z);
			glVertex3f(vertices[indicesface[i].ind2].x, vertices[indicesface[i].ind2].y, vertices[indicesface[i].ind2].z);
			glVertex3f(vertices[indicesface[i].ind3].x, vertices[indicesface[i].ind3].y, vertices[indicesface[i].ind3].z);

			//	cout << float (indicesface[2].ind1);
			//	cout << indicesface[2].ind2;
			//	cout << indicesface[2].ind3;
			//	glVertex3f(vertices[indicesface[0].ind1].x, vertices[indicesface[0].ind1].y, vertices[indicesface[0].ind1].z);
		glEnd();
		}		
	glFlush();
	glutSwapBuffers();
		
}
//

//open gl
void displayMe()
{
		
		if (bandera == 0)
		{


			string nombre = "";
			cout << "Dame el nombre del archivo: ";
			cin >> nombre;
			nombre = nombre + ".obj";
			o.archivo = nombre;
			
		//	Objeto obj = Objeto(nombre);
			
			o.imprimir(1);//aqui se guardan los datos en los nuevos archivos dependiendo la opcion actualmente los v 
			o.GuardaVertices();
			o.imprimir(2);//aqui se uardan las caras
			o.ObtenIndicesF();
			bandera = 1;
		}

		//obj.imprimeDatos();
		if (bandera == 1)
		{

			o.draw();
			bandera = 1;
		}
		
	
	
}

void specialKeys(int key, int x, int y) 
{

		//  Flecha derecha: aumentar rotación 5 grados
	if (key == GLUT_KEY_RIGHT)
	{
		rotate_y += 5;
		cout << "ENTRO";
	}
		//  Flecha izquierda: disminuir rotación 5 grados
		else if (key == GLUT_KEY_LEFT)
		{
			rotate_y -= 5;
			cout << "ENTRO";
		}
		

		else if (key == GLUT_KEY_UP)
		{
			rotate_x += 5;
			cout << "ENTRO";
		}
		

		else if (key == GLUT_KEY_DOWN)
		{
			rotate_x -= 5;
			cout << "ENTRO";
		}
		//  Solicitar actualización de visualización
		glutPostRedisplay();

	}

//inici0
void inicio(void)
{
	/* Activamos la matriz de proyeccion. */
	//glMatrixMode(GL_PROJECTION);

	/* "Reseteamos" esta con la matriz identidad. */
//	glLoadIdentity();

	/* Plano de proyeccion igual a la ventana
	* de visualizacion.
	* Volumen de visualizacion
	* desde z=-10 hasta z=10.*/
	//glOrtho(ORIGENX+90, ANCHO-140, ORIGENY+90, ALTO-140, -10, 10);
	//glOrtho(170, ANCHO-170 , 170 , ALTO-170, -10, 10);
//	glOrtho(185, ANCHO - 155, 185, ALTO - 155, -10, 10);
	//glOrtho(-10, 400, -10, 400, -7, 6);
	//gluOrtho2D(1,1,1,1);
	//gluOrtho2D(-10, 100, -10, 100);
//	gluLookAt(0, 5, 5, 0, 0, 0, 0, 1, 0);

	/* Activamos la matriz de modelado/visionado. */
//	glMatrixMode(GL_MODELVIEW);

	/* La "reseteamos". */
	//glLoadIdentity();

	/* Nos trasladamos al centro de nuestra
	* ventana donde siempre dibujaremos el
	* poligono.
	* Nos mantenemos en el plano z=5 que se encuentra
	* dentro del volumen de visualizacion.*/

//	glTranslatef((GLfloat)ANCHO / 2, (GLfloat)ALTO / 2, 5.0);

	/* Color de fondo para la ventana
	* de visualizacion, negro. */
//	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glViewport(0, 0, ANCHO, ALTO);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	glOrtho(-8, 5, -8, 5, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

}



int main(int argc, char** argv)
{
	
	
	
	//string nombre="";
	//cout << "Dame el nombre del archivo: ";
	//cin >> nombre;
	//nombre = nombre + ".obj";
	//Objeto o = Objeto(nombre);
	//opcion 1=v 2=f  3=vn
	//o.imprimir(1);//aqui se guardan los datos en los nuevos archivos dependiendo la opcion actualmente los v 
	//o.GuardaVertices();
	//o.imprimir(2);//aqui se uardan las caras
	//o.ObtenIndicesF();
	//o.imprimeDatos();
	//opengl
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ANCHO,ALTO);
	glutInitWindowPosition(ORIGENX,ORIGENY);
	glutCreateWindow("Lector");
//	glEnable(GL_DEPTH_TEST);//cambio
	inicio();
	//glEnable(GL_DEPTH_TEST);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(displayMe);
	
	
	//glutSpecialFunc(specialKeys);
	


	glutMainLoop();
	
	return 0;
//	system("pause");
//	getchar();

}
