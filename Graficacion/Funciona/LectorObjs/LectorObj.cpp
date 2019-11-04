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
#define TAM 5000
#define PI 3.14159265

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
void MultMatriz4x4(GLfloat m1[4][4], GLfloat m2[4][4], GLfloat m3[4][4]);

//bezzier
int nPuntos = 0;

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
	glColor3f(0.0, 1.0, 0.0);
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
Objeto o = Objeto("");
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
	tam = result.size();//tama�o del vector 
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
	tam = result.size();//tama�o del vector 
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
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	GLfloat aSen, aCos;
	aSen = sin(1 * PI / 180);
	aCos = cos(1 * PI / 180);
	int contador = 0;
	//puntos
	GLfloat puntos[4];
	GLfloat puntos1[4];
	GLfloat puntos2[4];
	//diferencia o pivotes
	GLfloat pivote[4];
	GLfloat pivote1[4];
	GLfloat pivote2[4];
	//
	GLfloat nuevox[TAM];
	GLfloat nuevoy[TAM];
	GLfloat nuevoz[TAM];

	GLfloat nuevo1x[TAM];
	GLfloat nuevo1y[TAM];
	GLfloat nuevo1z[TAM];

	GLfloat nuevo2x[TAM];
	GLfloat nuevo2y[TAM];
	GLfloat nuevo2z[TAM];

	//
	GLfloat ultimox[TAM];
	GLfloat ultimoy[TAM];
	GLfloat ultimoz[TAM];

	GLfloat ultimo1x[TAM];
	GLfloat ultimo1y[TAM];
	GLfloat ultimo1z[TAM];

	GLfloat ultimo2x[TAM];
	GLfloat ultimo2y[TAM];
	GLfloat ultimo2z[TAM];

	Point pAnterior = abc[0];
	GLfloat vBezier[4];
	//lados
	GLfloat Tl1x[TAM];
	GLfloat Tl1y[TAM];
	GLfloat Tl1z[TAM];

	GLfloat Tl2x[TAM];
	GLfloat Tl2y[TAM];
	GLfloat Tl2z[TAM];

	GLfloat Tl3x[TAM];
	GLfloat Tl3y[TAM];
	GLfloat Tl3z[TAM];


	for (int i = 0; i < indicesface.size(); i++)
	{
		Tl1x[i] = vertices[indicesface[i].ind1].x;
		Tl1y[i] = vertices[indicesface[i].ind1].y;
		Tl1z[i] = vertices[indicesface[i].ind1].z;
		//puntos[3] = 1.0f;

		Tl2x[i] = vertices[indicesface[i].ind2].x;
		Tl2y[i] = vertices[indicesface[i].ind2].y;
		Tl2z[i] = vertices[indicesface[i].ind2].z;
		//puntos1[3] = 1.0f;

		Tl3x[i] = vertices[indicesface[i].ind3].x;
		Tl3y[i] = vertices[indicesface[i].ind3].y;
		Tl3z[i] = vertices[indicesface[i].ind3].z;

		ultimox[i] = vertices[indicesface[i].ind1].x;
		ultimoy[i] = vertices[indicesface[i].ind1].y;
		ultimoz[i] = vertices[indicesface[i].ind1].z;

		ultimo1x[i] = vertices[indicesface[i].ind2].x;
		ultimo1y[i] = vertices[indicesface[i].ind2].y;
		ultimo1z[i] = vertices[indicesface[i].ind2].z;

		ultimo2x[i] = vertices[indicesface[i].ind3].x;
		ultimo2y[i] = vertices[indicesface[i].ind3].y;
		ultimo2z[i] = vertices[indicesface[i].ind3].z;




	}

	abc[0].setxyz(-0.892906, 0.010544, 0.895358);
	abc[1].setxyz(-0.490000, 1.0, 0.895358);
	abc[2].setxyz(-0.5, 1.0, 0.895358);
	abc[3].setxyz(0.0, 0.0, 0.895358);
	for (double  t = 0.0; t <= 1.0; t += 0.0005) {
		contador++;
		Point P = drawBezier(abc[0], abc[1], abc[2], abc[3], t);
		drawLine(pAnterior, P);
		pAnterior = P;
		vBezier[0] = P.x;
		vBezier[1] = P.y;
		vBezier[2] = P.z;
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0, 0.0, 0.0);
		glEnd();
		
		pivote[0] = 0.0f - Tl1x[0];
		pivote[1] = 0.0f - Tl1y[0];
		pivote[2] = 0.0f - Tl1z[0];

		pivote1[0] = 0.0f - Tl2x[0];
		pivote1[1] = 0.0f - Tl2y[0];
		pivote1[2] = 0.0f - Tl2z[0];

		pivote2[0] = 0.0f - Tl3x[0];
		pivote2[1] = 0.0f - Tl3y[0];
		pivote2[2] = 0.0f - Tl3z[0];
		for (int i = 0; i < indicesface.size(); i++)
		{

			//dibujado

			Tl1x[i] += pivote[0];
			Tl1y[i] += pivote[1];
			Tl1z[i] += pivote[2];

			Tl2x[i] += pivote1[0];
			Tl2y[i] += pivote1[1];
			Tl2z[i] += pivote1[2];

			Tl3x[i] += pivote2[0];
			Tl3y[i] += pivote2[1];
			Tl3z[i] += pivote2[2];
			//rotacion
			nuevox[i] = Tl1x[i];
			nuevoy[i] = Tl1y[i] * aCos - Tl1z[i] * aSen;
			nuevoz[i] = Tl1y[i] * aSen + Tl1z[i] * aCos;

			nuevo1x[i] = Tl2x[i];
			nuevo1y[i] = Tl2y[i] * aCos - Tl2z[i] * aSen;
			nuevo1z[i] = Tl2y[i] * aSen + Tl2z[i] * aCos;

			nuevo2x[i] = Tl3x[i];
			nuevo2y[i] = Tl3y[i] * aCos - Tl3z[i] * aSen;
			nuevo2z[i] = Tl3y[i] * aSen + Tl3z[i] * aCos;

			Tl1x[i] = nuevox[i];
			Tl1y[i] = nuevoy[i];
			Tl1z[i] = nuevoz[i];

			Tl2x[i] = nuevo1x[i];
			Tl2y[i] = nuevo1y[i];
			Tl2z[i] = nuevo1z[i];

			Tl3x[i] = nuevo2x[i];
			Tl3y[i] = nuevo2y[i];
			Tl3z[i] = nuevo2z[i];
			//traslacion Bezzier
			Tl1x[i] += vBezier[0];
			Tl1y[i] += vBezier[1];
			Tl1z[i] += vBezier[2];

			Tl2x[i] += vBezier[0];
			Tl2y[i] += vBezier[1];
			Tl2z[i] += vBezier[2];

			Tl3x[i] += vBezier[0];
			Tl3y[i] += vBezier[1];
			Tl3z[i] += vBezier[2];

			glBegin(GL_TRIANGLES);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(Tl1x[i], Tl1y[i], Tl1z[i]);
			glVertex3f(Tl2x[i], Tl2y[i], Tl2z[i]);
			glVertex3f(Tl3x[i], Tl3y[i], Tl3z[i]);
			glEnd();
			
		}
		
		//glFlush();
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
			//string nombre = "balon2.0.obj";
			o.archivo = nombre;			
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

		//  Flecha derecha: aumentar rotaci�n 5 grados
	if (key == GLUT_KEY_RIGHT)
	{
		rotate_y += 5;
		cout << "ENTRO";
	}
		//  Flecha izquierda: disminuir rotaci�n 5 grados
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
		//  Solicitar actualizaci�n de visualizaci�n
		glutPostRedisplay();

	}

//inici0
void inicio(void)
{
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0,1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ANCHO/ALTO, ANCHO / ALTO, -ANCHO / ALTO, ANCHO / ALTO, -1.0, 1.0);

}
int main(int argc, char** argv)
{
		
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ANCHO*2,ALTO*2);
	glutCreateWindow("Lector");
	inicio();
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(displayMe);
	glutMainLoop();	
	
	return 0;

}

void MultMatriz4x4(GLfloat m1[4][4], GLfloat m2[4][4],GLfloat m3[4][4])
{
	//GLfloat mr[4][4];
	m3[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0];
	m3[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1];
	m3[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2];
	m3[0][3] = m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3];

	m3[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0];
	m3[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1];
	m3[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2];
	m3[1][3] = m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3];

	m3[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0];
	m3[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1];
	m3[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2];
	m3[2][3] = m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3];

	m3[3][0] = m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0];
	m3[3][1] = m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1];
	m3[3][2] = m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2];
	m3[3][3] = m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3];
}
void MultMatriz4x1(GLfloat m[4][4], GLfloat v[4])
{
	//GLfloat vr[4];
	v[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3];
	v[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3];
	v[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3];
	v[3] = m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3];
}