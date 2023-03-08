#include <iostream>
#include "Graph.h"

using namespace std;

struct CCord {
	int x;
	int y;
};

int main() {
	vector<char> d;
	Graph<char,int> prueba;

	prueba.insert_nodo('A');
	prueba.insert_nodo('B');
	prueba.insert_nodo('C');
	prueba.insert_nodo('D');

	prueba.insert_edge(10, 'A', 'B', 0);
	prueba.insert_edge(5, 'C', 'B', 0);
	prueba.insert_edge(4, 'D', 'C', 0);
	prueba.insert_edge(7, 'B', 'D', 0);

	prueba.imprimir_nodos(); cout << endl;
	prueba.imprimir_aristas(); cout << endl;

	prueba.remove_node('A');
	prueba.remove_edge(7, 'B', 'D');

	prueba.imprimir_nodos(); cout << endl;
	prueba.imprimir_aristas(); cout << endl;

	d = prueba.dijkstra('D', 'B');
	for (int i = 0; i < d.size(); i++) {
		cout << d[i] << endl;
	}
	
	system("pause");
	return 0;
}