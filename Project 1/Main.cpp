#include <iostream>
#include "DynArray.h"
#include "Stack.h"
#include "Queue.h"
#include "Ticket.h"
#include "TicketMachine.h"

using namespace std;

void testDynArray()
{
	cout << "Testing Stack.h" << endl;
	cout << endl;

	cout << "Constructor, incrementSize, decrementSize, resize, getSize, getCapacity:" << endl;
	DynArray<unsigned> arr;
	cout << "Array1 size: " << arr.getSize() << endl;
	cout << "Array1 capacity: " << arr.getCapacity() << endl;
	cout << "Incrementing size:" << endl;
	arr.incrementSize();
	arr.incrementSize();
	arr.incrementSize();
	arr.incrementSize();
	arr.incrementSize();
	cout << "Array1 size: " << arr.getSize() << endl;
	cout << "Array1 capacity: " << arr.getCapacity() << endl;
	cout << "Decrementing size:" << endl;
	arr.decrementSize();
	cout << "Array1 size: " << arr.getSize() << endl << endl;

	
	cout << "Testing Copy constructor:" << endl;
	DynArray<unsigned> arr2(arr);
	cout << "Array2 size: " << arr.getSize() << endl;
	cout << "Array2 capacity: " << arr.getCapacity() << endl << endl;

	cout << "Testing operator= and empty:" << endl;
	DynArray<unsigned> arr3;
	cout << "Array3:" << endl;
	cout << "Empty(1 for Yes, 0 for No): " << arr3.empty() << endl;
	cout << "arr3 = arr2 = arr"<< endl; 
	arr3 = arr2 = arr;
	cout << "Array3 size: " << arr.getSize() << endl;
	cout << "Array3 capacity: " << arr.getCapacity() << endl;
	cout << "Empty(1 for Yes, 0 for No): " << arr3.empty() << endl << endl;

	cout << "Testing operator[]:" << endl;
	DynArray<double> arr4;
	for (int i = 0; i < arr4.getCapacity(); i++)
	{
		arr4[i] = i * 2;
		arr4.incrementSize();
		cout << "Array4 size: " << arr4.getSize() << ", element " << i << " = " << arr4[i] << endl;
	}
}

void testStack()
{
	cout << "Testing Stack.h" << endl;
	cout << endl;

	Stack<int> s1;

	cout << "Checking whether the stack is initially empty:" << endl;
	cout << "Stack: "; s1.print();
	cout << "empty? ";	(s1.empty() ? (cout << "yes") : (cout << "no")) << endl;
	cout << "size " << s1.size() << endl;
	cout << "top " << s1.top() << endl;
	cout << endl;

	cout << "Checking how removal of an item of an empty stack is accomplished:" << endl;
	cout << "pop " << s1.pop() << endl;
	cout << endl;

	cout << "Inserting some elements in the stack:" << endl;
	s1.push(23);	cout << "Stack: "; s1.print();
	s1.push(100); 	cout << "Stack: "; s1.print();
	s1.push(19); 	cout << "Stack: "; s1.print();
	s1.push(7); 	cout << "Stack: "; s1.print();
	s1.push(33487); 	cout << "Stack: "; s1.print();
	s1.push(4783);		cout << "Stack: "; s1.print();
	cout << "empty? ";	(s1.empty() ? (cout << "yes") : (cout << "no")) << endl;
	cout << "size " << s1.size() << endl;
	cout << "top " << s1.top() << endl;
	cout << endl;

	cout << "Checking whether a stack can be properly assigned " << endl
		<< "to another one using a copy constructor:" << endl;
	Stack<int> s2 = s1;
	cout << "top of Stack1: " << s1.top() << endl;
	cout << "top of Stack2: " << s2.top() << endl;
	cout << endl;

	cout << "Checking whether the top element is correctly removed " << endl
		<< "by comparing the top elements of the two stacks:" << endl;
	s2.pop();
	cout << "top of Stack1: " << s1.top() << endl;
	cout << "top of Stack2: " << s2.top() << endl;
	cout << endl;

	cout << "Another test for assignment, this time using the = operator. (Stack3 = Stack2)" << endl;
	Stack<int> s3;
	s3 = s2;
	cout << "top of Stack3: " << s3.top() << endl;
	cout << endl;

	cout << "Checking whether two elements from the stack properly swap their values:" << endl;
	cout << "Stack1: "; s1.print();
	cout << "Swaping first element with the top." << endl;
	s1.swap(0, 5);
	cout << "Stack1: "; s1.print();
	cout << endl;

	cout << "Checking if 2 stacks exchange their values correctly:" << endl << endl;

	cout << "First case: when the calling stack is empty:" << endl;
	Stack <int> s4;
	cout << "s3: "; 	s3.print(); 	
	cout << "s4: ";		s4.print(); 
	cout << "Now swapping the elements between s4 and s3." << endl;
	s4.swapStack(s3);
	cout << "s3: ";		s3.print();	
	cout << "s4: "; 	s4.print();		cout << endl;


	cout << "Second case: when the stack which is the argument is empty:" << endl;
	cout << "Now swapping again the elements between s4 and s3." << endl;
	s4.swapStack(s3);
	cout << "s3: ";		s3.print();	
	cout << "s4: ";		s4.print();		cout << endl;

	cout << "Third case: when both stacks have elements but different number:" << endl;
	cout << "s1: "; 	s1.print();	
	cout << "s2: "; 	s2.print(); 
	cout << "Now swapping the elements between s1 and s2." << endl;
	s1.swapStack(s2);
	cout << "s1: ";		s1.print();	
	cout << "s2: ";		s2.print();		cout << endl;
	cout << endl << endl;
}


