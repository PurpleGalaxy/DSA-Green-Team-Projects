#ifndef TICKET_H
#define TICKET_H
#include <iostream>

class Ticket
{
private:
	char* ownerName;
	char* eventName;

	void copyString(char*&, const char*); //Copies the content of one string to another manually
	void eraseString(char*& name); //Delete string
public:
	//BIG 4
	Ticket();
	Ticket(Ticket const&);
	Ticket& operator=(Ticket const&);
	~Ticket();

	//accessors and mutators
	void setOwnerName(const char*);
	void setEventName(const char*);
	const char* getOwnerName() const;
	const char* getEventName() const;
	void printTicket() const; // used for testing
};

//Copy function
void Ticket::copyString(char*& dest, const char* name)
{
	dest = new char[strlen(name) + 1];
	int i;
	for (i = 0; i < strlen(name); i++)
		dest[i] = name[i];
	dest[i] = '\0';
}

//eraseName function
void Ticket::eraseString(char*& name)
{
	delete[] name;
}


//	BIG 4

//Default constructor
Ticket::Ticket()
{
	ownerName = nullptr;
	eventName = nullptr;
}

//Copy constructor
Ticket::Ticket(Ticket const& other)
{
	copyString(ownerName, other.ownerName);
	copyString(eventName, other.eventName);
}

//Operator =
Ticket& Ticket::operator=(Ticket const& other)
{
	if (this != &other)
	{
		eraseString(ownerName);
		eraseString(eventName);
		copyString(ownerName, other.ownerName);
		copyString(eventName, other.eventName);
	}
	return *this;
}

//Destructor
Ticket::~Ticket()
{
	eraseString(ownerName);
	eraseString(eventName);
}

//Mutators
void Ticket::setOwnerName(const char* name)
{
	eraseString(ownerName);
	copyString(ownerName, name);
}
void Ticket::setEventName(const char* name)
{
	eraseString(eventName);
	copyString(eventName, name);
}

//Accessors
const char* Ticket::getOwnerName() const
{
	return ownerName;
}
const char* Ticket::getEventName() const
{
	return eventName;
}


void Ticket::printTicket() const
{
	cout << "Event: " << getEventName() << endl;
	cout << "Owner: " << getOwnerName() << endl;
}
#endif 
