#include <iostream>
#include "BTree.h"

using namespace std;

template<class T>
struct Asc{
	T operator()(T a, T b) {
		return a < b;
	}
};

template<class T>
struct Des{
	T operator()(T a, T b) {
		return a > b;
	}
};

template<class T, class O, O N>
struct bidoof{                     
	typedef typename bidoof<T, O, N> B;
	typedef typename nodo<B, N> Nodo;
	typedef typename O O;
	typedef typename T T;
	O t = N;
};

int main(){
	BTree<bidoof<int,int,4>,Asc <int>> a;

	a.insert(1);
	a.insert(8);
	a.insert(3);
	a.insert(2);
	
	system("pause");
	return 0;
}