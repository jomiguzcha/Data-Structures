#pragma once

template <class T>
class Nodo_T{
public:
	Nodo_T<T> * nodos[2];
	T x;
	Nodo_T(T _x) {
		nodos[0] = 0;
		nodos[1] = 0;
		x = _x;
	};
};

