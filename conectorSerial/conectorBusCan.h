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
	cm_SwitchRelay=82
};

class conectorBusCan {
protected:
	map<string,string> commandsID;
	map<string,string> commandsName;
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
	bool exec(string command,string node="",string args="");
};

#endif /* CONECTORBUSCAN_H_ */
