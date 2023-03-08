#pragma once
#include "Nodo.h"
#include "F_ordenes.h"
#include "Tree_iterator.h"
#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

template <class T,class O>
class Tree{
public:
	Tree() { root = 0; };
	~Tree() {};

	void Rep(Nodo<T>**& q, Nodo<T>** p);
	void RR(Nodo<T>**);
	void RL(Nodo<T>**);
	void LL(Nodo<T>**);
	void LR(Nodo<T>**);
	void actualizar_ins(Nodo<T>** p, T x, stack<pair<Nodo<T>*, bool>>& trayectoria);//ACTUALIZA LOS PESOS
	void actualizar_rem(Nodo<T>** p, T x, stack<pair<Nodo<T>*, bool>>& trayectoria);//ACTUALIZA LOS PESOS
	void equilibrar(Nodo<T>**, T);
	bool find(T x, Nodo<T>**& p, stack<pair<Nodo<T>*, bool>>& trayectoria);
	bool insert(T x);
	bool remove(T x);
	void mostrar(Nodo<T> *);
	void mostrar_endl();
	void inorden_x(Nodo<T> *);

	typedef Tree_iterator<T, Inorden<T>, stack<pair<Nodo<T> *, short>>> inorden_iterator;
	typedef Tree_iterator<T, Preorden<T>, stack<pair<Nodo<T> *, short>>> preorden_iterator;
	typedef Tree_iterator<T, Postorden<T>, stack<pair<Nodo<T> *, short>>> postorden_iterator;
	typedef Tree_iterator<T, Reverse<T>, stack<pair<Nodo<T> *, short>>> reverse_iterator;
	typedef Tree_iterator<T, Niveles<T>, queue<pair<Nodo<T> *, short>> > niv_iterator;

	inorden_iterator inorden_begin() {
		inorden_iterator i;
		i.pila_x.push(pair <Nodo<T> *, short>(root, 0));
		i++;
		return i;
	}

	inorden_iterator inorden_end() {
		return inorden_iterator();
	}

	preorden_iterator preorden_begin() {
		preorden_iterator i;
		i.pila_x.push(pair <Nodo<T> *, short>(root, 0));
		i++;
		return i;
	}

	preorden_iterator preorden_end() {
		return preorden_iterator();
	}

	postorden_iterator postorden_begin() {
		postorden_iterator i;
		i.pila_x.push(pair <Nodo<T> *, short>(root, 0));
		i++;
		return i;
	}

	postorden_iterator postorden_end() {
		return postorden_iterator();
	}

	reverse_iterator reverse_begin() {
		reverse_iterator i;
		i.pila_x.push(pair <Nodo<T> *, short>(root, 0));
		i++;
		return i;
	}

	reverse_iterator reverse_end() {
		return reverse_iterator();
	}

	niv_iterator niv_begin() {
		niv_iterator i;
		i.pila_x.push(pair <Nodo<T> *, short>(root, 0));
		return i;
	}

	niv_iterator niv_end() {
		return niv_iterator();
	}
	
	Nodo<T>* root;
	O o;
	stack<pair<Nodo<T> *, short>> p_x;
	queue<Nodo<T> *> cola;
};

template<class T, class O>
inline void Tree<T, O>::Rep(Nodo<T>**& q, Nodo<T>** p){
	q = &((*p)->nodos[(*p)->nodos[0] == 0]);
	while ((*q)->nodos[0] || (*q)->nodos[1]) {
		q = &((*q)->nodos[(*q)->nodos[1] != 0]);
	}
}

template<class T, class O>
inline void Tree<T, O>::RR(Nodo<T>** p){
	Nodo<T>* tmp = (*p)->nodos[1];
	Nodo<T>* aux = tmp->nodos[0];

	tmp->nodos[0]= *p;
	(*p)->nodos[1] = aux;
	aux = *p;
	*p = tmp;

	(aux)->peso -= 2;
	(tmp)->peso -= 1;
}