void testQueue()
{
	cout << "Testing Queue.h:" << endl;
	cout << endl;

	cout << "test constructor" << endl;
	Queue<double> q1;
	Queue<int> q2;
	cout << "Queue1 (double): "; q1.print();
	cout << "Queue2 (int): "; q2.print();
	cout << endl;

	cout << "Inserting some elements in both queues:" << endl;
	q1.push(4);	cout << "Queue1: "; q1.print();
	q1.push(210); cout << "Queue1: "; q1.print();
	q1.push(519.5); cout << "Queue1: "; q1.print();
	q1.push(7.0009); cout << "Queue1: "; q1.print();
	cout << endl;

	q2.push(12);	cout << "Queue2: "; q2.print();
	q2.push(95); cout << "Queue2: "; q2.print();
	q2.push(3897); cout << "Queue2: "; q2.print();
	q2.push(621); cout << "Queue2: "; q2.print();
	q2.push(2); cout << "Queue2: "; q2.print();
	q2.push(911); cout << "Queue2: "; q2.print();
	cout << endl;


	cout << "Front and back functions" << endl;
	cout << "Queue1's head: " << q1.front() << endl;
	cout << "Queue1's tail: " << q1.back() << endl;
	cout << "Queue2's head: " << q2.front() << endl;
	cout << "Queue2's tail: " << q2.back() << endl;
	cout << endl;

	Queue<unsigned> q3;
	cout << "Queue3: ";
	cout << "Queue3's tail: " << q3.back() << endl;

	//Empty, push, pop, size
	cout << "Empty, push, pop, size:" << endl;
	cout << "Queue3's size: " << q3.size() << endl;
	cout << "Empty(1 for Yes, 0 for No)? " << q3.empty() << endl;
	q3.push(5);
	cout << "\npush: " << q3.back() << endl;
	cout << "Queue3's size: " << q3.size() << endl;
	cout << "Empty(1 for Yes, 0 for No)? " << q3.empty() << endl;
	cout << "\nPop: " << q3.pop() << endl;
	cout << "Queue3's size: " << q3.size() << endl;
	cout << "Empty(1 for Yes, 0 for No)? " << q3.empty() << endl;
	cout << "Pop: "; q3.pop();
	cout << endl;

	cout << "Swap" << endl;
	q3.push(5);
	q3.push(4);
	q3.print();
	q3.swap(0, 1);
	q3.print();
	cout << "Pop: " << q3.pop() << endl;
	q3.swap(0, 1);
	q3.print();
	cout << endl;

	cout << "Testing swapQueue: " << endl << endl;
	Queue<unsigned> q4;
	cout << "swapQueue test 1:" << endl;
	cout << "Queue3: "; q3.print();
	cout << "Queue4: "; q4.print(); 
	cout << "Swaping queues" << endl;
	q3.swapQueue(q4);
	cout << "Queue3: "; q3.print();
	cout << "Queue4: "; q4.print(); 
	cout << endl;

	cout << "swapQueue test 2:" << endl;
	q4.push(3);
	q4.push(4);
	q4.push(5);
	q3.push(4);
	q3.push(3);
	cout << "Queue3: ";		q3.print();
	cout << "Queue4: ";		q4.print();
	cout << "Swaping queues: " << endl;
	q3.swapQueue(q4);
	cout << "Queue1: ";		q3.print();
	cout << "Queue2: ";		q4.print();

	cout << endl << endl;
}

