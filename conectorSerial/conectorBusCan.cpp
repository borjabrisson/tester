/*
 * conectorBusCan.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: borja
 */

#include "conectorBusCan.h"

conectorBusCan::conectorBusCan() {
	// TODO Auto-generated constructor stub
	setCommand();
	setNameCommand();
}

string conectorBusCan::partialHex(int dec) {
	string numeroHex="";
		stringstream stream;
		if(dec<16) {
		   switch(dec) {
				   case 10:
				   numeroHex="A";
				   break;
				   case 11:
				   numeroHex="B";
				  break;
				  case 12:
				  numeroHex="C";
				  break;
				  case 13:
				  numeroHex="D";
				  break;
				  case 14:
				 numeroHex="E";
				  break;
				  case 15:
				  numeroHex="F";
				  break;
				  default:
					  stream << dec;
					  numeroHex = stream.str();
				  break;
		  }
		  return numeroHex;
		}
		return "error";
}

string conectorBusCan::HexToStr(int dec) {
	int cociente=16, residuo=0;
		string numeroHex="", numeroHex1="";

		while(dec>=16){
			cociente=dec/16;
			residuo=dec%16;
			dec=cociente;
			numeroHex1=partialHex(residuo);
			numeroHex=numeroHex1+numeroHex;
			dec=cociente;
		}
		numeroHex1=partialHex(dec);
		numeroHex=numeroHex1+numeroHex;
		if (numeroHex.length() == 1) numeroHex = "0"+numeroHex;
		return numeroHex;
}

conectorBusCan::~conectorBusCan() {
	// TODO Auto-generated destructor stub
}

void conectorBusCan::setCommand() {
	commandsID.insert(pair<string,string>("00","TestCtrLink"));
	commandsID.insert(pair<string,string>("01","Reset"));
	commandsID.insert(pair<string,string>("02","GetFirmware"));
	commandsID.insert(pair<string,string>("51","CloseRelay"));
	commandsID.insert(pair<string,string>("52","SwitchRelay"));
	commandsID.insert(pair<string,string>("42","SetCFG"));
}

void conectorBusCan::setNameCommand() {
	map<string,string>::iterator it;
	for(it = commandsID.begin(); it != commandsID.end();it++){
		commandsName[(*it).second] = (*it).first;
	}
	commandsName.insert(pair<string,string>("TestNodeLink","00"));
	commandsName.insert(pair<string,string>("SetupNCanMax","01"));
}

string conectorBusCan::calculateCRC(string command){
	int size = command.size(),amount=0;
	for(int i=0;i<size; i++){
		amount += (int)command[i];
	}
	amount = amount % 256;
	return this->HexToStr(amount);
}

int conectorBusCan::getIDCommand(string id) {
	if (id[0]> '9') id[0] -= 7;
	if (id[1]> '9') id[1] -= 7;
	return ((id[0]-48)*16) + (id[1]-48);
}



bool conectorBusCan::buildEmptyCmd(string cmd, string node) {
	string msg =node+cmd+"00";
		msg += this->calculateCRC(msg);
	return 	this->sendMessage(msg);
}

bool conectorBusCan::buildArgsCmd(string cmd, string node, string args,int minArgs, int maxArgs) {
	string msg =node+cmd;
	int size = args.size()/2;
		if ( (size >= minArgs) && (size <= maxArgs) ){
			msg += "0/";//+(string)(char)(48+size);
			msg += args + this->calculateCRC(msg+args);
	return		this->sendMessage(msg);
		}
		return false;
}

bool conectorBusCan::sendMessage(string msg) {
	string out = '\x02'+msg+'\x03';
	cout << "Enviamos al bus: "<< out << endl;
	return true;
}

bool conectorBusCan::exec(string command, string node, string args) {
	string id = commandsName[command];

	cout << "ID: "<< id<< " -- " << getIDCommand(id)<< endl;
	switch (getIDCommand(id)){
	case cm_TestLink:
		if(command == "TestCtrLink") node="00";
		this->buildEmptyCmd(id,node);
		break;
	case cm_Reset:
		this->cmReset(node);
		break;
	case cm_GetFirmware:
		this->cmGetFirmware(node);
		break;
	case cm_SwitchRelay:
		cout << "nose"<< endl;
		break;
	case cm_SetCFG:
		this->buildArgsCmd(id,node,args,6,6);
		break;
	}
	return false;
}
/*
void conectorBusCan::cmTestLink(string ID) {
	string msg =ID+"0000";
	msg += this->calculateCRC(msg);
	this->sendMessage(msg);
}

void conectorBusCan::cmReset(string ID) {
	string msg =ID+"0100";
	msg += this->calculateCRC(msg);
	this->sendMessage(msg);
}

void conectorBusCan::cmGetFirmware(string ID) {
	string msg =ID+"0200";
		msg += this->calculateCRC(msg);
		this->sendMessage(msg);
}

void conectorBusCan::cmCloseRelay(string ID, string args) {
	string msg =ID+"5102";
	if (args.size() == 4){
		msg += args + this->calculateCRC(msg+args);
		this->sendMessage(msg);
	}
}

void conectorBusCan::cmSwitchRelay(string ID, string args) {
	string msg =ID+"5202";
		if (args.size() == 4){
			msg += args + this->calculateCRC(msg+args);
			this->sendMessage(msg);
		}
}

void conectorBusCan::cmWrDisplay(string ID, string args) {
	string msg =ID+"0B";
	int size = args.size();
		if ( (size > 2) && (size < 13) ){
			msg += "0"+size;
			msg += args + this->calculateCRC(msg+args);
			this->sendMessage(msg);
		}
}

void conectorBusCan::cmWrInmDisplay(string ID, string args) {
	string msg =ID+"0C";
	int size = args.size();
		if ( (size > 2) && (size < 13) ){
			msg += "0"+size;
			msg += args + this->calculateCRC(msg+args);
			this->sendMessage(msg);
		}
}

void conectorBusCan::cmClrDisplay(string ID) {
	string msg =ID+"0A00";
		msg += this->calculateCRC(msg);
		this->sendMessage(msg);
}

void conectorBusCan::cmSaveAndRestoreDisplay(string ID, string args) {
}

void conectorBusCan::cmActiveLedBuzzer(string ID, string args) {
	string msg =ID+"5A02";
		if (args.size() == 4){
			msg += args + this->calculateCRC(msg+args);
			this->sendMessage(msg);
		}
}

void conectorBusCan::cmSwitchLed(string ID, string args) {
	string msg =ID+"5B02";
		if (args.size() == 4){
			msg += args + this->calculateCRC(msg+args);
			this->sendMessage(msg);
		}
}

void conectorBusCan::cmOutPort(string ID, string args) {
}

void conectorBusCan::cmEjectCard(string ID) {
}

void conectorBusCan::cmCaptureCard(string ID) {
}

void conectorBusCan::cmSetCFG(string ID, string args) {
	string msg =ID+"4206";
		if (args.size() == 12){
			msg += args + this->calculateCRC(msg+args);
			this->sendMessage(msg);
		}
}

void conectorBusCan::cmGetCFG(string ID) {
	string msg =ID+"4300";
		msg += this->calculateCRC(msg);
		this->sendMessage(msg);
}

void conectorBusCan::cmTxDigitalInput(string ID) {
}


*/