template<class T, class O>
inline void Tree<T, O>::RL(Nodo<T>** p){
	Nodo<T>* tmp = ((*p)->nodos[1])->nodos[0];
	Nodo<T>* aux1 = tmp->nodos[0];
	Nodo<T>* aux2 = tmp->nodos[1];
	
	tmp->nodos[0] = *p;
	tmp->nodos[1] = (*p)->nodos[1];
	(*p)->nodos[1] = aux1;
	(tmp->nodos[1])->nodos[0] = aux2;
	aux1 = tmp->nodos[1];
	aux2 = *p;
	*p = tmp;

	(aux2)->peso -= 2;
	(aux1)->peso += 1;
}

template<class T, class O>
inline void Tree<T, O>::LL(Nodo<T>** p){
	Nodo<T>* tmp = (*p)->nodos[0];
	Nodo<T>* aux = tmp->nodos[1];

	tmp->nodos[1] = *p;
	(*p)->nodos[0] = aux;
	aux = *p;
	*p = tmp;

	(aux)->peso += 2;
	(tmp)->peso += 1;
}

template<class T, class O>
inline void Tree<T, O>::LR(Nodo<T>** p){
	Nodo<T>* tmp = ((*p)->nodos[0])->nodos[1];
	Nodo<T>* aux1 = tmp->nodos[0];
	Nodo<T>* aux2 = tmp->nodos[1];

	tmp->nodos[1] = *p;
	tmp->nodos[0] = (*p)->nodos[0];
	(*p)->nodos[0] = aux2; 
	(tmp->nodos[0])->nodos[1] = aux1;
	aux1 = tmp->nodos[0];
	aux2 = *p;
	*p = tmp;

	(aux1) -= 1;
	(aux2) += 2;
}

template<class T, class O>
inline void Tree<T, O>::actualizar_ins(Nodo<T>** p, T x, stack<pair<Nodo<T> *, bool>>& trayectoria){ 
	Nodo<T>** s = &root;
	if (!trayectoria.empty()) {
		if (((trayectoria.top()).first)->nodos[!((trayectoria.top()).second)]) { // Hermano
			s = &((trayectoria.top()).first);
		}
		else {
			trayectoria.pop();
			if (!trayectoria.empty()) {
				Nodo<T>*aux = ((trayectoria.top()).first)->nodos[!((trayectoria.top()).second)]; //Tio
				if (aux!=NULL && ((aux)->nodos[0] != NULL || (aux)->nodos[1] != NULL)){
					s = &((trayectoria.top()).first);
				}
			}
		}
	}
		
	while (s != p){
		if (o((*s)->x, x)) {
			(*s)->peso += 1;
		}
		else {
			(*s)->peso += -1;
		}
		//cout <<"Peso "<<(*s)->x<<"  :" << (*s)->peso << endl;
		s = &((*s)->nodos[o((*s)->x, x)]);
	}
}

template<class T, class O>
inline void Tree<T, O>::actualizar_rem(Nodo<T>**p , T x, stack<pair<Nodo<T> *, bool>>& trayectoria){
	Nodo<T>** s = &root;

	if (!trayectoria.empty()) {
		if (((trayectoria.top()).first)->nodos[!((trayectoria.top()).second)]) { // Hermano
			s = &((trayectoria.top()).first);
		}
		else {
			trayectoria.pop();
			if (!trayectoria.empty()) {
				Nodo<T>*aux = ((trayectoria.top()).first)->nodos[!((trayectoria.top()).second)]; //Tio
				if (aux != NULL && ((aux)->nodos[0] != NULL || (aux)->nodos[1] != NULL)) {
					s = &((trayectoria.top()).first);
				}
			}
		}
	}
	
	while (s != p) {
		if (o((*s)->x, x)) {
			(*s)->peso += -1;
		}
		else {
			(*s)->peso += 1;
		}
		//cout <<"Peso "<<(*s)->x<<"  :" << (*s)->peso << endl;
		s = &((*s)->nodos[o((*s)->x, x)]);
	}
}