void testTicket()
{
	cout << "Testing Ticket.h:" << endl;
	cout << endl;

	cout << "Checking what values are in ownerName and eventName initially:" << endl;
	Ticket t1;
	if (t1.getOwnerName() == nullptr && t1.getEventName() == nullptr)
		cout << "The object is empty." << endl << endl;

	cout << "Setting ownerName and eventName and checking if the" << endl
		 << "the operation was successful by calling the get functions : " << endl;
	t1.setOwnerName("John Michael");
	t1.setEventName("Olympic Games 2017");
	cout << "t1 owner: " << t1.getOwnerName() << endl;
	cout << "t1 event: " << t1.getEventName() << endl << endl;

	cout << "Checking if the copy constructor is working as intended:" << endl;
	cout << "Ticket t2 = t1" << endl; Ticket t2 = t1;
	cout << "t2 owner: " << t2.getOwnerName() << endl;
	cout << "t2 event: " << t2.getEventName() << endl << endl;

	cout << "Testing setters by setting new data to t2:" << endl;
	t2.setOwnerName("Maria Fernandez");
	t2.setEventName("The Beatles World Tour");
	cout << "t1 owner: " << t1.getOwnerName() << endl;
	cout << "t1 event: " << t1.getEventName() << endl;
	cout << "t2 owner: " << t2.getOwnerName() << endl;
	cout << "t2 event: " << t2.getEventName() << endl << endl;

	cout << "Checking if operator= is working as intended:" << endl;
	cout << "Ticket t3;" << endl;
	cout << "t3 = t1;" << endl;	
	Ticket t3;
	t3 = t1;
	cout << "t3 owner: " << t3.getOwnerName() << endl;
	cout << "t3 event: " << t3.getEventName() << endl << endl;
}

void testTicketMachine()
{
	cout << "Testing TicketMachine.h:" << endl;
	cout << endl;
	
	cout << "Tesing the print function when there are no tickets in the machine:" << endl;
	TicketMachine tm("Football");
	tm.print();
	cout << endl;

	cout << "Testing if a ticket with correct ownerName and eventName is accepted by the machine:" << endl;
	Ticket t1;
	cout << "Setting ownet to Ivan and event to Football:" << endl;
	t1.setOwnerName("Ivan");
	t1.setEventName("Football");
	tm.addTicket(t1);
	tm.print();
	cout << endl;

	cout << "Testing if a ticket with incorrect ownerName and correct eventName" << endl
		 << "is accepted by the machine:" << endl;
	Ticket t2;
	cout << "Setting owner to Aleks and event to Football" << endl;
	t2.setOwnerName("Aleks");
	t2.setEventName("Football");
	tm.addTicket(t2);
	tm.print();
	cout << endl;

	cout << "Testing if a ticket with correct ownerName and incorrect eventName" << endl
		<< "is accepted by the machine:" << endl;
	Ticket t3;
	cout << "Setting owner to Pesho and event to Handball" << endl;
	t3.setOwnerName("Pesho");
	t3.setEventName("Handball");
	tm.addTicket(t3);
	tm.print();
	cout << endl;

	cout << "Testing if a ticket with incorrect ownerName and eventName" << endl
		 << "is accepted by the machine:" << endl;
	Ticket t4;
	cout << "Setting owner to Aleks and event to Handball" << endl;
	t4.setOwnerName("Aleks");
	t4.setEventName("Handball");
	tm.addTicket(t4);
	tm.print();
	cout << endl;

	cout << "Trying to sell a ticket when there are none in the machine:" << endl;
	tm.sellTicket();
	cout << endl;

	cout << "Trying to sell a ticket when there is a ticket in it:" << endl;
	Ticket t5;
	cout << "Setting the ticket data: owner to George and event to Volleyball." << endl;
	t5.setOwnerName("George");
	t5.setEventName("Volleyball");
	tm.addTicket(t5);
	tm.sellTicket();
	tm.addTicket(t1);
	tm.print();
	cout << endl;

}


int main()
{
	testDynArray();
	testStack();
	testQueue();
	testTicket();
	testTicketMachine();

	return 0;
}