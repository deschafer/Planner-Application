#include "stdafx.h"
#include "ViewBase.h"


CViewMonthly::CViewMonthly(unsigned *Rows, unsigned *Columns, int *Height,
	int *Width, int* TopBarSize, CPlannerObject* Object)
	: CViewBase(Rows, Columns, Height, Width, TopBarSize, Object) 
{}


//
// DrawLayout()
// Draws the Month style layout for this view
//
void CViewMonthly::DrawLayout(CDC* pDC, CPlannerView* View)
{
	// Local Vars


	// Initialize variables if not already
	if (m_Width == 0 || m_Height == 0 || m_SizeChanged)
	{
		InitilizeWndVariables(View);
		m_CurrentMonth->ResetCells(m_WidthPortion, m_HeightPortion);
	}

	// Sets the default color for the background
	FillBackground(pDC, View);

	// Drawing the month section of the UI
	DrawMonthSection(pDC, View);

	// Drawing the top bar/ days of the week section of the UI
	DrawTopBarSection(pDC, View);

	// Draws the rows and columns for the main layout of the month view
	DrawGrid(pDC);

	// Draws the contents of each cell
	DrawCells(pDC);
}

void CViewMonthly::DrawGrid(CDC* pDC)
{

	// Draws rows based on amount of rows and current
	// dimensions of client area
	for (int height = m_HeightPortion + *m_TopBarSize; height < *m_Height - 10; height += m_HeightPortion)
	{
		pDC->MoveTo(0, height);
		pDC->LineTo(*m_Width, height);
	}
	// Draws columns based on amount of colomns and current
	// dimensions of client area
	for (int width = m_WidthPortion; width < *m_Width - 10; width += m_WidthPortion)
	{

		pDC->MoveTo(width, *m_TopBarSize);
		pDC->LineTo(width, *m_Height);

	}

}

