#pragma once
#include <vector>
#include "Edge.h"
#include "Nodo.h"

using namespace std;

template <class N,class E>
struct Graph{
	Graph() {}
	typedef Graph<N, E> G;
	typedef Nodo<G> Nodo;
	typedef Edge<G> Edge;
	typedef N N;
	typedef E E;

	vector<Nodo*> nodos;
	vector<Edge*> edges;

	bool insert_nodo(N n);
	bool insert_edge(E e,N a,N b,bool d);
	bool remove_node(N n);
	bool remove_edge(E e,N a, N b);
	void imprimir_nodos();
	void imprimir_aristas();
	int min_siguiente(vector<int>, vector<bool>);
	int existe_arista(int, int);
	int peso_arista(int, int);
	vector<char> dijkstra(N,N);
};

template<class N, class E>
inline bool Graph<N, E>::insert_nodo(N n){
	Nodo* ptr = new Nodo(n);
	nodos.push_back(ptr);//Actualiza el vector de nodos
	return 1;
}

template<class N, class E>
inline bool Graph<N, E>::insert_edge(E e, N a, N b, bool d){
	Nodo*_a = NULL; Nodo*_b = NULL;
	for (int i = 0; i < nodos.size(); i++) {// Encuentra los nodos y los guarda
		if ((nodos[i])->v == a) {
			_a = nodos[i];
		}
		else if ((nodos[i])->v == b) {
			_b = nodos[i];
		}
	}

	Edge* ptr = new Edge(e, _a, _b, d);
	_a->edges.push_back(ptr);//Actualiza los nodos y el vector de aristas
	_b->edges.push_back(ptr);
	edges.push_back(ptr);
	return 1;
}

template<class N, class E>
inline bool Graph<N, E>::remove_node(N n){
	Nodo* ptr;
	for (int i = 0; i < nodos.size(); i++) {
		if ((nodos[i])->v == n) {// Encuentra el nodo y lo guarda
			ptr = nodos[i];
			for (int i = 0; i < ptr->edges.size(); i++) {//Elimina todas las aristas de su lista
				remove_edge((ptr->edges[i])->peso, ((ptr->edges[i])->nodos[0])->v, ((ptr->edges[i])->nodos[1])->v);
			}
			nodos.erase(nodos.begin()+i);//Elimina el nodo del vector de nodos 
			delete ptr;
			return 1;
		}
	}

	return 0;
}

template<class N, class E>
inline bool Graph<N, E>::remove_edge(E e, N a, N b){
	Edge* ptr;
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i]->peso == e && (edges[i]->nodos[0])->v == a && (edges[i]->nodos[1])->v == b) {// Encuentra la arista y la guarda
			ptr = edges[i];
			
			for (int i = 0; i < (ptr->nodos[0])->edges.size(); i++) {//Elimina la arista en el vector de aristas del nodo a
				if ((ptr->nodos[0])->edges[i]->peso == e && ((ptr->nodos[0])->edges[i]->nodos[0])->v == a && ((ptr->nodos[0])->edges[i]->nodos[1])->v == b) {
					(ptr->nodos[0])->edges.erase((ptr->nodos[0])->edges.begin()+i);
					break;
				}
			}

			for (int i = 0; i < (ptr->nodos[1])->edges.size(); i++) {//Elimina la arista en el vector de aristas del nodo b
				if ((ptr->nodos[1])->edges[i]->peso == e && ((ptr->nodos[1])->edges[i]->nodos[0])->v == a && ((ptr->nodos[1])->edges[i]->nodos[1])->v == b) {
					(ptr->nodos[1])->edges.erase((ptr->nodos[1])->edges.begin()+i);
					break;
				}
			}

			edges.erase(edges.begin()+i);//Elimina la arista del vector de aristas 
			delete ptr;
			return 1;
		}
	}
	return 0;
}

template<class N, class E>
inline void Graph<N, E>::imprimir_nodos(){
	for (int i = 0; i < nodos.size(); i++) {
		cout << nodos[i]->v << " : " << i << endl;
	}
}

template<class N, class E>
inline void Graph<N, E>::imprimir_aristas(){
	for (int i = 0; i < edges.size(); i++) {
		cout << (edges[i]->nodos[0])->v << " --> " << (edges[i]->nodos[1])->v << " ; " << edges[i]->peso << endl;
	}
}

template<class N, class E>
inline int Graph<N, E>::min_siguiente(vector<int> d, vector<bool> m){
	int min = 1000, i = 0;
	for (int j = 0; j < nodos.size(); j++) {
		if (m[j] == 0 && d[j] <= min && d[j] != -1) {
			min = d[j];
			i = j;
		}
	}
	
	return i;
}

template<class N, class E>
inline int Graph<N, E>::existe_arista(int a, int b){
	Nodo* ptr = nodos[a];
	Nodo* ptr2 = nodos[b];
	int aux = 0;

	for (int i = 0; i < edges.size(); i++) {
		if (edges[i]->nodos[0] == ptr && edges[i]->nodos[1] == ptr2) {
			aux = i;
			return aux;
		}
	}

	return 0;
}

template<class N, class E>
inline int Graph<N, E>::peso_arista(int a, int b){
	int aux = existe_arista(a, b);
	int i = edges[aux]->peso;
	return i;
}

template<class N, class E>
inline vector<char> Graph<N, E>::dijkstra(N a, N b){
	int init = 0, fin = 0;
	vector<char> camino;
	vector<int> distancia(nodos.size());
	vector<char>anterior(nodos.size());
	vector<bool>marcado(nodos.size());

	for (int i = 0; i < nodos.size(); i++) {
		if ((nodos[i])->v == a) {
			init = i;
		}
		else if ((nodos[i])->v == b) {
			fin = i;
		}
		distancia[i] = -1;
		anterior[i] = ' ';
		marcado[i] = 0;
	}

	distancia[init] = 0; anterior[init] = '-';

	for (int i = 0; i < nodos.size() - 1; i++) {
		int u = min_siguiente(distancia, marcado);
		marcado[u] = 1;
		for (int j = 0; j < nodos.size(); j++) {
			if (existe_arista(u, j)!=0 && !marcado[j] && distancia[j] > distancia[u] + peso_arista(u, j)) {
				distancia[j] = distancia[u] + peso_arista(u, j);
				anterior[j] = nodos[u]->v;
			}
		}
	}
	
	camino.insert(camino.begin(), nodos[fin]->v);
	char p = anterior[fin];
	while (p!=anterior[init]) {
		camino.insert(camino.begin(), p);
		for (int i = 0; i < nodos.size(); i++) {
			if (nodos[i]->v == p) {
				fin = i;
				p = anterior[fin];
				break;
			}
		}
	}

	return camino;
}
