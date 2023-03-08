#pragma once
#include "Lista.h"
#include "Tree.h"

template < class T, class F, class S, int z>
struct HashT{
	HashT() {};
	
	bool find(T x);
	bool insert(T x);
	bool remove(T x); 
	void show();

	F f;
	S t[z];
};

template<class T, class S, class F, int z>
inline bool HashT<T, S, F, z>::find(T x){
	int i = f(x) % z;
	return t[i].find(x);
}

template<class T, class S, class F, int z>
inline bool HashT<T, S, F, z>::insert(T x){
	int i = f(x) % z;
	return t[i].insert(x);	
}

template<class T, class S, class F, int z>
inline bool HashT<T, S, F, z>::remove(T x){
	int i = f(x) % z;
	return t[i].remove(x);
}

template<class T, class F, class S, int z>
inline void HashT<T, F, S, z>::show(){
		for (int i = 0; i < z; i++) {
			cout << i << ": ";
			t[i].mostrar();
			cout << endl;
		}
	}