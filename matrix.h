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
	int rows, columns;
	int** element;
	
	Strategy* strategy;

public:
	Matrix(int rows, int columns);
	~Matrix();
	inline int GetRows() const {return rows;}
	inline int GetColumns() const {return columns;}

	void Randomize();

	inline void SetNumber(int i, int j, int num) { element[i][j] = num; }
	inline int GetNumber(int i, int j) const { return element[i][j]; }
	Matrix* Multiply(const Matrix* B) const;

	void SetMultiplyStrategy(Strategy* specificStrategy) { strategy = specificStrategy; }

	int operator () (int i, int j) { return element[i][j]; }

	//Matrix* MultiplyWithStrategy();
};

class Strategy
{
public:
	Strategy() {}
	virtual ~Strategy() {}

	virtual Matrix* Multiply(const Matrix* A, const Matrix* B) const = 0;
};

class SingleThreadStrategy : public Strategy
{
public:
	SingleThreadStrategy() {}
	~SingleThreadStrategy() {}

	virtual Matrix* Multiply(const Matrix* A, const Matrix* B) const;
};

}

#endif