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
#include<time.h>



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
void MultMatriz4x1(GLfloat m[4][4], GLfloat v[4]);
//bezzier
int nPuntos = 0;
GLfloat anguloCuboX = 0.0f;
GLfloat anguloCuboY = 0.0f;
float LightPos[] = { 1.0f, 0.5f, 1.0f, 0.0f };   // Light Position
float LightAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f };   // Ambient Light Values
float LightDif[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // Diffuse Light Values
float LightSpc[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // Specular Light Values

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
//Calcular Bezier
Point drawBezier(Point A, Point B, Point C, Point D, double t) {
	//VARIABLE AUX PARA PASAR LOS NUEVOS PUNTOS
	Point P;
	P.x = pow((1 - t), 3) * A.x + 3 * t * pow((1 - t), 2) * B.x + 3 * (1 - t) * pow(t, 2)* C.x + pow(t, 3)* D.x;
	P.y = pow((1 - t), 3) * A.y + 3 * t * pow((1 - t), 2) * B.y + 3 * (1 - t) * pow(t, 2)* C.y + pow(t, 3)* D.y;
	P.z = pow((1 - t), 3) * A.z + 3 * t * pow((1 - t), 2) * B.z + 3 * (1 - t) * pow(t, 2)* C.z + pow(t, 3)* D.z;
	return P;
}
//metodo de dibujado
void drawLine(Point p1, Point p2) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.5, 0.0);//color naranja
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
	glFlush();
}

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
Objeto o = Objeto(""); //pelota
Objeto o2 = Objeto(""); //canasta
//en este metodo se genera la lectura del archivo obj original y se crea otro dependiendo de la opcion 
//donde se guardara el de vertices o face
///
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
		//cout << texto << endl;
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
//	for (int i = 0; i < aux.size(); i++)
//	{
//		cout << "aux";
//		cout << aux[i] << endl;
//	}
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
	
	//iluminacion
	/* Activo la fuente de luz */


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	//iluminacion
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/* Activo la fuente de luz */
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);        // Set Light1 Position
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);         // Set Light1 Ambience
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);         // Set Light1 Diffuse
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpc);        // Set Light1 Specular
	glEnable(GL_LIGHT0);                                // Enable Light1
	glEnable(GL_LIGHTING);

	/* Propiedades del material del Objeto*/
	GLfloat mat_ambient[] = { 1.0,0.5,0.0,0.0 };
	GLfloat mat_diffuse[] = { 1.0, 0.7f, 0.0f, 0.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 120.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//menu


	int n, n2, opcion, numero;
	GLfloat px = 0.0;
	GLfloat py = 0.0;
	GLfloat pz = 0.0;

	GLfloat qx = 0.0;
	GLfloat qy = 0.0;
	GLfloat qz = 0.0;

	GLfloat nx = 0.0;
	GLfloat ny = 0.0;
	GLfloat nz = 0.0;
	
	GLfloat modulo = 0.0;
	do
	{
		cout << "Baloncesto\n";
		cout << "1.- EMPEZAR\n";
		cout << "2.- Salir\n";
		cout << "Dame tu Opcion: ";
		cin >> opcion;
		srand(time(NULL));
		numero = rand()%2;
		/* Inicio del anidamiento */
		switch (opcion)
		{
		case 1:
		//	cout << "Valores de Camara\n";
		//	cout << "X: ";
		//	cin >> n;
		//	cout << "Y: ";
		//	cin >> n2;
			for (int i = 1; i <= 3; i++)
			{
				if(numero==0)
				{ 
					switch (i)
					{
					case 1:
						abc[0].setxyz(-0.9, 0.0, 0.1);
						abc[1].setxyz(-0.4, 1.0, 0.1);
						abc[2].setxyz(0.0, 1.0, 0.1);
						abc[3].setxyz(0.1, 0.0, 0.1);
						nPuntos = 4;
						break;
					case 2:
						abc[0].setxyz(0.1, 0.0, 0.1);
						abc[1].setxyz(0.2, 0.5, 0.1);
						abc[2].setxyz(0.3, 0.5, 0.1);
						abc[3].setxyz(0.4, 0.0, 0.1);
						nPuntos = 4;
						break;
					case 3:
						abc[0].setxyz(0.4, 0.0, 0.1);
						abc[1].setxyz(0.5, 0.3, 0.1);
						abc[2].setxyz(0.6, 0.3, 0.1);
						abc[3].setxyz(0.7, 0.0, 0.1);
						nPuntos = 4;
						break;
					default:
						break;
					}
				}
				else
				{
					switch (i)
					{
					case 1:
						abc[0].setxyz(-0.9, 0.0, -0.4);
						abc[1].setxyz(-0.6, 1.0, -0.4);
						abc[2].setxyz(-0.4, 1.0, -0.4);
						abc[3].setxyz(-0.1, 0.7, -0.4);
						nPuntos = 4;
						break;
					case 2:
						abc[0].setxyz(-0.1, 0.7, -0.4);
						abc[1].setxyz(-0.2, 0.9, -0.4);
						abc[2].setxyz(-0.2, 0.9, -0.4);
						abc[3].setxyz(-0.3, 0.0, -0.4);
						nPuntos = 4;
						break;
					case 3:
						abc[0].setxyz(-0.3, 0.0, -0.4);
						abc[1].setxyz(-0.4, 0.3, -0.4);
						abc[2].setxyz(-0.6, 0.3, -0.4);
						abc[3].setxyz(-0.7, 0.0, -0.4);
						nPuntos = 4;
						break;
					default:
						break;
					}

				}

				GLfloat vPuntos[4];
				GLfloat vPuntos1[4];
				GLfloat vPuntos2[4];
				Point pAnterior = abc[0];
				GLfloat vBezier[4];
				//GLfloat MFINAL[4][4];
				// dibuja por medio de linea, e incrementa t lentamente para una curva mas detallada 
				for (double t = 0.0; t <= 1.0; t += 0.009) {
					Point P = drawBezier(abc[0], abc[1], abc[2], abc[3], t);
					//	getchar();
					drawLine(pAnterior, P);
					vBezier[0] = P.x;
					vBezier[1] = P.y;
					vBezier[2] = P.z;
					vBezier[3] = 1;
					pAnterior = P;
					GLfloat MT[4][4] = {
						{ 1.0f,0.0f,0.0f,vBezier[0] },
						{ 0.0f,1.0f,0.0f,vBezier[1] },
						{ 0.0f,0.0f,1.0f,vBezier[2] },
						{ 0.0f,0.0f,0.0f,vBezier[3] } };
				
					
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();

					glRotatef(rotate_x, 1.0, 0.0, 0.0);
					glRotatef(rotate_y, 0.0, 1.0, 0.0);

				//	glRotatef(n, 0.0f, 1.0f, 0.0f);
				//	glRotatef(n2, 1.0f, 0.0f, 0.0f);

				/*	glBegin(GL_LINES);
					glColor3f(1.0, 1.0, 1.0);
					glVertex3f(0.0, 1.0, 0.0);
					glVertex3f(0.0, -1.0, 0.0);
					glVertex3f(1.0, 0.0, 0.0);
					glVertex3f(-1.0, 0.0, 0.0);
					glEnd();*/

					
					

					for (int i = 0; i < o.indicesface.size(); i++)
					{

						vPuntos[0] = o.vertices[o.indicesface[i].ind1].x;
						vPuntos[1] = o.vertices[o.indicesface[i].ind1].y;
						vPuntos[2] = o.vertices[o.indicesface[i].ind1].z;
						vPuntos[3] = 1.0f;

						vPuntos1[0] = o.vertices[o.indicesface[i].ind2].x;
						vPuntos1[1] = o.vertices[o.indicesface[i].ind2].y;
						vPuntos1[2] = o.vertices[o.indicesface[i].ind2].z;
						vPuntos1[3] = 1.0f;

						vPuntos2[0] = o.vertices[o.indicesface[i].ind3].x;
						vPuntos2[1] = o.vertices[o.indicesface[i].ind3].y;
						vPuntos2[2] = o.vertices[o.indicesface[i].ind3].z;
						vPuntos2[3] = 1.0f;

						MultMatriz4x1(MT, vPuntos2);
						MultMatriz4x1(MT, vPuntos);
						MultMatriz4x1(MT, vPuntos1);

						px = vPuntos1[0] - vPuntos[0];
						py = vPuntos1[1] - vPuntos[1];
						pz = vPuntos1[2] - vPuntos[2];

						qx = vPuntos2[0] - vPuntos[0];
						qy = vPuntos2[1] - vPuntos[1];
						qz = vPuntos2[2] - vPuntos[2];

						nx = (py*qz) - (pz*qy);
						ny = (pz*qx) - (px*qz);
						nz = (px*qy) - (py*qx);

						modulo = sqrt(nx*nx + ny*ny + nz*nz);

						nx = nx / modulo;
						ny = ny / modulo;
						nz = nz / modulo;

						
						glBegin(GL_TRIANGLES);
						glNormal3f(nx, ny, nz);
						//glColor3f(1.0, 0.5, 0.0);
						glVertex3f(vPuntos[0], vPuntos[1], vPuntos[2]);
						glVertex3f(vPuntos1[0], vPuntos1[1], vPuntos1[2]);
						glVertex3f(vPuntos2[0], vPuntos2[1], vPuntos2[2]);
						glEnd();

					}
					for (int i = 0; i < o2.indicesface.size(); i++)
					{
						//VERTICE 1
						vPuntos[0] = o2.vertices[o2.indicesface[i].ind1].x;
						vPuntos[1] = o2.vertices[o2.indicesface[i].ind1].y;
						vPuntos[2] = o2.vertices[o2.indicesface[i].ind1].z;
						vPuntos[3] = 1.0f;
						//VERTICE 2
						vPuntos1[0] = o2.vertices[o2.indicesface[i].ind2].x;
						vPuntos1[1] = o2.vertices[o2.indicesface[i].ind2].y;
						vPuntos1[2] = o2.vertices[o2.indicesface[i].ind2].z;
						vPuntos1[3] = 1.0f;
						//VERTICE 3
						vPuntos2[0] = o2.vertices[o2.indicesface[i].ind3].x;
						vPuntos2[1] = o2.vertices[o2.indicesface[i].ind3].y;
						vPuntos2[2] = o2.vertices[o2.indicesface[i].ind3].z;
						vPuntos2[3] = 1.0f;

						px = vPuntos1[0] - vPuntos[0];
						py = vPuntos1[1] - vPuntos[1];
						pz = vPuntos1[2] - vPuntos[2];

						qx = vPuntos2[0] - vPuntos[0];
						qy = vPuntos2[1] - vPuntos[1];
						qz = vPuntos2[2] - vPuntos[2];

						nx = (py*qz) - (pz*qy);
						ny = (pz*qx) - (px*qz);
						nz = (px*qy) - (py*qx);

						modulo = sqrt(nx*nx + ny*ny + nz*nz);

						nx = nx / modulo;
						ny = ny / modulo;
						nz = nz / modulo;

						/*	cout << "VERTICE NUMERO: " << i <<"\n";
						cout << "NX: " << nx << "\n";
						cout << "NY: " << ny << "\n";
						cout << "NZ: " << nz <<"\n";*/

						//getchar();

						glBegin(GL_TRIANGLES);
						glNormal3f(nx, ny, nz);
						//glColor3f(0.0, 0.0, 1.0);
						glVertex3f(vPuntos[0], vPuntos[1], vPuntos[2]);
						glVertex3f(vPuntos1[0], vPuntos1[1], vPuntos1[2]);
						glVertex3f(vPuntos2[0], vPuntos2[1], vPuntos2[2]);
						glEnd();
					}
				}
				nPuntos = 0;
			}
			
		
			glFlush();
			glutSwapBuffers();
			break;
		case 2: cout << "Opcion numero 3";
			opcion = 2;
			exit(-1);
			break;
		}
	} while (opcion != 2);

		//PUNTOS DE REFERENCIA
}
//
//open gl
void displayMe()
{
		
		if (bandera == 0)
		{
			string nombre = "";

			/*cout << "Dame el nombre del archivo: ";
			cin >> nombre;
			nombre = nombre + ".obj";*/
			//string nombre = "balon2.0.obj";
			nombre = "balon2.obj";
			o.archivo = nombre;			
			o.imprimir(1);//aqui se guardan los datos en los nuevos archivos dependiendo la opcion actualmente los v 
			o.GuardaVertices();
			o.imprimir(2);//aqui se uardan las caras
			o.ObtenIndicesF();
			string nombre2 = "";

			/*cout << "Dame el nombre del archivo: ";
			cin >> nombre;
			nombre = nombre + ".obj";*/
			//string nombre = "balon2.0.obj";
			nombre2 = "canasta3.obj";
			o2.archivo = nombre2;
			o2.imprimir(1);//aqui se guardan los datos en los nuevos archivos dependiendo la opcion actualmente los v 
			o2.GuardaVertices();
			o2.imprimir(2);//aqui se uardan las caras
			o2.ObtenIndicesF();

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
		rotate_y += 5;

	//  Flecha izquierda: disminuir rotación 5 grados
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Solicitar actualización de visualización
	glutPostRedisplay();
	}

//inici0
void inicio(void)
{
	
}
int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ANCHO*2,ALTO*2);
	glutCreateWindow("Baloncesto");
	//inicio();
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(displayMe);
	glutMainLoop();	
	
	return 0;

}

void MultMatriz4x4(GLfloat m1[4][4], GLfloat m2[4][4])
{
	GLfloat mr[4][4];
	mr[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0];
	mr[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1];
	mr[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2];
	mr[0][3] = m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3];

	mr[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0];
	mr[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1];
	mr[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2];
	mr[1][3] = m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3];

	mr[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0];
	mr[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1];
	mr[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2];
	mr[2][3] = m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3];

	mr[3][0] = m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0];
	mr[3][1] = m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1];
	mr[3][2] = m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2];
	mr[3][3] = m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3];
}
void MultMatriz4x1(GLfloat m[4][4], GLfloat v[4])
{
	//GLfloat vr[4];
	v[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3];
	v[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3];
	v[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3];
	v[3] = m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3];
}


//
