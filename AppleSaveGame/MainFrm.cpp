
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "AppleSaveGame.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "AppleSaveGameView.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_NEWGAME, &CMainFrame::OnNewgame)
	ON_COMMAND(ID_SOUND, &CMainFrame::OnSound)
	ON_COMMAND(ID_END, &CMainFrame::OnEnd)
	ON_COMMAND(ID_HOW, &CMainFrame::OnHow)
	ON_COMMAND(ID_KEY, &CMainFrame::OnKey)
	ON_COMMAND(ID_TOOL_NEW, &CMainFrame::OnToolNew)
	ON_COMMAND(ID_TOOL_MUSIC, &CMainFrame::OnToolMusic)
	ON_COMMAND(ID_TOOL_END, &CMainFrame::OnToolEnd)
	ON_COMMAND(ID_TOOL_HOW, &CMainFrame::OnToolHow)
	ON_COMMAND(ID_TOOL_KEY, &CMainFrame::OnToolKey)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//*******************************************
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndToolBar);
	//*****************************************
	if (!m_paneSub.Create(_T("역대 점수"), this, CRect(0, 0, 300, 300), TRUE, 0Xfafa,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT
		| CBRS_FLOAT_MULTI)) {
		TRACE0("도킹팬을 만들지 못했습니다.\n");
		return -1;
	}
	m_paneSub.SetMinSize(500);
	m_paneSub.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_paneSub);
	

	//this->GetActiveView().pdlg  = m_paneSub.m_Sub;
	SetTimer(2000, 1000, NULL);
	//*****************************************
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CAppleSaveGameView* pView = (CAppleSaveGameView*)this->GetActiveView();
	PlaySound(L"./sound/music.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP); 
	KillTimer(2000);
	CFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::OnNewgame()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAppleSaveGameView* pView = (CAppleSaveGameView*)this->GetActiveView();
	pView->gamePage = _T("startPage");
	pView->score = 0;
	pView->playerLife = 3;
	pView->level = 0;
	Invalidate();
}


void CMainFrame::OnSound()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAppleSaveGameView* pView = (CAppleSaveGameView*)this->GetActiveView();
	if (pView->musicOnoff == false) {
		pView->musicOnoff = true;
		PlaySound(L"./sound/music.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP); //루프 재생
	}
	else {
		pView->musicOnoff = false;
		PlaySound(NULL, 0, 0);
	}
}


void CMainFrame::OnEnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	exit(0);
}


void CMainFrame::OnHow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(L"떨어지는 돌을 피하고 사과를 받으세요!");
}


void CMainFrame::OnKey()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(L"<키보드 키>\na:왼쪽으로 움직이기\nd:오른쪽으로 움직이기\ns:시작하기");
}


void CMainFrame::OnToolNew()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnNewgame();
}


void CMainFrame::OnToolMusic()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnSound();
}


void CMainFrame::OnToolEnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnEnd();
}


void CMainFrame::OnToolHow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnHow();
}


void CMainFrame::OnToolKey()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnKey();
}
