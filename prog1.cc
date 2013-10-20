#include <iostream>
#include "matrix.h"

#define LARGE 10000

using namespace std;

int main(int argc, char const *argv[])
{
	/* code */
	Matrix *A = new Matrix(LARGE, LARGE);
	Matrix *B = new Matrix(LARGE, LARGE);

	A->Randomize();
	B->Randomize();
	
	Matrix *C = A->Multiply(B);

	delete A;
	delete B;
	delete C;

	return 0;
}