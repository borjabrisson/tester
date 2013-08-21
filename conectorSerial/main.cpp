//============================================================================
// Name        : conectorSerial.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "conectorSerial.h"
#include "conectorBusCan.h"

#include <iostream>

#include <map>
#include <iostream>
#include <string>
#include <list>
#include <set>
using namespace std;
#define ENABLE_SERIAL_PORT_EVENT
/*
int main() {
	conectorSerial conector;

	conector.Open_Port("/dev/ttyUSB0");///dev/ttyS0"); 
	//conector.Open_Port("/dev/ttyS0");
    
   	conector.Configure_Port(B9600,"8N1");   // Configuro el puerto serie
	
	conector.Write_Port((string)"\x02"+"00000020"+"\x03");            // Escribo en el puerto serie.
    
	conector.Create_Thread_Port();            // Creo un hilo y le paso el manejador.
	conector.Write_Port((string)"\x02"+"02010023"+"\x03");
	conector.Write_Port((string)"\x02"+"02000022"+"\x03");

	printf("\nPresione ENTER para terminar\n");
	getchar();

    
  //  Set_Configure_Port(fd,OldConf);     // Restituyo la antigua configuración del puerto.

	conector.Close_Port();          // Cierro el puerto serie.
    
	printf("\nPresione ENTER para terminar\n");
	getchar();
	return 0;
}*/


int main() {
	conectorBusCan conector;
	string cmd, node,args;
	conector.Open();
// 	conector.Open("/dev/ttyS0");
    conector.launchListener();
	
	while(true){
		cout << "comando: ";	cin >> cmd;
		if (cmd == "exit") break;
		cout << "Nodo: ";		cin >> node;
		cout << "ARGS: ";		cin >> args;
		conector.exec(cmd,node,args);
	}
  //  Set_Configure_Port(fd,OldConf);     // Restituyo la antigua configuración del puerto.

	conector.Close();          // Cierro el puerto serie.
    
	printf("\nHasta la proxima\n");
	getchar();
	return 0;
}