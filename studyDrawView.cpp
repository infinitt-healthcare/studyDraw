
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

	if (pDoc->d_pictures.size())
	{
		for (const DrawBmp& bmp : pDoc->d_pictures)
		{
			bmp.drawBmp(pDC);
		}
	}
	
	if (pDoc->d_lines.size())
	{
		for (const DrawLine& line : pDoc->d_lines)
		{
			line.drawAllLine(pDC);
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
	if (pDoc->uMouse_Mode == 1)
	{
		pDoc->d_line.line_Array.clear();
		pDoc->d_line.line_Array.push_back(point);
	}
	else if (pDoc->uMouse_Mode == 2)
	{
		pDoc->d_picture.pos1 = point;
	}
	else if (pDoc->uMouse_Mode == 0)
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
	}
	
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}

//의존성 역전 // 공통점 추상화 
void CstudyDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CstudyDrawDoc* pDoc = GetDocument();
	if (pDoc->uMouse_Mode == 1)
	{
		pDoc->d_lines.push_back(pDoc->d_line);
	}
	else if (pDoc->uMouse_Mode == 2)
	{
		pDoc->d_picture.pos2 = point;
		CClientDC dc(this);

		pDoc->d_picture.drawBmp(&dc);
		pDoc->d_pictures.push_back(pDoc->d_picture);
	}
	else if (pDoc->uMouse_Mode == 0)
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
	}
	
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


void CstudyDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	CstudyDrawDoc* pDoc = GetDocument();
	CClientDC dc(this);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON && pDoc->uMouse_Mode == 1)
	{
		
		pDoc->d_line.DrawLastLine(&dc, point);
		pDoc->d_line.push_back(point);
	}
	else if ((nFlags & MK_LBUTTON) == MK_LBUTTON && pDoc->uMouse_Mode == 0)
	{
//		for (DrawBmp& bmp : pDoc->d_pictures)
//		{
			if (m_pDrawBmp != NULL)
			{
				m_pDrawBmp->pos2 = point;
				m_pDrawBmp->drawBmp(&dc);
			}
//		}
	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->SetMousePositionOutput(point);

	CView::OnMouseMove(nFlags, point);
}




void CstudyDrawView::OnModePicture()
{
	CstudyDrawDoc* pDoc = GetDocument();
	pDoc->uMouse_Mode = 2;
}