template<class T, class O>
inline void Tree<T, O>::equilibrar(Nodo<T>** p, T x){
	Nodo<T>** s = &root;
	while (s!=p) {
		//cout << "Peso " << (*s)->x << "  :" << (*s)->peso << endl;
		if ((*s)->peso == 2) {
			if (((*s)->nodos[o((*s)->x, x)])->peso == 1) {
				RR(s);
				break;
			}
			else{
				RL(s);
				break;
			}
		}
		else if ((*s)->peso == -2) {
			if (((*s)->nodos[o((*s)->x, x)])->peso == -1) {
				LL(s);
				break;
			}
			else{
				LR(s);
				break;
			}
		}
		s = &((*s)->nodos[o((*s)->x, x)]);
	}
}

template<class T, class O>
inline bool Tree<T, O>::find(T x, Nodo<T>**& p, stack<pair<Nodo<T> *, bool>>& trayectoria){
	p = &root;
	while (*p && ((*p)->x != x)) {
		trayectoria.push(make_pair(*p, o((*p)->x, x)));
		p = &((*p)->nodos[o((*p)->x,x)]);
	}
	return !!*p;
}

template<class T, class O>
inline bool Tree<T, O>::insert(T x) {
	Nodo<T>** p;
	stack<pair<Nodo<T> *, bool>> trayectoria;
	if (find(x, p, trayectoria)) { return 0; }
	*p = new Nodo<T>(x);

	actualizar_ins(p,x,trayectoria);
	equilibrar(p, x);
	return 1;
}

template<class T, class O>
inline bool Tree<T, O>::remove(T x){
	Nodo<T>** p;
	stack<pair<Nodo<T> *, bool>> trayectoria;
	if (!find(x, p,trayectoria)) { return 0; }
	if ((*p)->nodos[0] && (*p)->nodos[1]) {
		Nodo<T>** q;
		Rep(q, p);
		if (trayectoria.empty()) {
			Nodo<T>** s = &root;
			while (s != q) {
				trayectoria.push(make_pair(*s, o((*s)->x, x)));
				s = &((*s)->nodos[o((*s)->x, x)]);
			}
		}
		(*p)->x = (*q)->x;
		p = q;
	}
	
	Nodo<T>* t = *p;
	*p = (*p)->nodos[(*p)->nodos[0]==0];
	delete t;

	actualizar_rem(p, x,trayectoria);
	equilibrar(p,x);
	return 1;
}

template<class T, class O>
inline void Tree<T, O>::mostrar(Nodo<T> *y) {
	cola.push(y);
	while (!cola.empty()) {
		cout << (cola.front())->x << " ";
		if ((cola.front())->nodos[0] != 0) {
			cola.push((cola.front())->nodos[0]);
		}
		if ((cola.front())->nodos[1] != 0) {
			cola.push((cola.front())->nodos[1]);
		}
		cola.pop();
	}
}

template<class T, class O>
inline void Tree<T, O>::mostrar_endl() {
	vector <Nodo<T>* > c;
	c.push_back(root);
	int len;
	int esp = 20;
	while (c.size() != 0) {
		len = c.size();
		for (int i = 0; i < len; i++) {
			if (c[i]) {
				for (int i = 0; i < esp; i++) {
					cout << " ";
				}
				cout << c[i]->x << " ";
				c.push_back(c[i]->nodos[0]);
				c.push_back(c[i]->nodos[1]);
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

template<class T, class O>
inline void Tree<T, O>::inorden_x(Nodo<T> *y){
	p_x.push(pair <Nodo<T> *, short> (y, 0));
	
	while (!p_x.empty()) {
		if ((p_x.top()).second == 0) {
			(p_x.top()).second = 1;
			if (((p_x.top()).first)->nodos[0] != NULL) {
				p_x.push(pair <Nodo<T> *, short> (((p_x.top()).first)->nodos[0], 0));
			}
		}
		else if ((p_x.top()).second == 1) {
			cout << ((p_x.top()).first)->x << " ";
			(p_x.top()).second = 2;
		}
		else if ((p_x.top()).second == 2) {
			(p_x.top()).second = 3;
			if (((p_x.top()).first)->nodos[1] != NULL) {
				p_x.push(pair <Nodo<T> *, short>(((p_x.top()).first)->nodos[1], 0));
			}
		}
		else if ((p_x.top()).second == 3) {
			p_x.pop();
		}
	}
}
	