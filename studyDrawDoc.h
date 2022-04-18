
// studyDrawDoc.h: CstudyDrawDoc 클래스의 인터페이스
//


#pragma once
#include <vector>
using namespace std;


class DrawLine
{
public:
	LOGPEN line_Pen;
	vector<CPoint> line_Array;
	virtual void drawAllLine(CDC* dc) const
	{
		dc->MoveTo(line_Array[0]);
		CPen pen(line_Pen.lopnStyle, line_Pen.lopnWidth.x, line_Pen.lopnColor);
		CPen* pOldPen = dc->SelectObject(&pen);
		for (const CPoint& pt : line_Array)
		{
			dc->LineTo(pt);
		}
		dc->SelectObject(pOldPen);
	}
	void DrawLastLine(CDC* dc, CPoint&point) const
	{
		CPen pen(line_Pen.lopnStyle, line_Pen.lopnWidth.x, line_Pen.lopnColor);
		CPen* pOldPen = dc->SelectObject(&pen);
		dc->MoveTo(line_Array[line_Array.size() - 1]);
		dc->LineTo(point);
		dc->SelectObject(pOldPen);
	}
	void push_back(const CPoint& point)
	{
		line_Array.push_back(point);
	}
};

class DrawBmp
{
public:
	LPCWSTR fileName;
	CPoint pos1;
	CPoint pos2;
	bool isClicked = false;

	void drawBmp(CDC* dc) const
	{
		CDC MemDC;
		BITMAP bmpInfo;
		MemDC.CreateCompatibleDC(dc);

		CBitmap bmp;
		CBitmap* pOldBmp = NULL;
		bmp.LoadBitmap(fileName);

		bmp.GetBitmap(&bmpInfo);
		pOldBmp = MemDC.SelectObject(&bmp);

		dc->StretchBlt(pos1.x, pos1.y,			//출력될 좌표
			abs(pos2.x-pos1.x), abs(pos2.y - pos1.y) ,
			&MemDC,
			0, 0,			//원본 이미지 좌표
			bmpInfo.bmWidth, bmpInfo.bmHeight,			//원본 이미지의 폭과 높이
			SRCCOPY);
		MemDC.SelectObject(pOldBmp);
		MemDC.DeleteDC();
	
	}
};

class CstudyDrawDoc : public CDocument
{
protected: // serialization에서만 만들어집니다. 
	CstudyDrawDoc() noexcept;
	DECLARE_DYNCREATE(CstudyDrawDoc)

// 특성입니다.
public:
	DrawLine d_line;
	vector<DrawLine> d_lines;
	DrawBmp d_picture;
	vector<DrawBmp> d_pictures;
	int uMouse_Mode;
// 작업입니다.
public:
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CstudyDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
	afx_msg void OnLinesize1px();
	afx_msg void OnLinesize3px();
	afx_msg void OnLinesize5px();
	afx_msg void OnUpdateLinesize1px(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLinesize3px(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLinesize5px(CCmdUI* pCmdUI);
	afx_msg void OnLinestylePssolid();
	afx_msg void OnLinestylePsdash();
	afx_msg void OnUpdateLinestylePssolid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLinestylePsdash(CCmdUI* pCmdUI);
	afx_msg void OnModeCursur();
	afx_msg void OnModeDraw();
	afx_msg void OnUpdateIndicatorColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorStyle(CCmdUI* pCmdUI);
	afx_msg void OnSelectBmpFlower();
	afx_msg void OnSelectBmpNightsky();
	afx_msg void OnUpdateModeDraw(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectBmpFlower(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectBmpNightsky(CCmdUI* pCmdUI);
	virtual void DeleteContents();
	afx_msg void OnUpdateModePicture(CCmdUI* pCmdUI);
	afx_msg void OnInformationStatus();
};
