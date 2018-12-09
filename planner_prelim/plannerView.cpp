
// plannerView.cpp : implementation of the CPlannerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "planner_prelim.h"
#endif

#include "plannerDoc.h"
#include "planner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlannerView

IMPLEMENT_DYNCREATE(CPlannerView, CView)

BEGIN_MESSAGE_MAP(CPlannerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlannerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_NEXT_MONTH, &CPlannerView::OnNextMonth)
	ON_COMMAND(ID_PREV_MONTH, &CPlannerView::OnPrevMonth)
	ON_COMMAND(ID_YEAR_PLUS, &CPlannerView::OnYearPlus)
	ON_COMMAND(ID_YEAR_MINUS, &CPlannerView::OnYearMinus)
	ON_COMMAND(ID_VIEW_MONTHLY, &CPlannerView::OnViewMonthly)
	ON_COMMAND(ID_VIEW_WEEKLY, &CPlannerView::OnViewWeekly)
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_DAILY, &CPlannerView::OnViewDaily)
END_MESSAGE_MAP()

// CPlannerView construction/destruction

CPlannerView::CPlannerView() : m_Rows(5), m_Columns(7), m_Height(0),
m_Width(0), m_TopBarSize(60),  m_Planner(2018, 2028, this), m_DialogMax(1), m_DialogCount(0),
m_MonthlyView(&m_Rows, &m_Columns, &m_Height, &m_Width, &m_TopBarSize, &m_Planner),
m_WeeklyView(&m_Rows, &m_Columns, &m_Height, &m_Width, &m_TopBarSize, &m_Planner),
m_DailyView(&m_Width, &m_Height, &m_TopBarSize, &m_Planner)
{

	//m_CurrentView = &m_WeeklyView;
	m_CurrentView = &m_DailyView;
}

CPlannerView::~CPlannerView()
{
}

BOOL CPlannerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlannerView drawing

void CPlannerView::OnDraw(CDC* pDC)
{
	// Creating a CMemDC object
	CMemDC DpDC(*pDC, this);

	// Setting the current device context to this new device context
	pDC = &DpDC.GetDC();


	CPlannerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	
	// Gets the current client dimensions of this view object
	this->GetClientRect(&rect);

	// Sets appropriate variables to these dimensions
	m_Height = rect.Height();
	m_Width = rect.Width();
	

	m_CurrentView->DrawLayout(pDC, this);


}

// CPlannerView Initialization

// CPlannerView printing


void CPlannerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlannerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlannerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlannerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlannerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlannerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlannerView diagnostics

#ifdef _DEBUG
void CPlannerView::AssertValid() const
{
	CView::AssertValid();
}

void CPlannerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlannerDoc* CPlannerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlannerDoc)));
	return (CPlannerDoc*)m_pDocument;
}
#endif //_DEBUG

void CPlannerView::WindowDestroyed()
{
	m_DialogCount--;

	CRect *Rect = nullptr;

	if (m_CurrentView->GetSelectedObject() != nullptr)
	{
		Rect = m_CurrentView->GetSelectedRect();
	}

	
	m_CurrentView->ResetSelectedObject();
	InvalidateRect(nullptr);
}

int CPlannerView::SetDayObject(CDay *Day)
{

	m_Planner.SetDayObject(Day);
	InvalidateRect(Day->m_Cell);
	return 0;
}

// CPlannerView message handlers in PLANNER.cpp

