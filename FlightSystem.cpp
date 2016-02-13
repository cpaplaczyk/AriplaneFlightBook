//Created by Clayton Paplaczyk

// Project Flight.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include "Date_Time.h"
#include "FlightNode.h"
#include "HubNode.h"
#include "TempFlight.h"
#include <stdio.h>
#include <string.h>
#include <fstream>	// used by ofstream
#include <sstream>	// used by istringstream
#include <iostream>
#include <iomanip>

using namespace std;

ostringstream os;

#pragma warning(disable: 4996)

// functions
void insertHub(string ntoken, string ltoken);
void debugger();
HubNode* get_sdhub(string fData);
void get_outgoing();
void lowest_Price();

void v_test();

HubNode *head = NULL;
FlightNode *headl = NULL;
void insertFlight(TempFlight *t);

//virtual float getBaggageFees(){
//	cout<<"Baggage Fees Virtual"
//}
//virtual int getDelay();

//float getBaggageFees() {
//	cout<<"Baggage Fees Normal"<<endl;
//}

//int getDelay;


int main(){	
	char data1[256];
	string data, name, location, str;  // string class is available in C++ 

	//reading the Hub.csv file
	fstream fileHandler;
	fileHandler.open("C:/Users/Keith/Downloads/Hub.csv", ios::in | ios::binary);

	if(fileHandler.is_open())
	{
		char *ntoken;
		char *ltoken;
		const char s[2] = ",";
		const char l[2] = "\r";
		
		getline(fileHandler, data); //throw away first line in file
		//parses the file for Hub.csv
		while(fileHandler.good()){
			getline(fileHandler, data);
			if (data.empty()) {break;}
			strcpy(data1, data.c_str());
			ntoken = strtok(data1, s);  // read first parameter
			ltoken = strtok(NULL, l);   // read second parameter on line
			insertHub(ntoken, ltoken);  // write it to the linked list	
		}
		fileHandler.close();
	}
	else
		cout << "ERROR: Could not open file for reading data!" << endl;

	// read the Flight.csv file
	// Column #1 - Flight Number
	// Column #2 - Ticket Price
	// Column #3 - Source Hub
	// Column #4 - Destination Hub
	// Column #5 - Departure Date/Time
	// Column #6 - Flight Duration
	// Column #7 - Airline Company

	fileHandler.open("C:/Users/Keith/Downloads/Flight.csv", ios::in | ios::binary);
	if(fileHandler.is_open())
	{
		TempFlight t;
		Date_Time departure;
		const char s[2] = ",";
		const char d[2] = "/";
		const char l[2] = "\r";
		string temp;
		char temp1[256];
		
		getline(fileHandler, data); //throw away first line in file
		//parses the file for Flight.csv 7 differnet things being taken out per line
		while(fileHandler.good()){
			getline(fileHandler, data); // get one line of data from the file
			if (data.empty()) break;
			strcpy(data1, data.c_str()); // copy data so we can parse through it
			t.flightNumber = strtok(data1, s); // 1 get Flight Number
			t.price = atof(strtok(NULL, s)); // 2 get Ticket Price, convert to double

			temp = (strtok(NULL, s)); // 3 get Source Hub 
			t.source = get_sdhub(temp); // get the HubNode City Location for Source

			temp = (strtok(NULL, s)); // 4 get Destination Hub 
			t.destination = get_sdhub(temp); // get the HubNode City Location for Destination

			// get Date and Time
			temp = (strtok(NULL, s)); // 5 get Departure Date/Time

			t.duration = atoi(strtok(NULL, s)); // 6 get Flight Duration convert to integer
			t.flightCompany = (strtok(NULL, l)); // 7 get flightCompany

			// Put Date and Time in the class
			strcpy(temp1, temp.c_str()); // copy data so we can parse through it
			t.departure.minutes = atoi(strtok(temp1, d)); 
			t.departure.hours = atoi(strtok(NULL, d));
			t.departure.day = atoi(strtok(NULL, d));
			t.departure.month = atoi(strtok(NULL, d));
			t.departure.year = atoi(strtok(NULL, d));

			insertFlight(&t); // write it to the linked list
		}//while
		fileHandler.close();
	}
	else
		cout << "ERROR: Could not open file for reading data!" << endl;

	debugger();
}  // main


//************************************************************************
//    Adds Hub.csv info to HubNode
	void insertHub(string ntoken, string ltoken){
		HubNode *newnode=new HubNode(); //creating newnode

		newnode->name = ntoken;
		newnode->location = ltoken;
		newnode->next=NULL; //assigning link of newnode to NULL
		if(head==NULL) {
			head=newnode;
		} //if
		else
		{
		HubNode *temp=head;
			while(temp->next!=NULL) {//traversing link to find end of the list
			temp=temp->next;
		}//while
		temp->next=newnode;//attaching new node to end of the list}
		}//else
}

