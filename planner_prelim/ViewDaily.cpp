#include "stdafx.h"
#include "ViewBase.h"


// CTOR for a CViewDaily subview object
CViewDaily::CViewDaily(int *Width, int *Height, int * TopBarPortion, CPlannerObject* Object) :
	CViewBase(0, 0, Height, Width, TopBarPortion, Object), m_PreviousMonth(0), m_TimeOffset(0)
{
	m_Rows = new unsigned;
	m_Columns =  new unsigned;

	*m_Rows = 10;
	*m_Columns = 2;
}

//
// DrawLayout()
// Draws the entire user layout for this Daily view
//
void CViewDaily::DrawLayout(CDC* pDC, CPlannerView* View)
{


	// Initialize variables if not already
	if (m_Width == 0 || m_Height == 0 || m_SizeChanged)
	{
		InitilizeWndVariables(View);
		m_CurrentMonth->ResetCells(m_WidthPortion, m_HeightPortion);
	}

	// Get the current day object
	SetDay();

	// Drawing a default background
	FillBackground(pDC, View);

	// Drawing the month section
	DrawMonthSection(pDC, View);

	// Drawing the topbar section
	DrawTopBarSection(pDC, View);

	// Drawing the basicc grid layout
	DrawGrid(pDC, View);

}

// Sets the current day object
void CViewDaily::SetDay()
{

	// Getting today's time information
	time_t Time = time(NULL);
	tm* p_Time = localtime(&Time);

	
	// If the month has been changed, change the current day object
	if (m_PreviousMonth != m_CurrentMonth->ReturnMonthType())
	{

		// If this month, then set the current day to today's date
		if (m_CurrentMonth->ReturnMonthType() == p_Time->tm_mon &&
			m_CurrentMonth->ReturnDayWithDate(1)->GetYear() == m_Year->ReturnYearDate())
		{
			// Set the day object
			m_CurrDay = m_CurrentMonth->ReturnDayWithDate(p_Time->tm_mday);
		}

		else
		{
			// Otherwise set the date as the first of the month
			m_CurrDay = m_CurrentMonth->ReturnDayWithDate(1);
		}
	}

	// Storing this month type
	m_PreviousMonth = m_CurrentMonth->ReturnMonthType();
}

//
// DrawGrid()
// Draws the basic grid elemments of the UI for this daily view
//
void CViewDaily::DrawGrid(CDC* pDC, CPlannerView* View)
{
	// Local Variables
	CPen aPen(PS_SOLID, 3, RGB(30, 40, 50));
	CPen *OldPen = nullptr;

	// Selecting the new pen
	OldPen = pDC->SelectObject(&aPen);

	// Drawing main dividing line
	pDC->MoveTo(*m_Width / 2, *m_TopBarSize);
	pDC->LineTo(*m_Width / 2, *m_Height);

	// Restoring the pen object
	pDC->SelectObject(OldPen);

	// Drawing the right section of this view
	DrawRightSection(pDC, View, *m_TopBarSize, *m_Height, m_WidthPortion, *m_Width);

	

	

}

//
//
//
//
void CViewDaily::DrawLeftSection(CDC* pDC, CPlannerView* View, int HeightMin, int HeightMax, int WidthMin, int WidthMax)
{



}


//
//
//
//
void CViewDaily::DrawCenterSection(CDC* pDC, CPlannerView* View, int HeightMin, int HeightMax, int WidthMin, int WidthMax)
{
	// Local Variables
	CString String;

	int BegIndex = 0 + m_TimeOffset;





}


//
// DrawRightSection()
// Draws the hourly section of this view, called from DrawGrid().
// By having this in its own function, the coordinates can be simplified further,
// making it easier to maintain and read.
//
void CViewDaily::DrawRightSection(CDC* pDC, CPlannerView* View, int HeightMin, int HeightMax, int WidthMin, int WidthMax)
{
	// Local Variables
	int HeightPortion = (HeightMax - HeightMin) / 10;

	//CString String;
	//String.Format(L"HeightMX: %d HeightMN: %d Rows: %d Portion: %d", HeightMax, HeightMin, *m_Rows, HeightPortion);

	//AfxMessageBox(String);

	for (int i = 0; i < 10; i++)
	{

		pDC->MoveTo(WidthMin, HeightMax - (HeightPortion * i));
		pDC->LineTo(WidthMax, HeightMax - (HeightPortion * i));

	}

}

//
// DrawTopBarSection()
// Draws the unique top bar for this daily view
//
void CViewDaily::DrawTopBarSection(CDC* pDC, CPlannerView* View)
{

	// Local Variables
	int FontSize = 22;
	CFont font;
	CRect EnclosingRect(CPoint(0, 37), CPoint(*m_Width, *m_TopBarSize));
	CBrush NewBrush;
	CString String;

	// Set the background mode as transparent so text will
	// appear accordingly
	pDC->SetBkMode(TRANSPARENT);

	// Drawing the top bar section
	pDC->MoveTo(0, *m_TopBarSize);
	pDC->LineTo(*m_Width, *m_TopBarSize);

	// Create the font
	VERIFY(font.CreateFont(
		FontSize,                  // nHeight
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
		_T("Cambria")));           // lpszFacename

								   // Save the default font, and set the new font
	CFont* def_font = pDC->SelectObject(&font);

	// Create the new brush
	NewBrush.CreateSolidBrush(RGB(140, 120, 120));

	// Set the color of the text 
	pDC->SetTextColor(RGB(50, 50, 50));

	// Color in the rectangle for this section of the topbar
	pDC->FillRect(EnclosingRect, &NewBrush);

	// Formatting the String for the first section
	String.Format(L"Tasks for %d/%d", m_CurrentMonth->ReturnMonthType() + 1, m_CurrDay->GetNumber());
	pDC->TextOutW(m_WidthPortion * 0 + (m_WidthPortion / 50), 37, String);

	// Reformatting the String for the second section
	String.Format(L"Hourly Events");
	pDC->TextOutW(m_WidthPortion * 1 + (m_WidthPortion / 50), 37, String);

	// Selecting the old object
	pDC->SelectObject(def_font);

	// Deleting objects
	font.DeleteObject();
	NewBrush.DeleteObject();

}


//
//
//
//
int CViewDaily::OnNextMonth()
{

	if (!(m_CurrentMonth->m_NumberDays < m_CurrDay->GetNumber() + 1))
	{

		m_CurrDay = m_CurrentMonth->ReturnDayWithDate(m_CurrDay->GetNumber() + 1);

	}

	return 0;
}

//
//
//
//
int CViewDaily::OnPrevMonth()
{

	if (!(0 >= m_CurrDay->GetNumber() - 1))
	{

		m_CurrDay = m_CurrentMonth->ReturnDayWithDate(m_CurrDay->GetNumber() - 1);

	}

	return 0;
}

//
// OnNextYear()
// Message handler for the next year toolbar button --
// Moves to the next month in this planner object
//
int CViewDaily::OnNextYear()
{
	// Moving the current month
	m_Planner->MoveCurrMonth(1);
	
	// Getting the new current year if there was a change
	m_Year = m_Planner->ReturnCurrentYear();

	m_SizeChanged = 1;

	return 1;
}


//
// OnPrevYear()
// Message handler for the prev year button -- 
// Moves to the previous month in this planner object
//
int CViewDaily::OnPrevYear()
{

	// Moving the current month
	m_Planner->MoveCurrMonth(-1);

	// Getting the new current year if there was a change
	m_Year = m_Planner->ReturnCurrentYear();

	m_SizeChanged = 1;

	return 1;
}