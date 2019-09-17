#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

void lectura();

int main(int argc, char **argv)
{
	lectura();
	system("pause");
	return 0;
}
void lectura()
{
	ifstream archivo;
	string texto;
	string copia = "cube.obj";


	archivo.open(copia);
	if (archivo.fail())
	{
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		cout << texto << endl;

	}
	archivo.close();
}