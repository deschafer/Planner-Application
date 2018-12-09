#include "stdafx.h"
#include "planner.h"
#include "resource.h"

void CPlannerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_CurrentView->Update();

}


void CPlannerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* temp = nullptr;
	CString String;
	LoadLibrary(_T("riched32.dll"));
	CRect *ORect = nullptr;

	// Construct the dialog box passing the 
	// ID of the dialog template resource
	if (m_DialogCount < m_DialogMax)
	{
		// Create new dialog object
		CDialogAddEvent * aDlg = new CDialogAddEvent();

		if (m_CurrentView->SetObject(point, aDlg->m_Day))
		{
			aDlg->m_TempEventName.Format(L"Add Event: %d/%d/%d", aDlg->m_Day.GetMonth() + 1, aDlg->m_Day.GetNumber(), aDlg->m_Day.GetYear());

			ORect = m_CurrentView->GetSelectedRect();

			// Creating the dialog object
			aDlg->Create(IDD_ADD_EVENT, this);
			m_DialogCount++;		// Incrementing the open dialog count
			m_OpenDialog = aDlg;	// Setting the open dialog pointer

			// Now calculating the position of the dialog.
			// First, getting the Rect object of the dialog
			CRect Rect;
			aDlg->GetWindowRect(&Rect);
			Rect.NormalizeRect();

			// Next saving the dimensions of this object
			int dx = Rect.Width();
			int dy = Rect.Height();

			// Then moving the object to the location of the cursor
			Rect.OffsetRect(point.x, point.y);

			// Getting client area dimensions
			CRect Client;
			GetClientRect(&Client);
			CRect rect;

			// Places the rectangle so that is always visible
			if (point.x + dx > Client.Width()) Rect.OffsetRect(-dx,0);
			if (point.y + dy > Client.Height()) Rect.OffsetRect(0, -dy);

			// Set the pointer to this view
			aDlg->View = this;

			// Lastly doing any subview-specefic operations before displaying the dialog
			m_CurrentView->SetDialogData(aDlg);

			// Move window to new location and display the window, updating the location of the change.
			aDlg->MoveWindow(Rect);
			aDlg->ShowWindow(SW_SHOW);
			InvalidateRect(nullptr);
		}

	}
	else
	{
		if (m_CurrentView->GetSelectedObject() != nullptr)
			ORect = m_CurrentView->GetSelectedRect();

		m_OpenDialog->DestroyWindow();
		InvalidateRect(nullptr);
	
	}

	
	
}




void CPlannerView::OnNextMonth()
{
	int error = 0;

	error = m_CurrentView->OnNextMonth();

	if (!error) InvalidateRect(nullptr);
}


void CPlannerView::OnPrevMonth()
{
	int error = 0;

	error = m_CurrentView->OnPrevMonth();

	if (!error) InvalidateRect(nullptr);
}


void CPlannerView::OnYearPlus()
{
	int error = 0;

	error = m_CurrentView->OnNextYear();

	if (error) InvalidateRect(nullptr);
}


void CPlannerView::OnYearMinus()
{
	int error = 0;

	error = m_CurrentView->OnPrevYear();

	if (error) InvalidateRect(nullptr);
}


void CPlannerView::OnViewMonthly()
{
	if (m_CurrentView == &m_MonthlyView) return;
	else
	{
		m_CurrentView = &m_MonthlyView;
		m_CurrentView->Reset();
		InvalidateRect(nullptr);
	}
}


void CPlannerView::OnViewWeekly()
{
	if (m_CurrentView == &m_WeeklyView) return;
	else
	{
		m_CurrentView = &m_WeeklyView;
		m_CurrentView->Reset();
		InvalidateRect(nullptr);
	}
}

void CPlannerView::OnViewDaily()
{
	if (m_CurrentView == &m_DailyView) return;
	else
	{
		m_CurrentView = &m_DailyView;
		m_CurrentView->Reset();
		InvalidateRect(nullptr);
	}
}



BOOL CPlannerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0)
	{
		m_CurrentView->SetScroll();
		m_CurrentView->MoveRow(1);

	}
	else
	{
		m_CurrentView->SetScroll();
		m_CurrentView->MoveRow(-1);

	}

	
	InvalidateRect(nullptr);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

int CPlannerView::SendData(CPlannerEvent* Event)
{

	//AfxMessageBox(*Event->GetDescription());
	return 0;
}

BOOL CPlannerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}


