#pragma once
#include "Lista.h"
#include "Tree.h"

template<class E>
struct Adaptor{
	Adaptor() {};
	
	typedef typename E::type T;
	
	bool find(T);
	bool insert(T);
	bool remove(T);
	void mostrar();

	E i;
};

template<class E>
inline bool Adaptor<E>::find(T x){
	return i.find(x);
}

template<class E>
inline bool Adaptor<E>::insert(T x){
	return i.insert(x);	
}

template<class E>
inline bool Adaptor<E>::remove(T x){
	return i.remove(x);	
}

template<class E>
inline void Adaptor<E>::mostrar(){
	i.mostrar();
}
