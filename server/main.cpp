#include "serverIP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "listen/hijo.h"
#include "configuration/configuration.h"

#include <sys/types.h> 

int main( int argc, char *argv[] )
{
	serverIP server;
	cout << "antes del start"<< endl;
	server.start();
	cout << "tras el start"<< endl;
	string input;
	cin >> input;
	server.free();
	cin >> input;
	sleep(20);
}