//******************************************************************************
	//Adds Flight.csv info to FlightNode
	void insertFlight(TempFlight *t){
		class FlightNode *newnode=new FlightNode(); //creating newnode

		newnode->flightNumber = t->flightNumber;
		newnode->price = t->price;
		newnode->flightCompany = t->flightCompany;
		newnode->departure = t->departure;
		newnode->duration = t->duration;
		newnode->source = t->source;
		newnode->destination = t->destination;
		newnode->next=NULL; //assigning link of newnode to NULL

		if(headl==NULL) {
			headl=newnode;
		} //if
		else
		{
		FlightNode *temp=headl;
			while(temp->next!=NULL) {//traversing link to find end of the list
				temp=temp->next;
			}//while
		temp->next=newnode;//attaching new node to end of the list}
		}//else
	}//end of insertFlight()


//***********************************************************************
	// used to print out data from the linked lists to the console
	int print_all() {					
		class FlightNode *templ=headl; //print FlightNode info
		if (headl == NULL) {
			printf("No records found in FlightNode.\n");
	    }//if
		else {
			while (templ!= NULL) {
				cout<<templ->flightNumber<<endl;
				cout<<"$"<<setiosflags(ios::fixed)<<setprecision(2)<<templ->price<<endl;
				cout<<templ->source<<endl;
				cout<<templ->destination<<endl;
				cout<<templ->departure.month<<"/";
				cout<<templ->departure.day<<"/";
				cout<<templ->departure.year<<"  ";
				cout<<setfill('0') << setw(2)<<templ->departure.hours<<":";
				cout<<setfill('0') << setw(2)<<templ->departure.minutes<<endl;
				cout<<templ->duration<<endl;
				cout<<templ->flightCompany<<endl;
				cout<<endl<<endl;
				templ=templ->next;
			}//while
		}//else
		return 0; 
	}


//****************************************************************************
	// debugger to print out specfic items for Project Deliverables
	void debugger() {
		int opt;
		//menu
		while(1){
			cout<<endl;
			cout<<"1. Loop over each Hub and print Outgoing Flights"<<endl;
			cout<<"2. Flight Plan with the Lowest Price"<<endl;
			cout<<"3. Flight Plan with the Shortest Time"<<endl;
			cout<<"4. Working System"<<endl;
			cout<<"5. test Virtual Stuff"<<endl;
			cout<<"6. Exit"<<endl;
			cout<<"Enter option>>";	cin>>opt;

			switch(opt){
			case 1:
				get_outgoing();
				break;
			case 2:
				lowest_Price();
				break;
			case 3:
//				sort_duration();
				break;
			case 4:
//				display();
				break;
			case 5:
				v_test();
				break;
			case 6:
				exit(0);
				break;
			default:
			cout<<"wrong choice enter again"<<endl;
			}//switch
		}//while
//		return 0; //successfully terminated program
	}//debugger


//*************************************************************************************
// traverse through the HubNode list(which is a list of all the airports) and
// compare the passed string to an airport hub location(city)
// Put the HubNode.location into FlightNode.source and destination
// fData = Flight.csv file Source Airport name

HubNode* get_sdhub(string fData){
	class HubNode *h=head;
	char hub[256];    // HubNode parameter converted
	char flight[256]; // passed parameter converted

	strcpy(flight, fData.c_str()); // convert string to char
	if (head == NULL) {
	   printf("No records found in HubNode.\n");
	}//if
	 else {
		strcpy(hub, h->name.c_str()); // copy data so we can parse through it
		while (strcmp(flight, hub)!=0) { // loop through HubNode
			h=h->next;
			if(h->next==NULL) break;
			strcpy(hub, h->name.c_str()); // copy data so we can parse through it
		}//while
	 }//else
	 return h;
}

//*************************************************************************************
// traverse through the HubNode list(which is a list of all the airports) and
// for each location search through the FlightNode list and print out the outgoing 
// flights that match the HubNode name.

