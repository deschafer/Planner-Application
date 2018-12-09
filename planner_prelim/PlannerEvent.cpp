#include "stdafx.h"
#include "PlannerEvent.h"


CPlannerEvent::CPlannerEvent(CString Description, CString* Place, int StartDate, int EndDate) : m_TaskCompleted(0)
{

	m_Description = Description;
	m_Place = Place;
	m_StartDate = StartDate;
	m_EndDate = EndDate;


}

CPlannerEvent::CPlannerEvent(CString Description, CString* Place, int StartDate, int EndDate, int StartDateMinutes, int EndDateMinutes) : m_TaskCompleted(0)
{

	m_Description = Description;
	m_Place = Place;
	m_StartDate = StartDate;
	m_EndDate = EndDate;
	m_StartDateMinutes = StartDateMinutes;
	m_EndDateMinutes = EndDateMinutes;

}

CString CPlannerEvent::GetTimeStandardForm()
{
	CString NewString;
	int NewDate = 0;
	bool IfPm = 0;
	
	if (m_StartDate > 12) IfPm = 1;

	if (IfPm)
	{
		NewDate = m_StartDate - 12;

		if (m_StartDateMinutes < 10)
			NewString.Format(L"%d:0%dp.m.", NewDate, m_StartDateMinutes);
		else
			NewString.Format(L"%d:%dp.m.", NewDate, m_StartDateMinutes);
	}
	else
	{
		NewDate = m_StartDate;

		if(m_StartDate == 0 && m_StartDateMinutes < 10)
			NewString.Format(L"12:0%da.m.", m_StartDateMinutes);
		else if(m_StartDate == 0)
			NewString.Format(L"12:%da.m.", m_StartDateMinutes);
		else if (m_StartDateMinutes < 10)
			NewString.Format(L"%d:0%da.m.", NewDate, m_StartDateMinutes);
		else
			NewString.Format(L"%d:%da.m.", NewDate, m_StartDateMinutes);
	}
	


	return NewString;
}