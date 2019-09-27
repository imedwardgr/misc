/* Programa realizado por Eduardo Gómez
Compilacion:	g++ -std=c++11 -o mt mt.cpp
Ejecucion:		mt.exe < maquina.csv

Formato del .csv:
	Linea 1: Lenguaje que se lee separado por comas, primer elemento es un *
	Linea 2: Estado de aceptacion
	Linea 3+: 	Una linea por cada estado, con sus acciones en el formato "(a:B:D)", donde  a es el estado al se cambiará
				'B' es el caracter que se sustituye en la cadena y 'D' puede ser 'D' o 'I' y es el sentido al que se mueve
				Izquierda o Derecha.
	Linea +1: 	Despues de cada estado, se coloca una linea de puras comas como separadador entre los estados y la cadena
	Linea +2: 	La cadena a evaluar por la maquina.

*/
#include <iostream>
#include <string>
#include <list>
#include <windows.h>
#include <map>
#include <vector>

#define derecha true
#define izquierda false

using namespace std;

char estadoDeAceptacion;

void MoverCursor(int x, int y){ //Función para mover el cursor
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {(SHORT)x, (SHORT)y}; 
	SetConsoleCursorPosition(hStdout, position);
	return;
}

char leerEstados(string &cadEvaluar, map< pair<char,char>, tuple<char, char, bool> > &mapaEstados){ //Leemos todos los estados del csv
	string S;
	char ans;

	getline(cin, S);
	vector<char> diccionario;
	for(int i=2; i<S.size(); i++){
		if(S[i] != ',')
			diccionario.push_back(S[i]);
	}

	cin >> estadoDeAceptacion;

	char est, x, y, z;
	bool direccion;
	bool esCadFinal=false;
	bool isFirst = true;

	while(getline(cin,S)){
		est = S[0];

		if(esCadFinal){
			cadEvaluar = S;
			return ans;
		}

		for(int i=1, lec=-1; i<S.size(); i++){
			if(S[i] == ',')
				lec++;
			if(S[i] == '('){
				x = S[i+1];
				y = S[i+3];
				z = S[i+5];

				if(isFirst){
					ans = est;
					isFirst = false;
				}

				if(z == 'D')
					direccion = derecha;
				else
					direccion = izquierda;

				mapaEstados[make_pair(est,diccionario[lec])] = make_tuple(x,y,direccion);
			}

			if(est == ','){
				esCadFinal = true;
				break;
			}
		}
	}

	return ans;
}

//Hacemos la simulacion
void maquinaDeTuring(char first, string &finalCad, map< pair<char,char>, tuple<char, char, bool> > &mapaEstados){
	int pos = 0;
	char miEstado = first;

	// cout << miEstado;
	bool encontro;
	while(1){
		system("cls");
		encontro = false;

		MoverCursor(0,2);
		cout << finalCad;
		MoverCursor(pos,3);
		cout << "^";
		MoverCursor(pos,4);
		cout << "|";
		MoverCursor(pos,5);
		cout << miEstado;
		MoverCursor(0,10);
		cout << "Estado: " << miEstado << "\n";
		cout << "Leyendo: " << finalCad[pos] << "\n";

		if(mapaEstados.count(make_pair(miEstado,finalCad[pos])) != 0)
			encontro = true;

		auto t = mapaEstados[make_pair(miEstado, finalCad[pos])];
		finalCad[pos] = get<1>(t);
		miEstado = get<0>(t);
		if(get<2>(t)) pos++;
		else pos--;

		cout << "Reemplazando con " << finalCad[pos] << "\n";
		cout << "Cambiando estado a " << miEstado << endl;
		cout << "Moviendo a ";
		if(get<2>(t)) cout << " -> \n";
		else cout << " <- \n";

		if(!encontro){
			if(miEstado == estadoDeAceptacion)
				cout << "Cadena Aceptada";
			else
				cout << "Cadena Rechazada";

			return;
		}

		Sleep(20);
	}
}

int main(){
	string finalCad;
	string cadEvaluar;
	string espacios = "BBBBBBBBBBBBBBBBBBBB";

	map< pair<char,char>, tuple<char, char, bool> > mapaEstados;
	char first = leerEstados(cadEvaluar, mapaEstados);

	cout << "Cadena a evaluar: ";

	//Concatenamos espacios en blanco para simular la cinta infinitaa
	finalCad.append(espacios);
	finalCad.append(cadEvaluar);
	finalCad.append(espacios);

	cout << finalCad << endl;

	maquinaDeTuring(first, finalCad, mapaEstados);


	return 0;
}