//Created by Clayton Paplaczyk

#pragma once
#include <string>
using std::string;

class HubNode
{
public:
		string name;
		string location;
		HubNode* ptrlocation;
		HubNode* next;
		//FlightNode* headFlights;
//	} *head = NULL;

//HubNode* get_ptr(void){
//	return location;
//}
	HubNode(void);
	~HubNode(void);
};

