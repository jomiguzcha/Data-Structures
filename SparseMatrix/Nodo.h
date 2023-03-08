#pragma once
#include <iostream>

template<class T>
struct Nodo{
	Nodo(int _x, int _y,T d) {
		dato = d;
		x = _x;
		y = _y;
		right = NULL;
		down = NULL;
	};

	T dato;
	Nodo<T>* right;
	Nodo<T>* down;
	int x; //Fila
	int y; //Columna
};
