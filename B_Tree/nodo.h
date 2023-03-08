#pragma once

template<class B, int t>
struct nodo{
	typedef typename B::T T;
	typedef typename B::Nodo Nodo;

	T ar[t];
	Nodo* arr_ptr[t + 1];
	Nodo* p;
	nodo() {
		for (int i = 0; i < t; i++)
			ar[i] = -1;
		for (int i = 0; i < t + 1; i++)
			arr_ptr[i] = NULL;
		p = NULL;
	}
};