void CViewMonthly::DrawCells(CDC* pDC)
{
	// Local Variables
	CLLNode* Curr;
	CRect EnclosingRect;
	CString string;
	CFont font;
	CBrush NewBrush;

	// Creating the font object
	VERIFY(font.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Calibri")));           // lpszFacename

								   // Traversing the head of the list of days within the month object
	Curr = m_CurrentMonth->GetList();
	Curr->m_AuxPtr = Curr->GetHead();

	// Getting each cell's dimensions
	EnclosingRect = Curr->m_AuxPtr->Object.m_Cell;

	// Printing each cell

	// First selecting new font
	CFont* def_font = pDC->SelectObject(&font);

	// Then creating new brush and selecting background mode for styling
	NewBrush.CreateSolidBrush(RGB(221, 221, 235));
	pDC->SetBkMode(TRANSPARENT);

	// Traversing the linked list structure of each month, 
	// and drawing the contents of each cell.
	for (int i = 0; i < m_CurrentMonth->m_NumberDays; i++)
	{
		// Sets CString object format
		string.Format(L"%u.", Curr->m_AuxPtr->Object.GetNumber());
		// Writes the number of this day to the corner of this cell

		// Deflate with respect to pen width
		EnclosingRect.DeflateRect(1, 1);

		// Fill in this rectangle with NewBrush's color
		if (&Curr->m_AuxPtr->Object == m_SelectedDay)pDC->FillRect(EnclosingRect, new CBrush(RGB(150, 150, 160)));
		else pDC->FillRect(EnclosingRect, &NewBrush);

		// If this month is today
		if (m_Planner->IsToday(&Curr->m_AuxPtr->Object))
		{
			CRect *NewEnclosingRect = new CRect(EnclosingRect.TopLeft(), CPoint(EnclosingRect.BottomRight().x + 1, EnclosingRect.TopLeft().y + 5));

			pDC->FillRect(NewEnclosingRect, new CBrush(RGB(82, 95, 120)));

		}

		// Reset the rectangles size
		EnclosingRect.InflateRect(1, 1);
		// Finally drawing the text
		pDC->TextOutW(EnclosingRect.TopLeft().x + 5, EnclosingRect.TopLeft().y + 5, string);

		// Drawing the events
		for (int k = 0, n = 1; k < 24; k++)
		{
			if (Curr->m_AuxPtr->Object.GetEventsForTime(k)->GetHead() != nullptr)
			{

				Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux = Curr->m_AuxPtr->Object.GetEventsForTime(k)->GetHead();

				for (int j = 0; Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux != nullptr; Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux = Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux->next)
				{
					if (Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux->Object.GetPlace() != nullptr)
					{
						string.Format(L"%s : %s @ %s", *Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux->Object.GetDescription(), 
							*Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux->Object.GetPlace(), Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux->Object.GetTimeStandardForm());
					}
					else
					{
						string.Format(L"%s @ %s", *Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux->Object.GetDescription(),
							Curr->m_AuxPtr->Object.GetEventsForTime(k)->p_EventAux->Object.GetTimeStandardForm());

					}

					if (EnclosingRect.TopLeft().y + 10 + (15 * (n + 1)) + 5 * (n + 1) >= EnclosingRect.BottomRight().y)
					{
					}
					else if ((EnclosingRect.TopLeft().y + 10 + (15 * (n + 2)) + 5 * (n + 2)) >= EnclosingRect.BottomRight().y)
					{
						pDC->TextOutW(EnclosingRect.TopLeft().x + (5), EnclosingRect.TopLeft().y + 5 + (15 * n) + 5 * n, _T(". . ."));
					}
					else
					{
						pDC->TextOutW(EnclosingRect.TopLeft().x + (5), EnclosingRect.TopLeft().y + 10 + (15 * n) + 5 * n, string);
					}
					n++;
				}

				
			}

		}

		


		// Moves to next node
		Curr->m_AuxPtr = Curr->m_AuxPtr->next;
		// Check if nullptr
		if (Curr->m_AuxPtr == nullptr) break;

		// Set the rectangle as the next cell's rectangle
		EnclosingRect = Curr->m_AuxPtr->Object.m_Cell;
	}

	int Beginning = m_CurrentMonth->ReturnBegDate();

	if (Beginning != 0 )
	{

		if (m_CurrentMonth->ReturnMonthType() == 0 && m_Planner->IsStartYear(m_Year->ReturnYearDate()))
		{

		}
		else
		{
			CMonth* Prev = m_Planner->ReturnPrevMonth();

			CDay* CurrDay;

			

			for (int i = 0; i < Beginning; i++)
			{
				string.Format(L"%d / %d", Prev->ReturnMonthType() + 1, Prev->ReturnDayWithDate(Prev->m_NumberDays - (Beginning - 1 - i))->GetNumber());

				CurrDay = Prev->ReturnDayWithDate(Prev->m_NumberDays - (Beginning - 1 - i));

				EnclosingRect = CRect(CPoint(m_WidthPortion * i, *m_TopBarSize), CPoint(m_WidthPortion * (i+1), *m_TopBarSize + m_HeightPortion));

				pDC->TextOutW(m_WidthPortion * i + 5, *m_TopBarSize + 5, string);

				// Drawing the events
				for (int k = 0, n = 1; k < 24; k++)
				{
					if (CurrDay->GetEventsForTime(k)->GetHead() != nullptr)
					{

						CurrDay->GetEventsForTime(k)->p_EventAux = CurrDay->GetEventsForTime(k)->GetHead();

						for (int j = 0; CurrDay->GetEventsForTime(k)->p_EventAux != nullptr; CurrDay->GetEventsForTime(k)->p_EventAux = CurrDay->GetEventsForTime(k)->p_EventAux->next)
						{
							if (CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetPlace() != nullptr)
							{
								string.Format(L"%s : %s @ %s", *CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetDescription(),
									*CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetPlace(), CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetTimeStandardForm());
							}
							else
							{
								string.Format(L"%s @ %s", *CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetDescription(),
									CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetTimeStandardForm());

							}

							// If there is too many events for the space provided
							if (EnclosingRect.TopLeft().y + 10 + (15 * (n + 1)) + 5 * (n + 1) >= EnclosingRect.BottomRight().y)
							{
							}
							else if ((EnclosingRect.TopLeft().y + 10 + (15 * (n + 2)) + 5 * (n + 2)) >= EnclosingRect.BottomRight().y)
							{
								pDC->TextOutW(EnclosingRect.TopLeft().x + (5), EnclosingRect.TopLeft().y + 5 + (15 * n) + 5 * n, _T(". . ."));
							}
							else
							{
								pDC->TextOutW(EnclosingRect.TopLeft().x + (5), EnclosingRect.TopLeft().y + 10 + (15 * n) + 5 * n, string);
							}
							n++;
						}
					}
				}

			}	
		}

	}

	int Ending = m_CurrentMonth->ReturnDayWithDate(m_CurrentMonth->m_NumberDays)->GetDayOfWeek();

	if (Ending < 6)
	{
		if (m_CurrentMonth->ReturnMonthType() == 11 && m_Planner->IsLastYear(m_Year->ReturnYearDate()))
		{

		}
		else
		{
			CMonth* Next = m_Planner->ReturnNextMonth();
			CDay * CurrDay;

			for (int i = Ending + 1, l = 1; i < 7; i++, l++)
			{
				CurrDay = Next->ReturnDayWithDate(l);

				string.Format(L"%d / %d", Next->ReturnMonthType() + 1, Next->ReturnDayWithDate(l)->GetNumber());

				EnclosingRect = CRect(CPoint(m_WidthPortion * i, m_HeightPortion * (*m_Rows - 1) + *m_TopBarSize), CPoint(m_WidthPortion * (i + 1), m_HeightPortion * (*m_Rows) + *m_TopBarSize));

				pDC->TextOutW(m_WidthPortion * i + 5, m_HeightPortion * (*m_Rows - 1) + *m_TopBarSize + 5, string);

				// Drawing the events
				for (int k = 0, n = 1; k < 24; k++)
				{
					if (CurrDay->GetEventsForTime(k)->GetHead() != nullptr)
					{

						CurrDay->GetEventsForTime(k)->p_EventAux = CurrDay->GetEventsForTime(k)->GetHead();

						for (int j = 0; CurrDay->GetEventsForTime(k)->p_EventAux != nullptr; CurrDay->GetEventsForTime(k)->p_EventAux = CurrDay->GetEventsForTime(k)->p_EventAux->next)
						{
							if (CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetPlace() != nullptr)
							{
								string.Format(L"%s : %s @ %s", *CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetDescription(),
									*CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetPlace(), CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetTimeStandardForm());
							}
							else
							{
								string.Format(L"%s @ %s", *CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetDescription(),
									CurrDay->GetEventsForTime(k)->p_EventAux->Object.GetTimeStandardForm());

							}

							// Placing in correct position
							// If the event is out of view
							if (EnclosingRect.TopLeft().y + 10 + (15 * (n + 1)) + 5 * (n + 1) >= EnclosingRect.BottomRight().y)
							{
							}
							// If the event in the first out of view
							else if ((EnclosingRect.TopLeft().y + 10 + (15 * (n + 2)) + 5 * (n + 2)) >= EnclosingRect.BottomRight().y)
							{
								pDC->TextOutW(EnclosingRect.TopLeft().x + (5), EnclosingRect.TopLeft().y + 5 + (15 * n) + 5 * n, _T(". . ."));
							}
							// If the event is within view
							else
							{
								pDC->TextOutW(EnclosingRect.TopLeft().x + (5), EnclosingRect.TopLeft().y + 10 + (15 * n) + 5 * n, string);
							}
							n++;
						}
					}
				}
			}
		}
	}

	// Resetting the font
	pDC->SelectObject(def_font);

	// Deleting the objects
	font.DeleteObject();
	NewBrush.DeleteObject();


}

int CViewMonthly::OnNextMonth()
{
	/*
	// Local Vars
	int error = 0;
	bool NoChange = 0;
	int PrevYearDate = -1;

	
	error = m_Year->MoveMonth(1);

	if (m_CurrentMonth->ReturnMonthType() == 11)
		error = 0;

	if (!error)
	{
		PrevYearDate = m_Year->ReturnYearDate();

		m_Planner->IncrementCurrentYear(1);
		m_Year = m_Planner->ReturnCurrentYear();
		if (PrevYearDate != m_Year->ReturnYearDate()) m_Year->SetCurrentMonth(0);
		else
		{
			NoChange = 1;
		}
	}
	*/

	m_SizeChanged = 1;

	int error = m_Planner->MoveCurrMonth(1);

	m_Year = m_Planner->ReturnCurrentYear();

	return error;
}



int CViewMonthly::OnPrevMonth()
{
	/*
	// Local Vars
	int error = 0;
	bool NoChange = 0;
	int PrevYearDate = -1;

	m_SizeChanged = 1;
	error = m_Year->MoveMonth(-1);

	if (m_CurrentMonth->ReturnMonthType() == 0)
		error = 0;

	if (!error)
	{


		PrevYearDate = m_Year->ReturnYearDate();

		m_Planner->DecrementCurrentYear(1);
		m_Year = m_Planner->ReturnCurrentYear();
		if (PrevYearDate != m_Year->ReturnYearDate()) m_Year->SetCurrentMonth(11);
		else
		{
			NoChange = 1;
		}
	}
	*/


	m_SizeChanged = 1;

	int error = m_Planner->MoveCurrMonth(-1);

	m_Year = m_Planner->ReturnCurrentYear();

	return 0;

}

int CViewMonthly::OnNextYear()
{
	/*
	// Local Vars
	int PrevYearDate = -1;
	int Change = 0;
	int PrevMonthDate = m_Year->CurrentMonth()->ReturnMonthType();

	m_SizeChanged = 1;

	PrevYearDate = m_Year->ReturnYearDate();

	m_Planner->IncrementCurrentYear(1);
	m_Year = m_Planner->ReturnCurrentYear();
	m_Year->SetCurrentMonth(PrevMonthDate);

	if (PrevYearDate != m_Year->ReturnYearDate()) Change = 1;
	*/

	m_SizeChanged = 1;

	int error = m_Planner->MoveCurrYear(1);

	m_Year = m_Planner->ReturnCurrentYear();

	return 1;
}

int CViewMonthly::OnPrevYear()
{

	m_SizeChanged = 1;

	int error = m_Planner->MoveCurrYear(-1);

	m_Year = m_Planner->ReturnCurrentYear();

	return 1;
}

int CViewMonthly::MoveRow(int Movement)
{

	int error = 0;

	if (Movement > 0)
	{
		error = OnNextMonth();
	}
	else
	{
		error = OnPrevMonth();
	}

	return error;
}

bool CViewMonthly::SetObject(CPoint Point, CDay &DayObject)
{

	// Local Variables
	CLLNode* Curr;
	CRect EnclosingRect;
	CString string;


	// Traversing the head of the list of days within the month object
	Curr = m_CurrentMonth->GetList();
	Curr->m_AuxPtr = Curr->GetHead();

	// Getting each cell's dimensions
	EnclosingRect = Curr->m_AuxPtr->Object.m_Cell;

	// Traversing the linked list structure of each month, 
	// and drawing the contents of each cell.
	for (int i = 0; i < m_CurrentMonth->m_NumberDays; i++)
	{
		// Sets CString object format
		string.Format(L"%u.", Curr->m_AuxPtr->Object.GetNumber());
		// Writes the number of this day to the corner of this cell

		if (Point.x >= Curr->m_AuxPtr->Object.m_Cell.TopLeft().x &&
			Point.y >= Curr->m_AuxPtr->Object.m_Cell.TopLeft().y &&
			Point.x <= Curr->m_AuxPtr->Object.m_Cell.BottomRight().x &&
			Point.y <= Curr->m_AuxPtr->Object.m_Cell.BottomRight().y)
		{
			DayObject = Curr->m_AuxPtr->Object;
			m_SelectedDay = &Curr->m_AuxPtr->Object;
			m_SelectedDay->m_Cell = EnclosingRect;
			return 1;
		}

		// Moves to next node
		Curr->m_AuxPtr = Curr->m_AuxPtr->next;
		// Check if nullptr
		if (Curr->m_AuxPtr == nullptr) break;

		// Set the rectangle as the next cell's rectangle
		EnclosingRect = Curr->m_AuxPtr->Object.m_Cell;
	}

	int Beginning = m_CurrentMonth->ReturnBegDate();

	if (Beginning != 0)
	{
		CMonth* Prev = m_Planner->ReturnPrevMonth();

		for (int i = 0; i < Beginning; i++)
		{


		}


	}

	int Ending = m_CurrentMonth->ReturnDayWithDate(m_CurrentMonth->m_NumberDays)->GetDayOfWeek();

	if (Ending < 6)
	{
		CMonth* Next = m_Planner->ReturnNextMonth();

		for (int i = Ending + 1, n = 1; i < 7; i++, n++)
		{


		}


	}
	return 0;
}

bool CViewMonthly::ResetSelectedObject()
{
	m_SelectedDay = nullptr;

	return 1;
}