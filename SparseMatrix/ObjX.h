#pragma once
#include "Sparse_Matrix.h"
#include <iostream>

using namespace std;

template<class E>
struct ObjX{
	ObjX(int _a,int _b, E* _m) {
		a = _a;
		b = _b;
		m = _m;
	};

	typedef typename E::type T;

	ObjX operator =(T x) {
		m->set(a, b, x);
		return *this;
	}

	operator T() {
		return m->get(a,b);
	}

	E* m;
	int a, b;

};

