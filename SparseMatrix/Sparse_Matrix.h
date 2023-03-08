#pragma once
#include <iostream>
#include "Nodo.h"
#include "ObjX.h"

using namespace std;

template<class T, T N>
struct Sparse_Matrix{
	Sparse_Matrix(int _r, int _c) {
		r = _r;
		c = _c;
		rows = new Nodo<T>*[_r];
		columns = new Nodo<T>*[_c];

		for (int i = 0; i < _r; i++) { rows[i] = 0;};
		for (int j = 0; j < _c; j++) { columns[j] = 0;};
	}
	
	typedef Sparse_Matrix<T, N> esparsa;
	typedef T type;

	bool find(int a,int b,Nodo<T>**&p, Nodo<T>** &q);
	void insert(int a, int b,T c, Nodo<T>** p, Nodo<T>** q);
	void remove(int a,int b, Nodo<T>** p, Nodo<T>** q);
	void set(int a, int b, T c);
	T get(int a, int b);
	void print();
	void print_c();

	ObjX<esparsa> operator()(int a, int b) {
		ObjX<esparsa> z(a, b, this);
		return z;
	}

	Nodo<T>** rows;
	Nodo<T>** columns;
	int r, c;
};

template<class T, T N>
inline bool Sparse_Matrix<T, N>::find(int a, int b, Nodo<T>** &p, Nodo<T>** &q){
	p = &rows[a];
	while (*p!=0 && (*p)->y < b) {
		p = &((*p)->down);
	}

	q = &columns[b];
	while (*q!=0 && (*q)->x < a) {
		q = &((*q)->right);
	}

	return (*p==*q) && *p && *q;
}

template<class T, T N>
inline void Sparse_Matrix<T, N>::insert(int a, int b, T c, Nodo<T>** p, Nodo<T>** q){
	Nodo<T>* aux = new Nodo<T>(a,b,c);
	aux->down = *p;
	*p = aux;
	aux->right = *q;
	*q = aux;
}

template<class T, T N>
inline void Sparse_Matrix<T, N>::remove(int a, int b, Nodo<T>** p, Nodo<T>** q){
	Nodo<T>* aux = *p;
	*p = aux->down;
	*q = aux->right;
	delete aux;
}

template<class T, T N>
inline void Sparse_Matrix<T, N>::set(int a, int b, T c){
	Nodo<T>** p=0; Nodo<T>** q=0;
	bool func = find(a, b, p, q);
	if (!func) {
		insert(a, b, c, p, q);
	}
	else if (func && c != N) {
		(*p)->dato = c;
	}
	else if (func && c == N) {
		remove(a, b,p,q);
	}
}

template<class T, T N>
inline T Sparse_Matrix<T, N>::get(int a, int b){
	Nodo<T>** p = 0; Nodo<T>** q = 0;
	if (!find(a, b, p, q)) {
		return N;
	}
	else if(find(a, b, p, q)){
		return (*p)->dato;
	}
}

template<class T, T N>
inline void Sparse_Matrix<T, N>::print(){
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << get(i,j) <<"  ";
		}
		cout << endl;
	}
}

template<class T, T N>
inline void Sparse_Matrix<T, N>::print_c() {
	T a;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			a=get(i, j);
			if (a == 0) {
				cout << "   ";
			}
			else {
				cout << a << "  ";
			}
		}
		cout << endl;
	}
}
