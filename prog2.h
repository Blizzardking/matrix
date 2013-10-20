#ifndef __PROG2_YU_H__
#define __PROG2_YU_H__

#include <pthread.h>
#include "matrix.h"
#include "common.h"

namespace std {

class MultiThreadStrategy : public Strategy
{
private:
	int NUM_THREAD;
	pthread_t* thread_id;

	// For thread safety
	// Only when the last computing process complet, 
	// the next calling thread, which has been scheduled 
	// for a new computing about matrix, 
	// will get the ownership of the compute object
	pthread_mutex_t compute_mutex;


public:
	MultiThreadStrategy(int num_thread);
	~MultiThreadStrategy();

	virtual Matrix* Multiply(const Matrix* A, const Matrix* B);
};

}

#endif