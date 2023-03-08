#pragma once
#include <vector>

using namespace std;

template <class G>
struct Nodo{
	typedef typename G::N N;
	typedef typename G::Edge Edge;
	N v;
	vector<Edge*> edges;

	Nodo(N _v) {
		v = _v;
	};
};

