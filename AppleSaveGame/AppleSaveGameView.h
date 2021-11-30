
// AppleSaveGameView.h: CAppleSaveGameView 클래스의 인터페이스
//

#pragma once
#include "Player.h"
#include "LinkedList.h"
#include "stone.h"
#include "apple.h"
#include "AppleSaveGameDoc.h"
#include "CSub.h"


class CAppleSaveGameView : public CView
{
protected: // serialization에서만 만들어집니다.
	CAppleSaveGameView() noexcept;
	DECLARE_DYNCREATE(CAppleSaveGameView)

// 특성입니다.
public:
	CAppleSaveGameDoc* GetDocument() const;

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
	virtual ~CAppleSaveGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	Player* player = new Player;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	void playerSystem();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void gameScreen();

	CImage spritePlayer0; CImage spritePlayer1;
	CImage spriteApple; CImage spriteStone;
	CImage backGround; CImage spriteStartPage;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	void stoneSystem();
	LinkedList<stone>* stoneList = new LinkedList<stone>(true);
	LinkedList<apple>* appleList = new LinkedList<apple>(true);
	int stageX = 400;
	int stageY = 500;
	int stoneSpeed=8;
	void appleSystem();
	int score = 0;
	int playerLife =3;
	void GameSystem();
	CString gamePage = _T("startPage");
	CSub* pDlg;	
	bool musicOnoff = true;
	int level = 1;
};

#ifndef _DEBUG  // AppleSaveGameView.cpp의 디버그 버전
inline CAppleSaveGameDoc* CAppleSaveGameView::GetDocument() const
   { return reinterpret_cast<CAppleSaveGameDoc*>(m_pDocument); }
#endif

