//Created by Clayton Paplaczyk

#include "StdAfx.h"
#include "FlightNode.h"
#include <string>
#include "Date_Time.h"
#include "HubNode.h"
using std::string;

FlightNode::FlightNode(void)
{
		string flightNumber;
		double price;
		string flightCompany;
		Date_Time departure;
		int duration;
		HubNode* source; 
		HubNode* destination;
//		string source;
//		string destination;
		FlightNode *next;
}

FlightNode::~FlightNode(void)
{
}
