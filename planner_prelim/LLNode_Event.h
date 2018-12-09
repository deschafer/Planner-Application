#pragma once
//#include "LLNode.h"
#include "PlannerEvent.h"

class CLLNode_Event //:public CLLNode
{
private:
	struct Node { //Simple Linked List struct

		CPlannerEvent Object;
		Node *next;
	};
	Node* p_Head;

public:

	Node* GetHead() { return p_Head; }	// Returns the head pointer
	void EnQueue(CPlannerEvent PlannerObject);		// Adds a new node to the end of the list

	Node* p_EventAux;

	CLLNode_Event() {}
	~CLLNode_Event() {}
};

