#pragma once

template <class T>
class Nodo{
public:
	Nodo<T> * nodos[2];
	T x;
	int peso;
	Nodo(T _x) {
		nodos[0] = 0;
		nodos[1] = 0;
		x = _x;
		peso = 0;
	};
};

