#pragma once
#include "Nodo.h"
#include "Lista.h"

template <class T>
struct Iterator_list{
	Iterator_list(Nodo<T> *_p=0) {
		p = _p;
	};

	Iterator_list<T> operator=(Iterator_list<T> i) {
		p = i.p;
		return i;
	}

	bool operator!=(Iterator_list<T> i) {
		return p != i.p;
	}

	Iterator_list<T> operator++(int) {
		p = p->next;
		return *this;
	}

	T operator*() {
		return p->dato;
	}

	Nodo<T> *p;

};