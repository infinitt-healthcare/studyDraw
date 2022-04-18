
// studyDrawDoc.cpp: CstudyDrawDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "studyDraw.h"
#endif

#include "studyDrawDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>

// CstudyDrawDoc

IMPLEMENT_DYNCREATE(CstudyDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CstudyDrawDoc, CDocument)
	ON_COMMAND(IDM_COLOR_RED, &CstudyDrawDoc::OnColorRed)
	ON_COMMAND(IDM_COLOR_GREEN, &CstudyDrawDoc::OnColorGreen)
	ON_COMMAND(IDM_COLOR_BLUE, &CstudyDrawDoc::OnColorBlue)
	ON_UPDATE_COMMAND_UI(IDM_COLOR_RED, &CstudyDrawDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(IDM_COLOR_GREEN, &CstudyDrawDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(IDM_COLOR_BLUE, &CstudyDrawDoc::OnUpdateColorBlue)
	ON_COMMAND(IDM_LINESIZE_1PX, &CstudyDrawDoc::OnLinesize1px)
	ON_COMMAND(IDM_LINESIZE_3PX, &CstudyDrawDoc::OnLinesize3px)
	ON_COMMAND(IDM_LINESIZE_5PX, &CstudyDrawDoc::OnLinesize5px)
	ON_UPDATE_COMMAND_UI(IDM_LINESIZE_1PX, &CstudyDrawDoc::OnUpdateLinesize1px)
	ON_UPDATE_COMMAND_UI(IDM_LINESIZE_3PX, &CstudyDrawDoc::OnUpdateLinesize3px)
	ON_UPDATE_COMMAND_UI(IDM_LINESIZE_5PX, &CstudyDrawDoc::OnUpdateLinesize5px)
	ON_COMMAND(IDM_LINESTYLE_PSSOLID, &CstudyDrawDoc::OnLinestylePssolid)
	ON_COMMAND(IDM_LINESTYLE_PSDASH, &CstudyDrawDoc::OnLinestylePsdash)
	ON_UPDATE_COMMAND_UI(IDM_LINESTYLE_PSSOLID, &CstudyDrawDoc::OnUpdateLinestylePssolid)
	ON_UPDATE_COMMAND_UI(IDM_LINESTYLE_PSDASH, &CstudyDrawDoc::OnUpdateLinestylePsdash)
	ON_COMMAND(IDM_MODE_CURSUR, &CstudyDrawDoc::OnModeCursur)
	ON_COMMAND(IDM_MODE_DRAW, &CstudyDrawDoc::OnModeDraw)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_COLOR, &CstudyDrawDoc::OnUpdateIndicatorColor)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_STYLE, &CstudyDrawDoc::OnUpdateIndicatorStyle)
	ON_COMMAND(IDM_SELECT_BMP_FLOWER, &CstudyDrawDoc::OnSelectBmpFlower)
	ON_COMMAND(IDM_SELECT_BMP_NIGHTSKY, &CstudyDrawDoc::OnSelectBmpNightsky)
	ON_UPDATE_COMMAND_UI(IDM_MODE_DRAW, &CstudyDrawDoc::OnUpdateModeDraw)
	ON_UPDATE_COMMAND_UI(IDM_SELECT_BMP_FLOWER, &CstudyDrawDoc::OnUpdateSelectBmpFlower)
	ON_UPDATE_COMMAND_UI(IDM_SELECT_BMP_NIGHTSKY, &CstudyDrawDoc::OnUpdateSelectBmpNightsky)
	ON_UPDATE_COMMAND_UI(IDM_MODE_PICTURE, &CstudyDrawDoc::OnUpdateModePicture)
	ON_COMMAND(IDM_INFORMATION_STATUS, &CstudyDrawDoc::OnInformationStatus)
END_MESSAGE_MAP()


// CstudyDrawDoc 생성/소멸

CstudyDrawDoc::CstudyDrawDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CstudyDrawDoc::~CstudyDrawDoc()
{
}

BOOL CstudyDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	uMouse_Mode = 0; 
	d_line.line_Pen.lopnStyle = 0;
	d_line.line_Pen.lopnColor = RGB(255, 0, 0);
	d_line.line_Pen.lopnWidth.x = 1;
	d_picture.fileName = (LPCWSTR)"";
	return TRUE;
}


// CstudyDrawDoc serialization

void CstudyDrawDoc::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{

	}
	else
	{

	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CstudyDrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CstudyDrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CstudyDrawDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CstudyDrawDoc 진단

#ifdef _DEBUG
void CstudyDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CstudyDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CstudyDrawDoc 명령


void CstudyDrawDoc::OnColorRed()
{
	d_line.line_Pen.lopnColor = RGB(255, 0, 0);
}


void CstudyDrawDoc::OnColorGreen()
{
	d_line.line_Pen.lopnColor = RGB(0, 255, 0);
}


void CstudyDrawDoc::OnColorBlue()
{
	d_line.line_Pen.lopnColor = RGB(0, 0, 255);
}


void CstudyDrawDoc::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(uMouse_Mode == 1);
	pCmdUI->SetCheck(d_line.line_Pen.lopnColor == RGB(255, 0, 0));
}


