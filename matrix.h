#ifndef __MATRIX_YU_H__
#define __MATRIX_YU_H__

#define NUMBER_LIMIT 99999

#include "cstdlib"


namespace std
{

class Matrix;
class Strategy;
class SingleThreadStrategy;
	
class Matrix
{
private:
	int rows, columns; //number of row and column
	int** element;   // The elements of the matrix
	
	Strategy* strategy;

public:
	Matrix(int rows, int columns);
	~Matrix();
	inline int GetRows() const {return rows;}  // get number of rows
	inline int GetColumns() const {return columns;}

	void Randomize();

	inline void SetNumber(int i, int j, int num) { element[i][j] = num; }
	inline int GetNumber(int i, int j) const { return element[i][j]; }
	Matrix* Multiply(const Matrix* B) const;    // this matrix multiplied to B 

	void SetMultiplyStrategy(Strategy* specificStrategy) { strategy = specificStrategy; }
	// The defaultStrategy is single thread solution

};


// Strategy Design Pattern
// This class Strategy is an abstract class, which is intended to 
// provide some interfaces that will be implemented by its inherited class
class Strategy
{
public:
	Strategy() {}
	virtual ~Strategy() {}

	virtual Matrix* Multiply(const Matrix* A, const Matrix* B) = 0;
};

class SingleThreadStrategy : public Strategy
{
public:
	SingleThreadStrategy() {}
	~SingleThreadStrategy() {}

	virtual Matrix* Multiply(const Matrix* A, const Matrix* B);
};

}

#endif
