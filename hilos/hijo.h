/*
 * hijo.h
 *
 *  Created on: Aug 12, 2013
 *      Author: borja
 */

#ifndef HIJO_H_
#define HIJO_H_

#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS     5

class hijo {
protected:
	static void* print(void *id);
public:
	hijo();
	virtual ~hijo();
	void run(int ID);
};

#endif /* HIJO_H_ */
