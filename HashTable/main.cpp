#include <iostream>
#include "HashT.h"
#include "Adaptor.h"
#include "Lista.h"
#include "Tree.h"

using namespace std;

template <class T>
struct Asc {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T>
struct Desc {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template<class T, T n>
struct Disp{
	T operator()(T x) {
		return x % n ;
	}
};


int main() {
	int n = 10;
	int arr[] = {9,54,45,95,74,62,37,465,123,78};

	HashT<int, Disp<int,5> , Adaptor <Lista<int,Asc<int>>> , 10> h_l;
	for (int i = 0; i < n; i++) {
		//h_l.insert(rand() % 100);
		h_l.insert(arr[i]);
	}
	h_l.show();

	HashT<int, Disp<int,5>, Adaptor <Tree<int,Asc<int>>>, 5> h_t;
	for (int i = 0; i < n; i++) {
		//h_t.insert(rand() % 1000);
		h_t.insert(arr[i]);
	}
	h_t.show();

	system("pause");
	return 0;
}