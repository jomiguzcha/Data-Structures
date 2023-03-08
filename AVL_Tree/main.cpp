#include <iostream>
#include "Tree.h"
#include "Tree_iterator.h"
#include <time.h>

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

	int arr[] = {1,8,3,7,2,9,4,5,6};
	for (int i = 0; i < 9; i++) {
		t.insert(arr[i]);
		t.mostrar_endl();
		cout << "//////////////////////////////////////////////"<<endl;
	}

	int a; int num;
	/*cout << "Cantidad de numeros a insertar:"; // INSERTADO POR PEDIDO
	cin >> num;
	for (int i = 0; i < num; i++) {
		cout << "Numero:";
		cin >> a;
		t.insert(a);
	}*/
	
	/*for (int j = 0; j < 10; j++) {  //INSERTADO RANDOM
		t.insert(rand() % 100);
	}*/

	t.mostrar_endl();
	cout << endl;

	cout << "Cantidad de numeros a eliminar:";
	cin >> num;
	for (int i = 0; i < num; i++) {
		cout << "Numero:";
		cin >> a;
		t.remove(a);
	}

	t.mostrar_endl();
	cout << endl;

	system("pause");
	return 0; 
}