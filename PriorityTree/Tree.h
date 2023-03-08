#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<class T,class O>
class Tree{
public:
	Tree() {
		for (int i = 0; i < 100; i++) { arr[i][0] = -1; arr[i][1] = -1; arr[i][2] = -1; }
	};
	~Tree() {};

	bool find(T,int&);
	void adjust(int);
	bool insert(T);
	void adjust_rem();
	bool remove();
	void inorden(int);
	void preorden(int);
	void postorden(int);
	void print_mat();
	void print();
	
	T arr[100][3];
	O o;

};

template<class T, class o>
inline bool Tree<T, o>::find(T x, int& p){
	int aux= arr[0][0]; // AUX = RAIZ
	p = 0;

	while (aux != -1 && aux!=x) {
		aux = arr[++p][0];
	}

	return aux==x;
}

template<class T, class O>
inline void Tree<T, O>::adjust(int p){
	int aux = 0;

	while (1) {
		if (p % 2 == 0) {   // SI ES PAR ES HIJO DERECHO
			if (o(arr[(p - 2) / 2][0], arr[p][0])) {
				aux = arr[(p - 2) / 2][0];
				arr[(p - 2) / 2][0] = arr[p][0];
				arr[p][0] = aux;
				arr[(p - 2) / 2][2] = arr[p][0];

				p = (p - 2) / 2;
			}
			else {
				break;
			}
		}

		else { // SINO ES HIJO IZQUIERDO
			if (o(arr[(p - 1) / 2][0], arr[p][0])) {
				aux = arr[(p - 1) / 2][0];
				arr[(p - 1) / 2][0] = arr[p][0];
				arr[p][0] = aux;
				arr[(p - 1) / 2][1] = arr[p][0];

				p = (p - 1) / 2;
			}
			else {
				break;
			}
		}
	}

}

template<class T, class o>
inline bool Tree<T, o>::insert(T x){
	int p=0;
	if (find(x, p)) { return 0; }

	if (p % 2 == 0) {   // SI ES PAR ES HIJO DERECHO
		arr[(p - 2) / 2][2] = x;
	}
	else { // SINO ES HIJO IZQUIERDO
		arr[(p - 1) / 2][1] = x;
	}

	arr[p][0] = x;
	arr[p][1] = arr[(p * 2) + 1][0];
	arr[p][2] = arr[(p * 2) + 2][0];

	adjust(p);

	return 1;
}

template<class T, class O>
inline void Tree<T, O>::adjust_rem(){
	int p = 0, aux=0;

	while (1) {
		if (o(arr[(p * 2) + 1][0], arr[(p * 2) + 2][0])) { // COMPARA LOS DOS HIJOS PARA HALLAR EL MAYOR
			if (o(arr[p][0], arr[(p * 2) + 2][0])) { //COMPARA SI EL HIJO MAYOR ES MAYOR AL PADRE // CASO DERECHO
				aux = arr[p][0];
				arr[p][0] = arr[(p * 2) + 2][0];
				arr[(p * 2) + 2][0] = aux;
				arr[p][2] = aux;

				if (p % 2 == 0) {   // SI ES PAR ES HIJO DERECHO
					arr[(p - 2) / 2][2] = arr[p][0];
				}
				else { // SINO ES HIJO IZQUIERDO
					arr[(p - 1) / 2][1] = arr[p][0];
				}

				p = (p * 2) + 2;
			}
			else {
				break;
			}
		}
		else {
			if (o(arr[p][0], arr[(p * 2) + 1][0])) {//COMPARA SI EL HIJO MAYOR ES MAYOR AL PADRE // CASO IZQUIERDO
				aux = arr[p][0];
				arr[p][0] = arr[(p * 2) + 1][0];
				arr[(p * 2) + 1][0] = aux;
				arr[p][1] = aux;

				if (p % 2 == 0) {   // SI ES PAR ES HIJO DERECHO
					arr[(p - 2) / 2][2] = arr[p][0];
				}
				else { // SINO ES HIJO IZQUIERDO
					arr[(p - 1) / 2][1] = arr[p][0];
				}

				p = (p * 2) + 1;
			}
			else {
				break;
			}
		}
	}

}

template<class T, class o>
inline bool Tree<T, o>::remove() {
	int p = 0, aux = 0, f = 0;

	while (aux != -1) {// RECORRER EL ARRAY HASTA LA POSICION DEL ULTIMO ELEMENTO
		aux = arr[++f][0];
	}
	f--;
	
	arr[p][0] = arr[f][0];   // SWAP CON EL ULTIMO ELEMENTO
	arr[f][0] = -1;

	if (f % 2 == 0) {   // ACTUALIZAR EL PADRE DEL ULTIMO ELEMENTO
		arr[(f - 2) / 2][2] = -1;
	}
	else {
		arr[(f - 1) / 2][1] = -1;
	}

	adjust_rem();

	return 1;
}

template<class T, class o>
inline void Tree<T, o>::inorden(int p) {
	if (arr[p][0] == -1) { return; }
	inorden((p * 2) + 1);
	cout << arr[p][0] <<" ";
	inorden((p * 2) + 2);
}

template<class T, class O>
inline void Tree<T, O>::preorden(int p){
	if (arr[p][0] == -1) { return; }
	cout << arr[p][0] << " ";
	preorden((p * 2) + 1);
	preorden((p * 2) + 2);
}

template<class T, class O>
inline void Tree<T, O>::postorden(int p){
	if (arr[p][0] == -1) { return; }
	postorden((p * 2) + 1);
	postorden((p * 2) + 2);
	cout << arr[p][0] << "  ";
}

template<class T, class O>
inline void Tree<T, O>::print_mat(){
	for (int i = 0; i <20 ; i++) { 
		cout << "Arr[" << i << "]: ";
		cout<<arr[i][0]<<" ";
		cout<<arr[i][1]<< " ";
		cout<<arr[i][2]<<endl; 
	}
}

template<class T, class O>
inline void Tree<T, O>::print() {
	int p = 0;
	bool vacio = 0;

	vector <int> c;
	c.push_back(arr[0][0]);
	int len;
	int esp = 30;
	while (c.size() != 0 && vacio==0) {
		len = c.size();
		for (int i = 0; i < len; i++){
			if (c[i]){
				for (int i = 0; i < esp; i++) {
					cout << " ";
				}
				cout << c[i] << " ";
				if (c[i] == -1) {
					vacio = 1;
				}
				c.push_back(arr[(p * 2) + 1][0]);
				c.push_back(arr[(p * 2) + 2][0]);
				p++;
			}
			else {
				for (int i = 0; i < esp; i++) {
					cout << " ";
				}
				cout << " - ";
			}
		}
		cout << endl;
		esp /= 2;
		c.erase(c.begin(), c.begin() + len);
	}

}
