#pragma once



class CPlannerEvent
{
private:
	CString m_Description;	// Description of this event
	CString* m_Place;		// Place for this event
	int m_StartDate;		// Starting date for this event
	int m_StartDateMinutes;
	int m_EndDate;			// Ending date for this event
	int m_EndDateMinutes;
	bool m_TaskCompleted;	// Whether this task is completed


public:

	CString* GetDescription() { return &m_Description; }
	int GetStartTime() { return m_StartDate; }
	int GetStartTimeMinutes() { return m_StartDateMinutes; }
	CString* GetPlace() { return m_Place; }
	CString GetTimeStandardForm();

	CPlannerEvent(CString Description, CString* Place, int StartDate, int EndDate);
	CPlannerEvent(CString Description, CString* Place, int StartDate, int EndDate, int StartDateMinutes, int EndDateMinutes);

	CPlannerEvent() {};
	~CPlannerEvent() {};
};

