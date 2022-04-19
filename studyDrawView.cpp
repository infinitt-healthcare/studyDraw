
// studyDrawView.cpp: CstudyDrawView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "studyDraw.h"
#endif

#include "studyDrawDoc.h"
#include "studyDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"


// CstudyDrawView

IMPLEMENT_DYNCREATE(CstudyDrawView, CView)

BEGIN_MESSAGE_MAP(CstudyDrawView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_MODE_PICTURE, &CstudyDrawView::OnModePicture)
	ON_COMMAND(IDM_MODE_RECTANGLE, &CstudyDrawView::OnModeRectangle)
END_MESSAGE_MAP()

// CstudyDrawView 생성/소멸

CstudyDrawView::CstudyDrawView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CstudyDrawView::~CstudyDrawView()
{
}

BOOL CstudyDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CstudyDrawView 그리기

void CstudyDrawView::OnDraw(CDC* pDC)
{
	CstudyDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->m_arrayShape.size())
	{
		for (const auto shape : pDoc->m_arrayShape)
		{
			shape->draw(pDC);
		}
	}
	
}


// CstudyDrawView 인쇄

BOOL CstudyDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CstudyDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CstudyDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CstudyDrawView 진단

#ifdef _DEBUG
void CstudyDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CstudyDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CstudyDrawDoc* CstudyDrawView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CstudyDrawDoc)));
	return (CstudyDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CstudyDrawView 메시지 처리기


void CstudyDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CstudyDrawDoc* pDoc = GetDocument();
	if (pDoc->m_nMouse_Mode == 1)
	{
		pDoc->m_pDrawShape = new DrawLine();
		static_cast<DrawLine*>(pDoc->m_pDrawShape)->m_logPen(pDoc->m_logPen);
		static_cast<DrawLine*>(pDoc->m_pDrawShape)->m_arrayLine.push_back(point);
	}
	else if (pDoc->m_nMouse_Mode == 2)
	{
		pDoc->m_pDrawShape = new DrawBmp();
		static_cast<DrawBmp*>(pDoc->m_pDrawShape)->rect_TopLeft(point);
		static_cast<DrawBmp*>(pDoc->m_pDrawShape)->m_bmpId(pDoc->m_lpcwstrBmpId);
	}
	else if (pDoc->m_nMouse_Mode == 3)
	{
		pDoc->m_pDrawShape = new DrawRect();
		static_cast<DrawRect*>(pDoc->m_pDrawShape)->m_logPen(pDoc->m_logPen);
		static_cast<DrawRect*>(pDoc->m_pDrawShape)->rect_TopLeft(point);
	}
	/*else if (pDoc->m_nMouse_Mode == 0)
	{
		for (DrawBmp& bmp : pDoc->d_pictures) {
			bmp.isClicked = false;
		}
		for (DrawBmp& bmp : pDoc->d_pictures)
		{
			CRect rect(bmp.pos2.x - 30, bmp.pos2.y - 30, bmp.pos2.x + 30, bmp.pos2.y + 30);

			bmp.isClicked = rect.PtInRect(point);
			if (bmp.isClicked) {
				m_pDrawBmp = &bmp;
				break;
			}
		}
	}*/
	
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void CstudyDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CstudyDrawDoc* pDoc = GetDocument();
	CClientDC dc(this);

	if (pDoc->m_nMouse_Mode == 1)
	{
		pDoc->m_arrayShape.push_back(pDoc->m_pDrawShape);
	}
	else if (pDoc->m_nMouse_Mode == 2)
	{
		static_cast<DrawBmp*>(pDoc->m_pDrawShape)->rect_BottomRight(point);
		pDoc->m_pDrawShape->draw(&dc);
		pDoc->m_arrayShape.push_back(pDoc->m_pDrawShape);
	}
	else if (pDoc->m_nMouse_Mode == 3)
	{
		static_cast<DrawRect*>(pDoc->m_pDrawShape)->rect_BottomRight(point);
		pDoc->m_pDrawShape->draw(&dc);
		pDoc->m_arrayShape.push_back(pDoc->m_pDrawShape);
	}

	/*else if (pDoc->uMouse_Mode == 0)
	{
		for (DrawBmp& bmp : pDoc->d_pictures)
		{
			
			if (bmp.isClicked)
			{
				bmp.pos2 = point;
				bmp.isClicked = false;
			}
		}
		pDoc->UpdateAllViews(NULL);
	}*/
	
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


void CstudyDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	CstudyDrawDoc* pDoc = GetDocument();
	CClientDC dc(this);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON && pDoc->m_nMouse_Mode == 1)
	{
		
		pDoc->m_pDrawShape->draw(&dc);
		static_cast<DrawLine*>(pDoc->m_pDrawShape)->m_arrayLine.push_back(point);
	}

//	else if ((nFlags & MK_LBUTTON) == MK_LBUTTON && pDoc->uMouse_Mode == 0)
//	{
////		for (DrawBmp& bmp : pDoc->d_pictures)
////		{
//			if (m_pDrawBmp != NULL)
//			{
//				m_pDrawBmp->pos2 = point;
//				m_pDrawBmp->drawBmp(&dc);
//			}
////		}
//	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->SetMousePositionOutput(point);

	CView::OnMouseMove(nFlags, point);
}




void CstudyDrawView::OnModePicture()
{
	CstudyDrawDoc* pDoc = GetDocument();
	pDoc->m_nMouse_Mode = 2;
}


void CstudyDrawView::OnModeRectangle()
{
	CstudyDrawDoc* pDoc = GetDocument();
	pDoc->m_nMouse_Mode = 3;
}
