#pragma once

#include "PlannerObject.h"
#include "Year.h"
#include "Month.h"
#include "Row.h"

static class CDialogAddEvent;

// Base class for each of the views for this application
class CViewBase
{

protected:

	int * m_Width;			// To store the total width of this client area
	int * m_Height;			// To store the total height of this client area
	int m_HeightPortion;	// To store the section size for each row
	int m_WidthPortion;		// To Store the section size for each column
	int * m_TopBarSize;		// The size of the top bar in this view
	unsigned * m_Rows;		// Stores the count of the number of rows
	unsigned * m_Columns;		// Stores the count of the number of columns
	bool m_SizeChanged;		// Indicator variable for whether size has been changed of window
	bool m_DaysComplete;	// Indicates whether the m_DayStrings array has been initialized
	bool m_MonthsComplete;  // Indicated whether the m_MonthStrings array has been initialized
	bool m_Scroll;
	CMonth *m_CurrentMonth;	// The current month object
	CString m_DayStrings[7];	// Array that holds the CString types for each of the days of the week
	CString m_MonthStrings[12];	// Array that holds the CString types for each of the twelve months
	CYear *m_Year;			// The current year object
	CPlannerObject *m_Planner;	// Current planner object
	CPlannerView *m_CurrentView;// Current view Object

public:

	virtual void InitilizeWndVariables(CPlannerView* View);

	// Functions that are important to all the subclasses
	virtual void FillBackground(CDC* pDC, CPlannerView* View);
	void DrawMonthSection(CDC* pDC, CPlannerView* View);
	virtual void DrawTopBarSection(CDC* pDC, CPlannerView* View);
	virtual void DrawLayout(CDC* pDC, CPlannerView* View) {};
	virtual void Update() { m_SizeChanged = 1; }
	virtual bool SetObject(CPoint Point, CDay &DayObject) { return 0; }	// Finds the object associated with this point on the screen
	virtual bool ResetSelectedObject() { return 0; }
	virtual CDay* GetSelectedObject() { return nullptr; }
	virtual void Reset() { m_SizeChanged = 1; }
	virtual CRect* GetSelectedRect() { return nullptr; }
	virtual void SetDialogData(CDialogAddEvent *aDlg) {}
	virtual void SetScroll() { m_Scroll = true; }

	// Default versions for these functions
	virtual int OnNextMonth() { return 0; }
	virtual int OnPrevMonth() { return 0; }
	virtual int OnNextYear() { return 0; }
	virtual int OnPrevYear() { return 0; }
	virtual int MoveRow(int Movement) { return 0; }

	CViewBase() {};
	CViewBase::CViewBase(unsigned *Rows, unsigned *Columns, int *Height, 
		int *Width, int *TopBarSize, CPlannerObject* Object);
	~CViewBase() {};
};


// Class for a month object
class CViewMonthly : public CViewBase
{
private:
	void DrawGrid(CDC* pDC);
	void DrawCells(CDC* pDC);

	CDay* m_SelectedDay;	// The selected day object, used for highlighting
public:

	virtual void DrawLayout(CDC* pDC, CPlannerView* View) override;
	virtual int OnNextMonth() override;
	virtual int OnPrevMonth() override;
	virtual int OnNextYear() override;
	virtual int OnPrevYear() override;

	virtual int MoveRow(int Movement) override;

	virtual bool SetObject(CPoint Point, CDay& DayObject) override;
	virtual bool ResetSelectedObject() override;
	virtual CDay* GetSelectedObject() { return m_SelectedDay; }
	virtual CRect* GetSelectedRect() { return &m_SelectedDay->m_Cell; }

	CViewMonthly(unsigned *Rows, unsigned *Columns, int *Height,
		int *Width, int *TopBarPortion, CPlannerObject* Object);

	CViewMonthly() {};
	~CViewMonthly() {};
};

// Class for the weekly view
class CViewWeekly : public CViewBase
{
private:

