//Created by Clayton Paplaczyk

#pragma once
#include "Date_Time.h"
#include "HubNode.h"
#include <string>
using std::string;

class FlightNode
{
public:
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
//	} *headl = NULL;

	FlightNode(void);
	~FlightNode(void);
};

