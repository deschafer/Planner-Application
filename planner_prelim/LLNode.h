#pragma once

#include "Day.h"
//#include "Month.h"

// Forward declaration of CMonth class -- Required to resolve include errors
class CMonth;



class CLLNode
{
private:
	struct Node { //Simple Linked List struct

		CDay Object;
		Node *next;
	};
	Node* p_Head;
public:
	// Default CTOR and DTOR
	CLLNode() { p_Head = nullptr; };
	~CLLNode() {};

	void EnQueue(CDay DayObject);		// Adds a new node to the end of the list
	void ResetSizes(CMonth* Month);		// Edits the sizes of all the nodes in the linked list
	Node* GetHead() { return p_Head; }	// Returns the head pointer
	Node* ReturnAuxPointer() { return m_AuxPtr; }
	Node* m_AuxPtr;
	CDay* ReturnDayWithDate(int Date);


};



