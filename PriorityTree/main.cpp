#include <iostream>
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

int main() {
	Tree<int, Asc<int>> t;
	int arr[10] = {10,9,8,7,6,5,4,3,2,1};
	/*int n = 10;
	for (int i = 0; i < n; i++) {
		t.insert(rand() % 100);
	}*/

	int z;
	for (int i = 0; i < 10; i++) {
		/*cout << "Dato: ";
		cin >> z;
		t.insert(z);*/
		t.insert(arr[i]);
	}

	t.print();

	while (1) {
		system("pause");
		t.remove();
		cout << "Eliminando: "<<endl;
		t.print();
	}
	/*
	t.preorden(0);cout << endl;
	t.print_mat();cout << endl;*/

	system("pause");
	return 0;
}