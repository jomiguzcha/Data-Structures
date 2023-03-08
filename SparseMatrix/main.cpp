#include <iostream>
#include "Sparse_Matrix.h"

using namespace std;

int main() {
	Sparse_Matrix<int, 0> SM(6, 6);
	int a, b,c;
	a = b = c = 0;

	/*int arr[] = {8,14,7,2,7,0};
	int pos[][2] = { {2,1},{3,5},{1,3},{4,1},{0,3},{2,1} };

	for (int i = 0; i < 6; i++) {
		SM(pos[i][0], pos[i][1]) = arr[i];
	}*/

	SM(2, 1) = 8;
	SM(3, 5) = 14;
	SM(1, 3) = 7;
	SM(4, 1) = 2;
	SM(0, 3) = 7;
	SM(2, 1) = 0;
	a = SM(1, 2);
	b = SM(0,3);

	SM.print();
	cout << endl << endl << endl << endl;
	SM.print_c();

	system("pause");
	return 0;
}