void CstudyDrawDoc::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(uMouse_Mode == 1);
	pCmdUI->SetCheck(d_line.line_Pen.lopnColor == RGB(0, 255, 0));
}


void CstudyDrawDoc::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(uMouse_Mode == 1);
	pCmdUI->SetCheck(d_line.line_Pen.lopnColor == RGB(0, 0, 255));
}


void CstudyDrawDoc::OnLinesize1px()
{
	d_line.line_Pen.lopnWidth.x = 1;
}


void CstudyDrawDoc::OnLinesize3px()
{
	d_line.line_Pen.lopnWidth.x = 3;
}


void CstudyDrawDoc::OnLinesize5px()
{
	d_line.line_Pen.lopnWidth.x = 5;
}


void CstudyDrawDoc::OnUpdateLinesize1px(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(uMouse_Mode == 1);
	pCmdUI->SetCheck(d_line.line_Pen.lopnWidth.x == 1);
}


void CstudyDrawDoc::OnUpdateLinesize3px(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(uMouse_Mode == 1);
	pCmdUI->SetCheck(d_line.line_Pen.lopnWidth.x == 3);
}


void CstudyDrawDoc::OnUpdateLinesize5px(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(d_line.line_Pen.lopnWidth.x == 5);
	pCmdUI->Enable(uMouse_Mode == 1);
}
void CstudyDrawDoc::OnLinestylePssolid()
{
	d_line.line_Pen.lopnStyle = 0;
	uMouse_Mode = 1;
}


void CstudyDrawDoc::OnLinestylePsdash()
{
	d_line.line_Pen.lopnStyle = 1;
	uMouse_Mode = 1;
}


void CstudyDrawDoc::OnUpdateLinestylePssolid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(d_line.line_Pen.lopnStyle == 0);
	pCmdUI->Enable(uMouse_Mode == 1);
}


void CstudyDrawDoc::OnUpdateLinestylePsdash(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(d_line.line_Pen.lopnStyle == 1);
	pCmdUI->Enable(uMouse_Mode==1);
}


void CstudyDrawDoc::OnModeCursur()
{
	uMouse_Mode = 0;

}


void CstudyDrawDoc::OnModeDraw()
{
	uMouse_Mode = 1;
}


void CstudyDrawDoc::OnUpdateIndicatorColor(CCmdUI* pCmdUI)
{
	
	if(uMouse_Mode == 0)
	{
		pCmdUI->SetText(_T("마우스 커서 모드"));
	}
	else if (uMouse_Mode == 1)
	{
		switch (d_line.line_Pen.lopnColor)
		{
		case RGB(255, 0, 0):
			pCmdUI->SetText(_T("빨간색"));
			break;
		case RGB(0, 255, 0):
			pCmdUI->SetText(_T("초록색"));
			break;
		case RGB(0, 0, 255):
			pCmdUI->SetText(_T("파란색"));
			break;

		}
	}
	else if (uMouse_Mode == 2)
	{
		pCmdUI->SetText(_T("그림 삽입 모드"));
	}
	
}


void CstudyDrawDoc::OnUpdateIndicatorStyle(CCmdUI* pCmdUI)
{
	if (uMouse_Mode == 1)
	{
		switch (d_line.line_Pen.lopnStyle)
		{
		case 0:
			pCmdUI->SetText(_T("PS_SOLID"));
			break;
		case 1:
			pCmdUI->SetText(_T("PS_DASH"));
			break;
		}
	}
	else
	{
		pCmdUI->SetText(_T(""));
	}
	
}


void CstudyDrawDoc::OnSelectBmpFlower()
{
	d_picture.fileName = (LPCWSTR)IDB_FLOWER;
}


void CstudyDrawDoc::OnSelectBmpNightsky()
{
	d_picture.fileName = (LPCWSTR)IDB_NIGHTSKY;
}


void CstudyDrawDoc::OnUpdateModeDraw(CCmdUI* pCmdUI)
{
	
}


void CstudyDrawDoc::OnUpdateSelectBmpFlower(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(d_picture.fileName == (LPCWSTR)IDB_FLOWER);
}


void CstudyDrawDoc::OnUpdateSelectBmpNightsky(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(d_picture.fileName == (LPCWSTR)IDB_NIGHTSKY);
}


void CstudyDrawDoc::DeleteContents()
{
	d_lines.clear();
	d_pictures.clear();

	CDocument::DeleteContents();
}


void CstudyDrawDoc::OnUpdateModePicture(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!(d_picture.fileName==(LPCWSTR)""));
}


void CstudyDrawDoc::OnInformationStatus()
{

	AfxMessageBox(_T("HI"));
}
 