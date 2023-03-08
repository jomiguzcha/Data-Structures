#pragma once
#include <iostream>
#include "Nodo.h"
#include "Iterator_list.h" 

using namespace std;

template<class T,class O>
class Lista{
public:
	Lista() { head = NULL; };
	~Lista() {};

	void mostrar();
	bool find(T, Nodo<T> **&p);
	bool insert(T x);
	bool remove(T x);
	typedef T type;
	typedef Iterator_list<T> iterator;

	iterator begin() {
		return iterator(head);
	}

	iterator end() {
		return iterator();
	}

	Nodo<T> * head;
	O o;
};

template<class T, class O>
inline void Lista<T, O>::mostrar(){
	Nodo<T> **p = &head;
	while (*p!=NULL) {
		cout << "-->";
		cout << (*p)->dato;
		p = &((*p)->next);
	}
	cout << "-->NULL" << endl;
}

template<class T, class O>
inline bool Lista<T, O>::find(T x, Nodo<T>**& p){
	p = &head;
	while (*p!=NULL && o((*p)->dato, x)) {
		p = &((*p)->next);
	}
	return *p && (**p).dato == x;
}

template<class T, class O>
inline bool Lista<T, O>::insert(T x){
	Nodo<T> **p;
	if (find(x, p)) {
		return 0;
	}
	Nodo<T>* t = new Nodo<T> (x);
	t->next = (*p);
	*p = t;

	return 1;
}

template<class T, class O>
inline bool Lista<T, O>::remove(T x){
	Nodo<T>** p;
	if (!find(x, p)) {
		return 0;
	}
	Nodo<T>* t = *p;
	*p = t->next;
	delete t;

	return 1;
}
