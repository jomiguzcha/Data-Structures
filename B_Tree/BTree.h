#pragma once
#include <iostream>
#include "nodo.h"

using namespace std;

template<class B, class Ord>
struct BTree{
	B a;
	Ord orden;
	typedef typename B::Nodo Nodo; 
	typedef typename B::O O;
	typedef typename B::T T;
	O t = a.t;

	Nodo* root = NULL;

	bool find(T v, Nodo** &ptr, int &i);
	bool insert(T v);
	bool remove(T v);
	void print();

};

template<class B, class ord>
inline bool BTree<B, ord>::find(T v, Nodo **& ptr, int & i) {
	ptr = &root;
	while (*ptr){ //busca en los nodos
		i = 0;

		while ((*ptr)->ar[i] >= 0 && orden((*ptr)->ar[i], v) && i < t) {  //verifica si v es mayor que los valores ya colocados
			i++;
		}

		if ((*ptr)->ar[i] == v) {//si se encuentra un valor igual, significa que ya lo encontró
			return 1;
		}

		if(!(*ptr)->arr_ptr[i]){//Pregunta si tiene hijos
			return 0;
		}

		else {
			ptr = &((*ptr)->arr_ptr[i]);//actualiza el ptr
			continue;		
		}
	}
	return 0;
}

template<class B, class ord>
inline bool BTree<B, ord>::insert(T v) {
	Nodo** ptr=NULL;
	int i = 0;
	if (find(v, ptr, i)) {
		return 0;
	}
	
	if (!*ptr) { // Si el root es vacio
		Nodo *nn = new Nodo;
		*ptr = nn;
		(*ptr)->ar[i] = v;
	}

	else if ((*ptr)->ar[i] ==- 1) {// Si la posicion donde deberia estar es vacia
		(*ptr)->ar[i] = v;
	}

	else if ((*ptr)->ar[i] !=-1 && (*ptr)->ar[t - 1] == -1 ) {// Si la posicion donde deberia estar es ocupada pero el nodo no esta lleno
		for (int tmp = 0; tmp < (t - i - 1); tmp++) {
			(*ptr)->ar[t - 1 - tmp] = (*ptr)->ar[t - 2 - tmp];
		}
		(*ptr)->ar[i] = v;
	}
	
	else if ((*ptr)->ar[i] != -1 && (*ptr)->ar[t - 1] != -1) {// Si la posicion donde deberia estar es ocupada y el nodo esta lleno
		T arr_exploid[t + 1];
		arr_exploid[i] = v;
		for (int j = 0; j < i; j++) {
			arr_exploid[j] = (*ptr)->ar[j]->v;}
		for (int j = i + 1; j < t + 1; j++) {
			arr_exploid[j] = (*ptr)->ar[j - 1]->v;}

		int elem_medio = (t+1) / 2;

		Nodo *n_root = new Nodo;
		(*n_root)->ar[0] == arr_exploid[elem_medio];

		Nodo *nn2 = new Nodo;
		
		nn1->ar[0]=(*ptr)->ar[elem_medio];
		(*ptr)->ar[elem_medio]=NULL;
	}

	return 1;
}

template<class B, class Ord>
inline bool BTree<B, Ord>::remove(T v){



	return false;
}

template<class B, class Ord>
inline void BTree<B, Ord>::print(){






}
