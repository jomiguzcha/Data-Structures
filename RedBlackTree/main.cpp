#include <iostream> 
#include <vector>
#include <Windows.h>

using namespace std;

HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class nodo {
public:
	int valor;
	bool color;
	nodo* rama[2];
	nodo* padre;

	nodo(int valor) : valor(valor) {
		padre = rama[0] = rama[1] = NULL;
		color = 1;}

	nodo *tio() {
		if (padre == NULL or padre->padre == NULL){ return NULL;}
		if (padre->isOnLeft()){ return padre->padre->rama[1];}
		else{ return padre->padre->rama[0];}
	}

	bool isOnLeft() { return this == padre->rama[0]; }

	nodo *hermano() {
		if (padre == NULL){ return NULL;}
		if (isOnLeft()){ return padre->rama[1];}
		return padre->rama[0];
	}

	void moveDown(nodo *nParent) {
		if (padre != NULL) {
			if (isOnLeft()) { padre->rama[0] = nParent;}
			else { padre->rama[1] = nParent;}
		}
		nParent->padre = padre;
		padre = nParent;
	}

	bool hasRedChild() {
		return (rama[0] != NULL and rama[0]->color == 1) or
			(rama[1] != NULL and rama[1]->color == 1);
	}
};

class RBTree {
public:
	nodo *head;

	void leftRotate(nodo *x) {		
		nodo *nParent = x->rama[1];
		if (x == head){ head = nParent;}
		x->moveDown(nParent);
		x->rama[1] = nParent->rama[0];
		if (nParent->rama[0] != NULL){ nParent->rama[0]->padre = x;}
		nParent->rama[0] = x;
	}

	void rightRotate(nodo *x) {
		nodo *nParent = x->rama[0];
		if (x == head){ head = nParent;}
		x->moveDown(nParent);
		x->rama[0] = nParent->rama[1];
		if (nParent->rama[1] != NULL){ nParent->rama[1]->padre = x;}
		nParent->rama[1] = x;
	}

