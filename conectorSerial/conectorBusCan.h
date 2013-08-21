/*
 * conectorBusCan.h
 *
 *  Created on: Aug 20, 2013
 *      Author: borja
 */

#ifndef CONECTORBUSCAN_H_
#define CONECTORBUSCAN_H_

#include <map>
#include <iostream>
#include <string>
#include <list>
#include <set>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

#include "conectorSerial.h"
#define ENABLE_SERIAL_PORT_EVENT

enum codeNumberCommand{
	cm_TestLink = 0,
	cm_Reset =1,
	cm_GetFirmware=2,
	cm_CloseRelay=0x51,
	cm_SwitchRelay=0x52,
	cm_WrDisplay=0x0B,
	cm_WrInmDisplay=0x0C,
	cm_ClrDisplay=0x0A,
	cm_SaveAndRestoreDisplay=0x0D,
	cm_ActivateLed=0x5A,
	cm_SwitchLed=0x5B,
	cm_OutputPort=0x64,
	cm_EjectCard=0x59,
	cm_CaptureCard=0x60,
	cm_SetCFG=0x42,
	cm_GetCFG=0x43,
	cm_TxDigitalInput=0x53
};

class conectorBusCan {
protected: // atributos
	map<string,string> commandsID;
	map<string,string> commandsName;

	conectorSerial conector;
	bool listener;
	int temp;

private: // Ejecución de comandos.
	bool sendMessage(string msg);
	bool buildEmptyCmd(string cmd,string node);
	bool buildArgsCmd(string cmd,string node,string args,int minArgs,int maxArgs);

	void runListener();
	static void *Handle_Thread(void *hPort);
protected:
	string partialHex(int dec);
	string HexToStr(int dec);

	void setCommand();
	void setNameCommand();
	int getIDCommand(string id);
	
	
public:
	conectorBusCan();
	virtual ~conectorBusCan();
	string calculateCRC(string command);
	virtual bool exec(string command,string node="",string args="");
	void Open(string port="/dev/ttyUSB0");
	
	void launchListener();
	void Close();
		
};

#endif /* CONECTORBUSCAN_H_ */
