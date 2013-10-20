#include <iostream>
#include <pthread.h>
#include "matrix.h"
#include "prog2.h"

const int  MAX_THREAD = 25;
const int LARGE = 10000;

using namespace std;

static const Matrix* A = NULL;
static const Matrix* B = NULL;
static Matrix* C = NULL;
// row_ready is the first row of matrix C 
// that are neither computed nor in-processing
static int row_ready = 0;
static pthread_mutex_t row_ready_mutex;

static void* compute_row_thread(void* row_num);


// class MultiThreadStrategy declared in prog2.h

MultiThreadStrategy::MultiThreadStrategy(int num_thread) {
	if(num_thread < 1)
		exit(-1);

	this->NUM_THREAD = num_thread;
	this->thread_id = new pthread_t[NUM_THREAD];	
}

MultiThreadStrategy::~MultiThreadStrategy() {
	
}

Matrix* MultiThreadStrategy::Multiply(const Matrix* mat_A, const Matrix* mat_B) {
	if(mat_A->GetColumns() != mat_B->GetRows())
		return NULL;

	pthread_mutex_lock(&compute_mutex);
	A = mat_A;
	B = mat_B;
	C = new Matrix(A->GetRows(), B->GetColumns());

	for (int i = 0; i < NUM_THREAD; ++i)
	{
		int err = pthread_create(&thread_id[i], NULL, compute_row_thread, &thread_id[i]);
		if(err != 0)
			exit(err);
	}

	row_ready = 0;
	pthread_mutex_unlock(&compute_mutex);
	
	for (int i = 0; i < NUM_THREAD; ++i)
	{
		pthread_join(thread_id[i], NULL);
	}

	return C;
}

// Each threads takes the responsibility to compute one row of C
static void* compute_row_thread(void* thread_num) {
	int thread = *((int *)thread_num);
	DEBUG("This is ");
	DEBUG(thread);
	DEBUG(" thread\n");

	for(int row = 0;;) {
		pthread_mutex_lock(&row_ready_mutex);
		row = row_ready;
		row_ready++;
		pthread_mutex_unlock(&row_ready_mutex);
		if(row >= C->GetRows())
			break;

		for (int j = 0; j < C->GetColumns(); ++j) {
			int num = 0;
			for (int k = 0; k < A->GetRows(); ++k) {
				num += A->GetNumber(row, k) * B->GetNumber(k, j);
			}
			C->SetNumber(row, j, num);
			usleep(10);
		}
		DEBUG("Row ");
		DEBUG(row);
		DEBUG(" computed\n");
	}

	return (void*)0;
}

int main(int argc, char const *argv[])
{
	// To avoid hard code on the implementation of the Matrix
	// I use Strategy Pattern to design the Matrix class
	// and its implementation of multiplication operation

	Matrix *A = new Matrix(LARGE, LARGE);
	Matrix *B = new Matrix(LARGE, LARGE);

	A->Randomize();
	B->Randomize();

	A->SetMultiplyStrategy(new MultiThreadStrategy(MAX_THREAD));

	DEBUG("MultiThreadStrategy set\n");
	
	Matrix* C = A->Multiply(B);

	return 0;
}