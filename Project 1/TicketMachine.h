#ifndef TICKETMACHINE_H_
#define TICKETMACHINE_H_

#include <iostream>
#include "Queue.h"
#include "Ticket.h"

using namespace std;

class TicketMachine
{
private:
	Queue <Ticket> box;
	char* event;

	void copyTicketMachine(TicketMachine const& other);
	void deleteTicketMachine();
public:
	TicketMachine(char* ev);
	TicketMachine(TicketMachine const& other);
	TicketMachine& operator=(TicketMachine const& other);
	~TicketMachine();

	void setEventName(char* name); 
	const char* getEventName() const; 

	void addTicket(const Ticket& ticket);
	void sellTicket();

	void print(); // used for testing
};



TicketMachine::TicketMachine(char* ev) :box()
{
	event = new char[strlen(ev) + 1];
	strcpy(event, ev);
}
// another way of interpreting the task is to have default ctor + setter
// but in our way we assure that the machine will have an event name


void TicketMachine::copyTicketMachine(TicketMachine const& other)
{
	box = other.box;

	event = new char[strlen(other.event) + 1];
	strcpy(event, other.event);
}

void TicketMachine::deleteTicketMachine()
{
	delete[]event;
}


TicketMachine::TicketMachine(TicketMachine const& other)
{
	copyTicketMachine(other);
}


TicketMachine& TicketMachine::operator=(TicketMachine const& other)
{
	if (this != &other)
	{
		deleteTicketMachine();
		copyTicketMachine(other);
	}

	return *this;
}

TicketMachine::~TicketMachine()
{
	deleteTicketMachine();
}

void TicketMachine::setEventName(char* name)
{
	event = new char[strlen(name) + 1];
	strcpy(event, name);
}

const char* TicketMachine::getEventName() const
{
	return event;
}

void TicketMachine::addTicket(const Ticket& ticket)
{
	if (strcmp(ticket.getOwnerName(), "Aleks") == 0)
		cerr << "Cannot accept ticket with the name Aleks." << endl;

	if (strcmp(ticket.getEventName(), event) != 0)
		cerr << "The machine doesn't accept tickets for that event." << endl;

	if (strcmp(ticket.getEventName(), event) == 0 && strcmp(ticket.getOwnerName(), "Aleks") != 0)
	{
		box.push(ticket);
	}
}

void TicketMachine::sellTicket()
{
	if (box.empty())
		cerr << "There are no tickets to sell." << endl;
	else
		box.pop();
}

void  TicketMachine::print()
{
	if (box.empty())
		cerr << "The ticket machine is empty." << endl;
	
	while (!box.empty())
	{
		Ticket temp = box.pop();
		temp.printTicket();
	}
}
#endif