
// studyDrawView.h: CstudyDrawView 클래스의 인터페이스
//

#pragma once


class CstudyDrawView : public CView
{
protected: // serialization에서만 만들어집니다.
	CstudyDrawView() noexcept;
	DECLARE_DYNCREATE(CstudyDrawView)

// 특성입니다.
public:
	CstudyDrawDoc* GetDocument() const;
	DrawBmp* m_pDrawBmp;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CstudyDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnModePicture();
	afx_msg void OnModeRectangle();
};

#ifndef _DEBUG  // studyDrawView.cpp의 디버그 버전
inline CstudyDrawDoc* CstudyDrawView::GetDocument() const
   { return reinterpret_cast<CstudyDrawDoc*>(m_pDocument); }
#endif

