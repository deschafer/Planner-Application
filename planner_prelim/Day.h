#pragma once
#include "PlannerEvent.h"
#include "LLNode_Event.h"
//class CLLNode_Event;

// CDay command target

class CDay //: public CObject
{
public:
	virtual ~CDay(void);

	CDay(const int DayNumber, const int DayOfWeek, CPoint TopLeft, CPoint BottomRight, int Month, int Year);
	CDay(void) {};

	CPlannerEvent* GetPlannerEvent() { return &m_Event; }
	CLLNode_Event* GetPlannerEvent(int x) { return EventListArray[x]; }
	unsigned GetNumber() { return m_DayNumber; }
	unsigned GetDayOfWeek() { return m_DayOfWeek; }
	int GetYear() { return m_Year; }
	int GetMonth() { return m_Month; }
	void Initilize(int m_DayNumber);
	void AddEvent(CPlannerEvent Event);
	CLLNode_Event* GetEventsForTime(int Time);
	bool IsEvent();


	CRect m_Cell;			// Holds the dimensions of this object

protected:
	unsigned m_DayNumber;	// Part of this day object's date
	unsigned m_DayOfWeek;
	CPlannerEvent m_Event;
	CLLNode_Event* EventListArray[24];

	int m_Year;
	int m_Month;
	
};