	void swapColors(nodo *x1, nodo *x2) {
		bool temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapValues(nodo *u, nodo *v) {
		int temp;
		temp = u->valor;
		u->valor = v->valor;
		v->valor = temp;
	}

	void fixRedRed(nodo *x) {
		if (x == head) {
			x->color = 0;
			return;
		}
		
		nodo* padre = x->padre;
		nodo* grandparent = padre->padre;
		nodo* tio = x->tio();

		if (padre->color != 0) {
			if (tio != NULL && tio->color == 1) {
				padre->color = 0;
				tio->color = 0;
				grandparent->color = 1;
				fixRedRed(grandparent);
			}
			else {
				if (padre->isOnLeft()) {
					if (x->isOnLeft()) { swapColors(padre, grandparent);}
					else {
						leftRotate(padre);
						swapColors(x, grandparent);}
					rightRotate(grandparent);
				}
				else {
					if (x->isOnLeft()) {
						rightRotate(padre);
						swapColors(x, grandparent);}
					else { swapColors(padre, grandparent);}
					leftRotate(grandparent);
				}
			}
		}
	}

	nodo *successor(nodo *x) {
		nodo *temp = x;
		while (temp->rama[0] != NULL){ temp = temp->rama[0];}
		return temp;
	}
	
	nodo *BSTreplace(nodo *x) {
		if ( x->rama[0] and x->rama[1] ){ return successor(x->rama[1]);}
		if ( !x->rama[0] and !x->rama[1] ){ return NULL;}
		if ( x->rama[0] ){ return x->rama[0];}
		else{ return x->rama[1];}
	}

	void deleteNode(nodo *v) {
		nodo *u = BSTreplace(v);
		bool uvBlack = ((u == NULL or u->color == 0) and (v->color == 0));
		nodo *padre = v->padre;

		if (u == NULL){
			// v es una hoja
			if (v == head) { head = NULL;}
			else {
				if (uvBlack) { fixDoubleBlack(v);} // u y v son negros
				else { // u o v son rojos
					if (v->hermano() != NULL){ v->hermano()->color = 1;}
				}
 
				if (v->isOnLeft()) { padre->rama[0] = NULL; }
				else { padre->rama[1] = NULL;}
			}
			delete v;
			return;
		}

		if (v->rama[0] == NULL or v->rama[1] == NULL) {
			// v tiene un hijo
			if (v == head) {
				v->valor = u->valor;
				v->rama[0] = v->rama[1] = NULL;
				delete u;
			}
			else {
				if (v->isOnLeft()) { padre->rama[0] = u;}
				else { padre->rama[1] = u;}
				delete v;
				
				u->padre = padre;
				if (uvBlack) { fixDoubleBlack(u);}
				else { u->color = 0;}
			}
			return;
		}

		// v tiene 2 hijos
		swapValues(u, v);
		deleteNode(u);
	}

	void fixDoubleBlack(nodo *x) {
		if (x == head){ return;}

		nodo *hermano = x->hermano(), *padre = x->padre;
		if (hermano == NULL){ fixDoubleBlack(padre);}
		else {
			if (hermano->color == 1) {
				padre->color = 1;
				hermano->color = 0;
				
				if (hermano->isOnLeft()) { rightRotate(padre);}
				else { leftRotate(padre);}
				fixDoubleBlack(x);
			}
			else {
				if (hermano->hasRedChild()) {
					// al menos 1 hijo rojo
					if (hermano->rama[0] != NULL and hermano->rama[0]->color == 1) {
						if (hermano->isOnLeft()) { // LL
							hermano->rama[0]->color = hermano->color;
							hermano->color = padre->color;
							rightRotate(padre);
						}
						else { // RL
							hermano->rama[0]->color = padre->color;
							rightRotate(hermano);
							leftRotate(padre);
						}
					}
					else {
						if (hermano->isOnLeft()) { // LR
							hermano->rama[1]->color = padre->color;
							leftRotate(hermano);
							rightRotate(padre);
						}
						else { // RR
							hermano->rama[1]->color = hermano->color;
							hermano->color = padre->color;
							leftRotate(padre);
						}
					}
					padre->color = 0;
				}
				else {
					// 2 hijos negros
					hermano->color = 1;
					if (padre->color == 0)
						fixDoubleBlack(padre);
					else
						padre->color = 0;
				}
			}
		}
	}

	RBTree() { head = NULL; }
	
	nodo* search(int n) {
		nodo* temp = head;
		while (temp != NULL) {
			if (n < temp->valor) {
				if (temp->rama[0] == NULL){ break;}
				else{ temp = temp->rama[0];}
			}
			
			else if (n == temp->valor) { break;}
			
			else {
				if (temp->rama[1] == NULL){ break;}
				else{ temp = temp->rama[1];}
			}
		}
		return temp;
	}

	void insert(int n){
		nodo *newNode = new nodo(n);
		if (head == NULL){
			newNode->color = 0;
			head = newNode;
		}
		else{
			nodo *temp = search(n);
			if (temp->valor == n){ return;}
			
			newNode->padre = temp;
			if (n < temp->valor){ temp->rama[0] = newNode;}
			else{ temp->rama[1] = newNode;}
			fixRedRed(newNode);
		}
	}

	void remove(int n) {
		if (head == NULL){ return;}
		nodo *v = search(n), *u;

		if (v->valor != n){ return;}
		deleteNode(v);
	}

	void eliminar_arbol(){
		nodo* a = head;
		while (head) {
			remove(a->valor);
			a = head;
		}
	}

	void mostrar(nodo* p, int level) {
		cout << "\n";
		if (!p) return;
		mostrar(p->rama[1], level + 1);
		for (int i = 0; i < level; i++)cout << "\t";
		cout << p->valor << "(";
		(p->color) ? cout << "R)\n" : cout << "N)\n";
		mostrar(p->rama[0], level + 1);
	}

	void mostrar_endl() {
		vector <nodo *> c;
		c.push_back(head);
		int len;
		int esp = 30;
		while (c.size() != 0) {
			len = c.size();
			for (int i = 0; i < len; i++) {
				if (c[i]) {
					for (int i = 0; i < esp; i++) {
						cout << " ";
					}
					if (c[i]->color == 1) {
						SetConsoleTextAttribute(hConsole, 4 | FOREGROUND_INTENSITY);
					}
					else {
						SetConsoleTextAttribute(hConsole, 64 | FOREGROUND_INTENSITY);
					}
					cout << c[i]->valor << " ";
					c.push_back(c[i]->rama[0]);
					c.push_back(c[i]->rama[1]);
				}
				else {
					for (int i = 0; i < esp; i++) {
						cout << " ";
					}
					SetConsoleTextAttribute(hConsole, 64 | FOREGROUND_INTENSITY);
					cout << " - ";
				}
			}
			cout << endl;
			esp /= 2;
			c.erase(c.begin(), c.begin() + len);
		}
	}
};

int main() {
	RBTree t;
	
	int arr[] = { 12,5,15,3,10,13,17,4,7,11,14,6,8 };

	for (int i = 0; i < 13; i++) {
		t.insert(arr[i]);
	}

	//t.mostrar(t.head, 0);
	t.mostrar_endl();
	cout << endl;
	
	int a; int num;
	cout << "Cantidad de numeros a eliminar:";
	cin >> num;

	for (int i = 0; i < num; i++) {
		cout << "Numero a eliminar : ";
		cin >> a;
		t.remove(a);
	}

	t.mostrar_endl();
	cout << endl;

	t.insert(9);
	t.insert(10);

	t.mostrar_endl();
	cout << endl;

	system("pause");
	return 0;
}