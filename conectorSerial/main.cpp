//============================================================================
// Name        : conectorSerial.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "conectorSerial.h"
#include <map>
#include <iostream>
#include <string>
#include <list>
#include <set>
using namespace std;
#define ENABLE_SERIAL_PORT_EVENT

int main() {
	conectorSerial conector;

	conector.Open_Port("/dev/ttyUSB0");///dev/ttyS0"); 
	//conector.Open_Port("/dev/ttyS0");
    
   	conector.Configure_Port(B9600,"8N1");   // Configuro el puerto serie.
    
    
	conector.Write_Port((string)"\x02"+"00000020"+"\x03");            // Escribo en el puerto serie.
    
	conector.Create_Thread_Port();            // Creo un hilo y le paso el manejador.
	conector.Write_Port((string)"\x02"+"02010023"+"\x03");
	conector.Write_Port((string)"\x02"+"02000022"+"\x03");

	/*string data;
	conector.Read_Port(data,10);
	cout << "valor obtenido " <<data << endl;
	conector.Read_Port(data,3);
	cout << "valor obtenido " <<data << endl;*/

printf("\nPresione ENTER para terminar\n");
	getchar();
/*conector.Write_Port("HOLA");
printf("\nPresione ENTER para terminar\n");
getchar();
conector.Write_Port("6\n");
getchar();*/
    
  //  Set_Configure_Port(fd,OldConf);     // Restituyo la antigua configuración 
                                        // del puerto.

	conector.Close_Port();          // Cierro el puerto serie.
    
    	printf("\nPresione ENTER para terminar\n");
	getchar();
	return 0;
}
