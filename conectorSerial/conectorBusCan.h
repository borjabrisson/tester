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

enum codeNumberCommand{
	cm_TestLink = 0,
	cm_Reset =1,
	cm_GetFirmware=2,
	cm_SwitchRelay=82,
	cm_SetCFG=0x42
};

class conectorBusCan {
protected: // atributos
	map<string,string> commandsID;
	map<string,string> commandsName;

private: // Ejecución de comandos.
	void cmTestLink(string ID="00");
	void cmReset(string ID);
	void cmGetFirmware(string ID);

	void cmCloseRelay(string ID,string args);
	void cmSwitchRelay(string ID,string args);

	void cmWrDisplay(string ID,string args);
	void cmWrInmDisplay(string ID,string args);
	void cmClrDisplay(string ID);

	void cmSaveAndRestoreDisplay(string ID,string args);
	void cmActiveLedBuzzer(string ID,string args);
	void cmSwitchLed(string ID,string args);

	void cmOutPort(string ID,string args);
	void cmEjectCard(string ID);
	void cmCaptureCard(string ID);
	void cmSetCFG(string ID,string args);
	void cmGetCFG(string ID);

	void cmTxDigitalInput(string ID);

	bool sendMessage(string msg);

	bool buildEmptyCmd(string cmd,string node);
	bool buildArgsCmd(string cmd,string node,string args,int minArgs,int maxArgs);

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
};

#endif /* CONECTORBUSCAN_H_ */
