#pragma once
#include <iostream>
#include "Nodo_T.h"
#include <queue>

using namespace std;

template <class T,class O>
class Tree{
public:
	Tree() { root = NULL; };
	~Tree() {};

	void Rep(Nodo_T<T>**& q, Nodo_T<T>** p);
	bool find(T x, Nodo_T<T>** &p);
	bool insert(T x);
	bool remove(T x);
	void mostrar();
	void mostrar_x(Nodo_T<T>* y);
	void Inorden(Nodo_T<T> *y);
	void Preorden(Nodo_T<T> *y);
	void Postorden(Nodo_T<T> *y);
	typedef T type;

	Nodo_T<T>* root;
	O o;
	queue<Nodo_T<T> *> cola;
};

template<class T, class O>
inline void Tree<T, O>::Rep(Nodo_T<T>**& q, Nodo_T<T>** p){
	q = &((*p)->nodos[(*p)->nodos[0] == 0]);
	while ((*q)->nodos[0] || (*q)->nodos[1]) {
		q = &((*q)->nodos[(*q)->nodos[1] != 0]);
	}
}

template<class T, class O>
inline bool Tree<T, O>::find(T x, Nodo_T<T>**& p){
	p = &root;
	while (*p && ((*p)->x != x)) {
		p = &((*p)->nodos[o((*p)->x,x)]);
	}

	return !!*p;
}

template<class T, class O>
inline bool Tree<T, O>::insert(T x){
	Nodo_T<T>** p;
	if (find(x, p)) { return 0; }
	*p = new Nodo_T<T>(x);

	return 1;
}

template<class T, class O>
inline bool Tree<T, O>::remove(T x){
	Nodo_T<T>** p;
	if (!find(x, p)) { return 0; }
	if ((*p)->nodos[0] && (*p)->nodos[1]) {
		Nodo_T<T>** q;
		Rep(q, p);
		(*p)->x = (*q)->x;
		p = q;
	}

	Nodo_T<T>* t = *p;
	*p = (*p)->nodos[(*p)->nodos[0]==0];
	delete t;

	return 1;
}

template<class T, class O>
inline void Tree<T, O>::mostrar(){
	if (root == NULL)	{
		cout << "El arbol esta vacio";
	}
	else {
		mostrar_x(root);
	}

}

template<class T, class O>
inline void Tree<T, O>::mostrar_x(Nodo_T<T>* y) {
	cola.push(y);
	while (!cola.empty()) {
		cout << (cola.front())->x << " ";
		if ((cola.front())->nodos[0] != 0) {
			cola.push((cola.front())->nodos[0]);
		}
		if ((cola.front())->nodos[1] != 0) {
			cola.push((cola.front())->nodos[1]);
		}
		cola.pop();
	}
}

template<class T, class O>
inline void Tree<T, O>::Inorden(Nodo_T<T> *y){
	if (y) { return; }
	Inorden(y->nodos[0]);
	cout << y->x;
	Inorden(y->nodos[1]);
}

template<class T, class O>
inline void Tree<T, O>::Preorden(Nodo_T<T>* y){
	if (*y) { return; }
	cout << y->x;
	Preorden(y->nodos[0]);
	Preorden(y->nodos[1]);
}

template<class T, class O>
inline void Tree<T, O>::Postorden(Nodo_T<T>* y){
	if (*y) { return; }
	Postorden(y->nodos[0]);
	Postorden(y->nodos[1]);
	cout << y->x;
}
