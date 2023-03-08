#pragma once
#include <iostream>

template <class T>
class Nodo {
public:
	Nodo(T _dato) {
		dato = _dato;
		next = NULL;
	}

	T dato;
	Nodo * next;
};
