// PlannerViewMonthly.cpp : implementation file
//

#include "stdafx.h"
#include "planner_prelim.h"
/*


// CPlannerViewMonthly

IMPLEMENT_DYNCREATE(CPlannerViewMonthly, CView)

CPlannerViewMonthly::CPlannerViewMonthly()
{

}

CPlannerViewMonthly::~CPlannerViewMonthly()
{
}

BEGIN_MESSAGE_MAP(CPlannerViewMonthly, CView)
END_MESSAGE_MAP()


// CPlannerViewMonthly drawing

void CPlannerViewMonthly::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


void CPlannerView::DrawLayout(CDC* pDC)
{
	// Local Vars

	// Initialize variables if not already
	if (m_Width == 0 || m_Height == 0 || m_SizeChanged)
	{
		this->InitilizeWndVariables();
		m_CurrentMonth->ResetCells(m_WidthPortion, m_HeightPortion);
	}

	// Sets the default color for the background
	this->FillBackground(pDC);

	// Drawing the month section of the UI
	this->DrawMonthSection(pDC);

	// Drawing the top bar/ days of the week section of the UI
	this->DrawTopBarSection(pDC);

	// Draws the rows and columns for the main layout of the month view
	this->DrawGrid(pDC);

	// Draws the contents of each cell
	this->DrawCells(pDC);
}

// CPlannerViewMonthly diagnostics

#ifdef _DEBUG
void CPlannerViewMonthly::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlannerViewMonthly::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPlannerViewMonthly message handlers
*/