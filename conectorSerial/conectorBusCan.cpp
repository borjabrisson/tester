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

bool conectorBusCan::exec(string command, string node, string args) {
	string id = commandsName[command];

	cout << "ID: "<< id<< " -- " << getIDCommand(id)<< endl;
	switch (getIDCommand(id)){
	case cm_TestLink:
		cout << "TestLink"<< endl;
		break;
	case cm_Reset:
		cout << "Reset"<< endl;
		break;
	case cm_SwitchRelay:
		cout << "nose"<< endl;
		break;
	}
	return false;
}

