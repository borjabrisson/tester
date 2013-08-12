/*
 * hijo.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: borja
 */

#include "hijo.h"

hijo::hijo() {
	// TODO Auto-generated constructor stub

}

hijo::~hijo() {
	// TODO Auto-generated destructor stub
}

void* hijo::print(void *id){
	long sock = (long)id;
    int n;
    char buffer[256];

    bzero(buffer,256);

    n = read(sock,buffer,255);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }
    printf("Here is the message(%d): %s\n",sock,buffer);
    n = write(sock,"I got your message",18);
    if (n < 0) 
    {
        perror("ERROR writing to socket");
        exit(1);
    }
    close(sock);
}

void hijo::run(int ID){
	int rc;
	pthread_t thread;
	//rc = pthread_create(&thread, NULL,print, (void *)ID);
	rc =  pthread_create(&thread, NULL, &hijo::print, (void *)ID);
  if (rc){
	 cout << "Error:unable to create thread," << rc << endl;
	 exit(-1);
  }
  //pthread_exit(NULL);
}
/*
void hijo::run(int ID)
{
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;
   for( i=0; i < NUM_THREADS; i++ ){
      cout << "Hijo() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL,
    		  &hijo::print, (void *)i);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   //pthread_exit(NULL);
}*/

