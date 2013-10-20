
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "matrix.h"
#include "common.h"


namespace std
{
	 
Strategy* const defaultStrategy = new SingleThreadStrategy();

Matrix::Matrix(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	element = new int*[rows];

	for (int i = 0; i < rows; ++i)
	{
		element[i] = new int[columns];
		memset(element[i], 0, columns);
	}

	strategy = defaultStrategy;
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; ++i)
	{
		delete [] element[i];
	}
	delete [] element;
}

void Matrix::Randomize() {
	srand(time(NULL));
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			element[i][j] = rand() % NUMBER_LIMIT;
		}
	}
}

Matrix* Matrix::Multiply(const Matrix* B) const {
	
	return strategy->Multiply(this, B);
}


Matrix* SingleThreadStrategy::Multiply(const Matrix* A, const Matrix* B) {
	
	if(A->GetColumns() != B->GetRows())
		return NULL;

	Matrix* C = new Matrix(A->GetRows(), B->GetColumns());
	
	for (int i = 0; i < C->GetRows(); ++i)
	{
		for (int j = 0; j < C->GetColumns(); ++j)
		{
			int num = 0;
			for (int k = 0; k < A->GetRows(); ++k)
			{
				num += A->GetNumber(i, k) * B->GetNumber(k, j);
			}
			C->SetNumber(i, j, num);
			usleep(10);
		}
		DEBUG("Row ");
		DEBUG(i);
		DEBUG(" computed\n");
	}


	return C;
}


//end std
}