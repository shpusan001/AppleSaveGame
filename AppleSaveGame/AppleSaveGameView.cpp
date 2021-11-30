
// AppleSaveGameView.cpp: CAppleSaveGameView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AppleSaveGame.h"
#endif

#include "AppleSaveGameDoc.h"
#include "AppleSaveGameView.h"
#include <atlimage.h>
#include <stdlib.h>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#define MY_TIMER 100
#endif
#include "MainFrm.h"


// CAppleSaveGameView

IMPLEMENT_DYNCREATE(CAppleSaveGameView, CView)

BEGIN_MESSAGE_MAP(CAppleSaveGameView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CAppleSaveGameView 생성/소멸

CAppleSaveGameView::CAppleSaveGameView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CAppleSaveGameView::~CAppleSaveGameView()
{
}

BOOL CAppleSaveGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAppleSaveGameView 그리기

void CAppleSaveGameView::OnDraw(CDC* pDC)
{
	CAppleSaveGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


}


// CAppleSaveGameView 인쇄

BOOL CAppleSaveGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAppleSaveGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAppleSaveGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAppleSaveGameView 진단

#ifdef _DEBUG
void CAppleSaveGameView::AssertValid() const
{
	CView::AssertValid();
}

void CAppleSaveGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAppleSaveGameDoc* CAppleSaveGameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAppleSaveGameDoc)));
	return (CAppleSaveGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CAppleSaveGameView 메시지 처리기


void CAppleSaveGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == 0x41) {
		player->keyOnOff[0] = true;
	}
	if (nChar == 0x44) {
		player->keyOnOff[1] = true;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CAppleSaveGameView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == 0x41) {
		player->keyOnOff[0] = false;
	}
	if (nChar == 0x44) {
		player->keyOnOff[1] = false;
	}
	if (gamePage == _T("startPage")) {
		if (nChar == 0x53) {
			gamePage = _T("gamePage");
		}
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CAppleSaveGameView::playerSystem()
{
	// TODO: 여기에 구현 코드 추가.
	if (player->keyOnOff[0] == true) {
		player->x -= player->speed;

	}
	if (player->keyOnOff[1] == true) {
		player->x += player->speed;
	}
	
	if (player->x > stageX - player->width) {
		player->x = stageX - player->width;
	}
	else if (player->x < 0 - player->width/2) {
		player->x = 0- player->width/2;
	}

}


void CAppleSaveGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (gamePage == "startPage") {
		GameSystem();
	}
	if (gamePage == "gamePage") {
		playerSystem();
		stoneSystem();
		appleSystem();
		GameSystem();
		Invalidate();
	}

	if (CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd()) {
		pDlg = pFrame->m_paneSub.m_Sub;
	}
	CView::OnTimer(nIDEvent);
}


void CAppleSaveGameView::gameScreen()
{
	// TODO: 여기에 구현 코드 추가.
}


int CAppleSaveGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	srand(unsigned(time(NULL)));

	SetTimer(MY_TIMER, 1000 / 60, NULL);

	spritePlayer0.Load(L"./image/Player0.png");
	spritePlayer1.Load(L"./image/Player1.png");
	spriteStone.Load(L"./image/Stone.png");
	spriteApple.Load(L"./image/Apple.png");
	backGround.Load(L"./image/Background.jpeg");
	spriteStartPage.Load(L"./image/GameStartScreen.png");
	pDlg->dbConnect();
	return 0;
}


void CAppleSaveGameView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오
	if (gamePage == "startPage") {
		spriteStartPage.Draw(dc, 0, 0);
	}
	if (gamePage == "gamePage") {
		//배경그리기
		int fixX = 40;
		int fixY = 60;
		dc.MoveTo(0, 0);
		dc.LineTo(0, stageY+ fixY);
		dc.LineTo(stageX+ fixX, stageY + fixY);
		dc.LineTo(stageX+ fixX, 0);
		//점수 출력
		CString scoreText;
		scoreText.Format(_T("Score : %d"), score);
		TextOut(dc, 3, 0, scoreText , scoreText.GetLength());

		// 목숨 출력
		CString lifeText;
		CString life;
		for (int i = 0; i < playerLife; i++)life.Append(_T("@"));
		lifeText.Format(_T("Life :  %s"), life);
		TextOut(dc, 325, 0, lifeText, lifeText.GetLength());

		//레벨 출력
		CString levelText;
		levelText.Format(_T("Level : %d"), level);
		TextOut(dc, 3, 20, levelText, levelText.GetLength());

		//플레이어 출력
		static int unsigned playerAnimateClock;
		static int unsigned playerAnimateClockMax = 10;
		if (player->keyOnOff[0] == false && player->keyOnOff[1] == false) {
			spritePlayer0.Draw(dc, player->x, player->y);
		}
		else{
			if(playerAnimateClock< playerAnimateClockMax/2)
				spritePlayer0.Draw(dc, player->x, player->y);
			if(playerAnimateClock >= playerAnimateClockMax/2)
				spritePlayer1.Draw(dc, player->x, player->y);
			if (playerAnimateClock > playerAnimateClockMax)
				playerAnimateClock = 0;
		}
		playerAnimateClock++;

		//돌 출력
		LinkedList<stone>* tempStone = stoneList;
		while (tempStone->nextNode != NULL) {
			tempStone = tempStone->nextNode;
			int stoneX = tempStone->data->x;
			int stoneY = tempStone->data->y;
			spriteStone.Draw(dc, stoneX, stoneY);
		}
	
		//사과 출력
		LinkedList<apple>* tempApple = appleList;
		while (tempApple->nextNode != NULL) {
			tempApple = tempApple->nextNode;
			int appleX = tempApple->data->x;
			int appleY = tempApple->data->y;
			spriteApple.Draw(dc, appleX, appleY);
		}
	}
}


