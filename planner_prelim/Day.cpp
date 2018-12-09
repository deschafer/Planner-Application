// Day.cpp : implementation file
//

#include "stdafx.h"
#include "planner_prelim.h"
#include "Day.h"


// CDay

CDay::CDay(const int DayNumber, const int DayOfWeek, CPoint TopLeft, CPoint BottomRight, int Month, int Year)
{
	CString Str;

	this->m_DayNumber = DayNumber;
	m_DayOfWeek = DayOfWeek;
	m_Year = Year;
	m_Month = Month;

	for (int i = 0; i < 24; i++)
	{
		Str.Format(L"%d.%d.%d", DayNumber, DayOfWeek, i);

		EventListArray[i] = new CLLNode_Event();
		//EventListArray[i]->EnQueue(CPlannerEvent(Str, nullptr, i, i));
	}


}


CDay::~CDay()
{
}



// CDay member functions

void CDay::Initilize(int DayNumber)
{

	this->m_DayNumber = DayNumber;

}

CLLNode_Event* CDay::GetEventsForTime(int Time)
{

	return EventListArray[Time];

}


void CDay::AddEvent(CPlannerEvent Event)
{
	if (Event.GetStartTime() > 0 || Event.GetStartTime() < 23)
	{
		EventListArray[Event.GetStartTime()]->EnQueue(Event);
	}
	else
	{
		AfxMessageBox(_T("Unable to add event -- time not within bounds."));
	}


}

bool CDay::IsEvent()
{

	for (int i = 0; i < 24; i++)
	{

		if (EventListArray[i]->GetHead() != nullptr) return 1;

	}
	return 0;
}