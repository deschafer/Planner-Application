
// planner.h : interface of the CPlannerView class
//

#pragma once
#include "plannerDoc.h"
#include "Month.h"
#include "Year.h"
#include "PlannerObject.h"
#include "ViewBase.h"
#include "DialogAddEvent.h"



class CPlannerView : public CView
{
protected: // create from serialization only
	CPlannerView();
	DECLARE_DYNCREATE(CPlannerView)

	// Attributes
public:
	CPlannerDoc* GetDocument() const;

	// Operations

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CPlannerView();
	int ReturnRows() { return m_Rows; }						// Returns the number of rows
	int ReturnColumns() { return m_Columns; }				// Returns number of columns
	int ReturnWidthPortion() { return m_WidthPortion; }		// Returns the width of each cell
	int ReturnHeightPortion() { return m_HeightPortion; }	// Returns the height of each cell
	int ReturnTopSize() { return m_TopBarSize; }			// Returns the size of the top portion of the client area
	int SendData(CPlannerEvent* Event);
	int SetDayObject(CDay* Day);							// Sets the day object for this planner
	void WindowDestroyed();
	void UpdateView() { m_CurrentView->ResetSelectedObject(); }
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_Width;			// To store the total width of this client area
	int m_Height;			// To store the total height of this client area
	int m_HeightPortion;	// To store the section size for each row
	int m_WidthPortion;		// To Store the section size for each column
	int m_TopBarSize;		// The size of the top bar in this view
	int m_WeeklyHeightPortion;	// The size for each row in the weekly view
	unsigned m_Rows;		// Stores the count of the number of rows
	unsigned m_Columns;		// Stores the count of the number of columns

	int m_DialogCount;
	int m_DialogMax;
	CDialogEx* m_OpenDialog;



	CPlannerObject m_Planner;

	CViewBase* m_CurrentView;
	CViewMonthly m_MonthlyView;
	CViewWeekly m_WeeklyView;
	CViewDaily m_DailyView;

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNextMonth();
	afx_msg void OnPrevMonth();
	afx_msg void OnYearPlus();
	afx_msg void OnYearMinus();
	afx_msg void OnViewMonthly();
	afx_msg void OnViewWeekly();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewDaily();
};

#ifndef _DEBUG  // debug version in plannerView.cpp
inline CPlannerDoc* CPlannerView::GetDocument() const
   { return reinterpret_cast<CPlannerDoc*>(m_pDocument); }
#endif

