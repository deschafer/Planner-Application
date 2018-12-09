#include "stdafx.h"
#include "LLNode_Event.h"

// Adds a new node to the end of the list
void CLLNode_Event::EnQueue(CPlannerEvent EventObject)
{

	// Local Vars
	Node* p_Aux;

	// Creating new node
	p_Aux = new Node;
	p_Aux->Object = EventObject;
	p_Aux->next = nullptr;

	if (p_Head == nullptr) { // If empty list

		p_Head = p_Aux;
		return;
	}
	// Otherwise, traverse and add to end of the list.
	Node *p_Traverse = p_Head;
	while (p_Traverse->next != nullptr)
		p_Traverse = p_Traverse->next;
	p_Traverse->next = p_Aux;

}

