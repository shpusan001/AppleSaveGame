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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	if (!m_Sub->Create(IDD_DIALOG_SUB, this))
	{
		TRACE0("�޴� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_Sub->ShowWindow(SW_SHOW);
	return 0;
}


void CSubPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_Sub->MoveWindow(0, 0, cx, cy);
	m_Sub->SetFocus();
}
