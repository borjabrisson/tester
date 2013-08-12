//============================================================================
// Name        : hilos.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "hijo.h"

using namespace std;

#define NUM_THREADS     5


int main ()
{

   pthread_t threads[NUM_THREADS];
   int rc;
   int i;
   hijo *obj;
   for( i=0; i < NUM_THREADS; i++ ){
      cout << "main() : creating thread, " << i << endl;
      obj = new hijo();
      obj->run(i);
   }
   pthread_exit(NULL);
}
