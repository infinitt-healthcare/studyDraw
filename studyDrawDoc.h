
// studyDrawDoc.h: CstudyDrawDoc 클래스의 인터페이스
//


#pragma once
#include <vector>
using namespace std;

class DrawShape {
public:
	virtual void draw(CDC* dc) const = 0;

};

class DrawLine : public DrawShape
{
public:
	LOGPEN m_logPen1;
	vector<CPoint> m_arrayLine;

	DrawLine() 
	{
		m_arrayLine.clear();
	}

	void m_logPen(LOGPEN& _m_logPen)
	{
		m_logPen1 = _m_logPen;
	}

	virtual void draw(CDC* dc) const override
	{
		dc->MoveTo(m_arrayLine[0]);
		CPen pen(m_logPen1.lopnStyle, m_logPen1.lopnWidth.x, m_logPen1.lopnColor);
		CPen* pOldPen = dc->SelectObject(&pen);
		for (const CPoint& pt : m_arrayLine)
		{
			dc->LineTo(pt);
		}
		dc->SelectObject(pOldPen);
	}
};

class DrawBmp : public DrawShape
{
public:
	LPCWSTR m_lpcwstrBmpId;
	CRect rect;

	bool isClicked = false;

	DrawBmp() { }

	void rect_TopLeft(CPoint m_pt)
	{
		rect.left = m_pt.x;
		rect.top = m_pt.y;
	}

	void rect_BottomRight(CPoint m_pt) 
	{
		rect.right = m_pt.x;
		rect.bottom = m_pt.y;
	}

	void m_bmpId(LPCWSTR _m_lpcwstrFileName)
	{
		m_lpcwstrBmpId = _m_lpcwstrFileName;
	}

	virtual void draw(CDC* dc) const override
	{
		CDC MemDC;
		BITMAP bmpInfo;
		MemDC.CreateCompatibleDC(dc);

		CBitmap bmp;
		CBitmap* pOldBmp = NULL;
		bmp.LoadBitmap(m_lpcwstrBmpId);

		bmp.GetBitmap(&bmpInfo);
		pOldBmp = MemDC.SelectObject(&bmp);
		dc->StretchBlt(rect.left, rect.top,	
			rect.right- rect.left, rect.bottom - rect.top,
			&MemDC,
			0, 0,
			bmpInfo.bmWidth, bmpInfo.bmHeight,
			SRCCOPY);
		MemDC.SelectObject(pOldBmp);
		MemDC.DeleteDC();
	}
};

class DrawRect : public DrawShape
{
public:
	LOGPEN m_logPen2;
	CRect rect;

	DrawRect() { }

	void m_logPen(LOGPEN _m_logPen)
	{
		m_logPen2 = _m_logPen;
	}

	void rect_TopLeft(CPoint m_pt)
	{
		rect.left = m_pt.x;
		rect.top = m_pt.y;
	}

	void rect_BottomRight(CPoint m_pt)
	{
		rect.right = m_pt.x;
		rect.bottom = m_pt.y;
	}
	
	virtual void draw(CDC* dc) const override
	{
		
		CPen pen(m_logPen2.lopnStyle, m_logPen2.lopnWidth.x, m_logPen2.lopnColor);
		CPen* pOldPen;
		pOldPen = dc->SelectObject(&pen); 
		dc->Rectangle(rect); 
		dc->SelectObject(pOldPen);
	}
	
};

class CstudyDrawDoc : public CDocument
{
protected: // serialization에서만 만들어집니다. 
	CstudyDrawDoc() noexcept;
	DECLARE_DYNCREATE(CstudyDrawDoc)

// 특성입니다.
public:

	DrawShape* m_pDrawShape;
	vector<DrawShape*> m_arrayShape;

	LOGPEN m_logPen;
	LPCWSTR m_lpcwstrBmpId;

	int m_nMouse_Mode;
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