void CAppleSaveGameView::stoneSystem()
{
	// TODO: 여기에 구현 코드 추가.

	//돌 리스트 헤드 받기
	LinkedList<stone>* temp = stoneList;
	//돌생성
	static bool oneTime;
	static int stoneClock;
	static int stoneClockMax;
	stoneClockMax = stoneClockMax > 2 ? (12 - level/3) : 2;
	if (!oneTime) { stoneClockMax = 12; oneTime = true; }
	if (stoneClock > stoneClockMax) {
		int randomX = rand() % stageX;
		stone* tempStone;
		stoneList->createNode()->data = new stone();
		while (temp->nextNode != NULL)temp = temp->nextNode;
		temp->data->x = randomX;
		temp->data->y = 0;
		stoneClock = 0;
	}
	stoneClock++;

	//돌 컨트롤 
	temp = stoneList;
	while (temp->nextNode != NULL) { 
		temp = temp->nextNode; 
		temp->data->y += (stoneSpeed + level/3);
	}

	temp = stoneList;
	while (temp->nextNode != NULL) {
		temp = temp->nextNode;
		LinkedList<stone>* tempBuf = temp->nextNode;
		if (temp->data->y > stageY) {
			temp->removeNode();
			temp = tempBuf;
		}
		if (temp->data->x > player->x - player->width && temp->data->x < player->x + player->width
			&& temp->data->y + temp->data->width > player->y) {
			playerLife--;
			Beep(960, 60);
			temp->removeNode();
			temp = tempBuf;
		}
	}
}


void CAppleSaveGameView::appleSystem()
{
	// TODO: 여기에 구현 코드 추가.
	//사과 리스트 헤드 받기
	LinkedList<apple>* temp = appleList;
	//사과생성
	static int appleClock;
	static int appleClockMax = 12;
	if (appleClock > appleClockMax) {
		int randomX = rand() % stageX;
		appleList->createNode()->data = new apple();
		while (temp->nextNode != NULL)temp = temp->nextNode;
		temp->data->x = randomX;
		temp->data->y = 0;
		appleClock = 0;
	}
	appleClock++;

	//사과 컨트롤 
	temp = appleList;
	while (temp->nextNode != NULL) {
		temp = temp->nextNode;
		temp->data->y += stoneSpeed;
	}

	temp = appleList;
	while (temp->nextNode != NULL) {
		temp = temp->nextNode;
		LinkedList<apple>* tempBuf = temp->nextNode;
		if (temp->data->y > stageY) {
			temp->removeNode();
			temp = tempBuf;
		}
		if (temp->data->x > player->x - player->width && temp->data->x < player->x + player->width
			&& temp->data->y + temp->data->width > player->y) {
			score++;
			Beep(360, 70);
			temp->removeNode();
			temp = tempBuf;
		}
	}
}


void CAppleSaveGameView::GameSystem()
{
	// TODO: 여기에 구현 코드 추가.
	if (gamePage == _T("startPage")) {
		player->keyOnOff[0] = false;
		player->keyOnOff[1] = false;
	}

	if (playerLife <= 0) {
		CString gameEndMessage;
		gameEndMessage.Format(_T("당신의 점수는 %d점입니다\n다시할래요?"), score);
		gamePage = "endPage";
		pDlg->inputData(score);
		pDlg->rankToken = true;
		if (AfxMessageBox(gameEndMessage, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			gamePage = "startPage";
			playerLife = 3;
			score = 0;
			level = 0;
		}
		else
		{
			if (AfxMessageBox(_T("종료하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				exit(0);
			}
			else
			{
				gamePage = "startPage";
				playerLife = 3;
				score = 0;
				level = 0;
			}
		}
	}
	if (gamePage == "gamePage") {
		static int gameTimeCount;
		gameTimeCount++;
		if (gameTimeCount > (1000 / 60 * 20)) {
			if(level < 30)level++;
			gameTimeCount = 0;
		}
	}
}
