#pragma once
#include <vector>

using namespace std;

template <class G>
struct Edge{
	typedef typename G::E E;
	typedef typename G::Nodo Nodo;
	E peso;
	Nodo* nodos[2];
	bool dir;
	
	Edge(E p,Nodo* a,Nodo*b,bool d) {
		peso = p;
		nodos[0] = a;
		nodos[1] = b;
		dir = d;	
	}

};

