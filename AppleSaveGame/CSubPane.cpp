#include "pch.h"
#include "CSubPane.h"
#include "resource.h"
#include "AppleSaveGameView.h"
#include "MainFrm.h"
BEGIN_MESSAGE_MAP(CSubPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


CSubPane::CSubPane()
{

}

CSubPane::~CSubPane()
{
}

int CSubPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	if (!m_Sub->Create(IDD_DIALOG_SUB, this))
	{
		TRACE0("메뉴 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_Sub->ShowWindow(SW_SHOW);
	return 0;
}


void CSubPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_Sub->MoveWindow(0, 0, cx, cy);
	m_Sub->SetFocus();
}