	int m_WeekStartDay;				// The starting day of the week for the current month
	int m_WeeklyHeightPortion;		// The heightportion of the display region
	int m_RowCounter;				// Used to count current displayed rows for the psuedo-scrolling
	int m_DayCounter;				// A counter used for weekly arithmetic counting the offset of the first week
	CDay* m_SelectedDay;			// The selected day for highlighting
	int m_SelectedTime;				// The selected time for highlighting
	CRect* m_SelectedRect;			// The current selected rectangle for highlighting
	bool m_Initialized;				// If this object is intitialized
	CDay* m_Week[7];				// Current displayed day objects are temporarily stored here
	bool m_LastWeek;				// Last week of the current month
	bool m_FirstWeek;				// First week of the current month
	bool m_FirstMonthFirstWeek;		// Inciates that the current week on display is the very first week of this planner
	bool m_LastMonthLastWeek;		// Inciates that the current week on display is the very first week of this planner
	bool m_Reminder;				// Not used yet
	int m_Offset;					// The offest for the psudo-scrolling
	bool m_Change;					// If there was a change in the view
	void DrawWeeklyGrid(CDC* pDC);	// Draws the gird lines for this view
	void ResetWeek();				// Reset the m_week array
	void DrawReminder(CDC* pDC);	// Not used yet

public:

	virtual void DrawLayout(CDC* pDC, CPlannerView* View) override;	
	virtual void DrawTopBarSection(CDC* pDC, CPlannerView* View) override;
	virtual void FillBackground(CDC* pDC, CPlannerView* View) override;
	virtual void InitilizeWndVariables(CPlannerView* View) override;
	void DrawCells(CPlannerView* View, CDC* pDC);
	void DrawColumn(CPlannerView* View, CDC* pDC, int StartDay, int StartDate, CMonth* Month);
	virtual int OnNextMonth() override;
	virtual int OnPrevMonth() override;
	virtual int OnNextYear() override;
	virtual int OnPrevYear() override;
	int GetDate(int Day, int Month, int Year);
	virtual bool SetObject(CPoint Point, CDay& DayObject) override;
	virtual bool ResetSelectedObject() { m_SelectedDay = nullptr; m_SelectedRect = nullptr; return 1; }
	virtual CDay* GetSelectedObject() { return m_SelectedDay; }
	virtual CRect* GetSelectedRect() { return m_SelectedRect; }
	virtual void SetDialogData(CDialogAddEvent *aDlg) override;
	virtual int MoveRow(int Movement) override;
	CViewWeekly(unsigned *Rows, unsigned *Columns, int *Height,
		int *Width, int *TopBarPortion, CPlannerObject* Object);
	CViewWeekly() {};
	~CViewWeekly() {};
};

// Class object for the daily view
class CViewDaily : public CViewBase
{
private:

	// Implementation-specefic functions
	void DrawGrid(CDC* pDC, CPlannerView* View);
	void DrawLeftSection(CDC* pDC, CPlannerView* View, int HeightMin, int HeightMax, int WidthMin, int WidthMax);
	void DrawCenterSection(CDC* pDC, CPlannerView* View, int HeightMin, int HeightMax, int WidthMin, int WidthMax);
	void DrawRightSection(CDC* pDC, CPlannerView* View, int HeightMin, int HeightMax, int WidthMin, int WidthMax);
	void SetDay();

	int m_TimeArray[24];	// Array to hold the time strings
	int m_TimeOffset;		// Holds offset for time for psuedo-scrolling

	int m_PreviousMonth;	

	CDay* m_CurrDay;		// Pointer to the current displayed object

public:

	virtual void DrawLayout(CDC* pDC, CPlannerView* View) override;
	virtual void DrawTopBarSection(CDC* pDC, CPlannerView* View) override;
	virtual int OnNextMonth() override;
	virtual int OnPrevMonth() override;
	virtual int OnNextYear() override;
	virtual int OnPrevYear() override;

	CViewDaily(int *m_Width, int *m_Height, int * TopBarPortion, CPlannerObject* Object);

	CViewDaily() {};
	~CViewDaily() {};
};