void get_outgoing(){
	class HubNode* h=head;
	class FlightNode *f=headl;
	char hub[256];    // HubNode location parameter converted
	char flight[256]; // parameter converted
	while (head != NULL) {
		f=headl; //reset FlightNode list to top
		strcpy(hub, h->name.c_str()); // get Hub location and convert it
		cout<<endl<<endl<<"---------------------------------------------------------------------------"<<endl;
		cout<<"Airport Outgoing Flights -  "<<h->name<<endl<<endl;
		cout<<"  Flight #                 Destination"<<endl<<endl;
		while (headl != NULL) { // loops through FlightHub list
			HubNode* sour = f->source;
			strcpy(flight, sour->name.c_str()); // get location from HubNode
			if (strcmp(hub, flight)==02) { 
				HubNode* dest = f->destination; 
				cout<<"  "<<f->flightNumber<<"       "<<dest->name;
				cout<<endl;
			}//if
			f=f->next;
			if(f->next==NULL) break;
		}//while headl
		h=h->next;
		if(h->next==NULL) break;
	}//while head
	
	return;
}
//  Lowest Price
// Search through FlightHub for:
//   1 - Flights that match the Departure City(source)
//   2 - Flights that match the Destination City(destination)
//   3 - Flights that are between 12/16/2013 - 12/18/2013 (Passed data)
// If any of these are direct flights, store them in an array
// if any of these are connecting flights store them in an array
// 
// Search through the stored direct flights adding baggage fees (Passed data)
// Pick the lowest price and store it
// Search through the connecting flights and see if
// the Phx to x = x to Los Angeles (Passed data) Destination = Source

// Split this into two functions:
// One function used to search for lowest price flights based upon passed data 
// Passed data - Date/Time, Number of bags

void lowest_Price() {

	int bags = 3; // THIS DATA NEEDS TO BE PASSED
	int bagFeeSW = 25;
	int bagFeeUS = 25;




	char depCity2[256] = "Phoenix";
	char desCity2[256]; 
	FlightNode* directF[10]; //used to store the direct flights
	FlightNode* srcMatch[10]; //used to store the Source Departure City that matched
	FlightNode* desMatch[10]; //used to store the Destination Destination City that matched
	class FlightNode* f=headl; 
	char srcCity[256]; // Source City from FlightNode
	char desCity[256]; // Destination City from FlightNode
	int a=0,b=0,c=0;
	cout<<"Enter Departure City>> Phoenix(fixed)"<<endl;
	cout<<"Enter Destination City>>"; cin>>desCity2;
	cout.width(50); cout<<left<<"Flights that match the Departure or Destination City"<<endl;
	cout.width(30); cout<<left<<"Flight Schedule"<<endl;
	cout<<"  Flight #    Company    Source Location       Departure Date/Time"<<endl;
	cout<<"                         Destination Location  Arrival Date/Time(Including Delays)"<<endl;
	cout<<"                         Price-Show Cancellation Details"<<endl;
	cout<<"Number of Bags"<<endl<<endl;
	cout<<"Running Grand Total"<<endl<<endl<<endl;

		f=headl; //reset FlightNode list to top
		Date_Time DT=f->departure; //function to get date/time

		// loops through FlightNode to find the possible flights
		while (headl != NULL) { // loops through FlightHub list
			HubNode* sour = f->source;
			HubNode* dest = f->destination;
			strcpy(srcCity, sour->location.c_str()); // get location from HubNode
			strcpy(desCity, dest->location.c_str()); // get source from HubNode

			// test for direct flights
			if ((strcmp(srcCity, depCity2)==0) && (strcmp(desCity, desCity2)==0)) {
				cout<<"Direct Flight  - "<<f->flightNumber<<endl<<endl;
				directF[a] = f;// store the pointer of the node
				a++;
			}
			else{			
				// Look for connecting flights
				// test for Departing cities being the same
				if (strcmp(srcCity, depCity2)==0) {  // if departing cities are the same
					DT=f->departure;
					cout.width(10); cout<<left<<f->flightNumber;
					cout.width(20); cout<<left<<f->flightCompany;
					cout.width(20); cout<<left<<sour->location;
					cout.width(20); cout<<left<<DT.display_DT();
					cout.width(30); cout<<left<<dest->location<<endl;
					cout<<endl;//
					srcMatch[b] = f;// store the pointer of the node
					b++;
				}//if
				else{
					if (strcmp(desCity, desCity2)==0) { // if destination cities are the same
						DT=f->departure;
						cout.width(10); cout<<left<<f->flightNumber;
						cout.width(20); cout<<left<<f->flightCompany;
						cout.width(20); cout<<left<<sour->location;
						cout.width(20); cout<<left<<DT.display_DT();
						cout.width(30); cout<<left<<dest->location<<endl;
						cout<<endl;
						cout<<endl;
						desMatch[c] = f;// store the pointer of the node
						c++;
					}//if
				}//else
			}//else
				f=f->next;// point to next node
				if(f->next==NULL) break;

		}//while headl


	return;
}
void v_test() {
	USAirway a;
	float test;
	USAirway* ptrA = &a;
	test = ptrA->getBaggageFees();

}