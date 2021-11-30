// CSub.cpp: 구현 파일
//

#include "pch.h"
#include "AppleSaveGame.h"
#include "CSub.h"
#include "afxdialogex.h"
#include "AppleSaveGameView.h"
#include "MainFrm.h"



// CSub 대화 상자

IMPLEMENT_DYNAMIC(CSub, CDialogEx)

CSub::CSub(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SUB, pParent)
	, m_recentScore(0)
	, m_editName(_T(""))
{

}

CSub::~CSub()
{
}

void CSub::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_recentScore);
	DDX_Control(pDX, IDC_LIST_RANKING, m_listRanking);
	//  DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_NAME, m_editName);
}


BEGIN_MESSAGE_MAP(CSub, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSub::OnBnClickedButtonSend)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSub 메시지 처리기


BOOL CSub::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(TRUE);
	m_editName = L"player";
	UpdateData(FALSE);

	FILE* fp;
	char file_buff[1000];

	fp = fopen("./save/scores.txt", "r");

	while (fscanf(fp, "%s\n", file_buff) != EOF) 
	{
		char* ps = file_buff;
		CString str;
		int len = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, ps, -1, NULL, NULL);
		str = new TCHAR[len];
		MultiByteToWideChar(CP_ACP, 0, ps, -1, (LPWSTR)(LPCWSTR)str, len);
		//AfxMessageBox(str);
		m_listRanking.AddString(str);
	}

	fclose(fp);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSub::inputData(int score)
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(TRUE);
	m_recentScore = score;
	UpdateData(FALSE);
}


bool CSub::dbConnect()
{
	// TODO: 여기에 구현 코드 추가.
	return false;
}


void CSub::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (rankToken == true) {
		CString inputRank;
		inputRank.Format(_T("점수:%d#이름:%s\n"), m_recentScore, m_editName);
		m_listRanking.AddString(inputRank);
		rankToken = false;
		if (m_listRanking.GetCount() > 20) {
			m_listRanking.DeleteString(0);
		}
	}
	else {
		AfxMessageBox(_T("이미 등록되었습니다.\n게임을 플레이하면 다시 등록할 수 있습니다."));
	}
	
	FILE* fp;
	fp = fopen("./save/scores.txt", "w");
	
	for (int i = 0; i < m_listRanking.GetCount(); i++) {
		CString temp;
		m_listRanking.GetText(i, temp);
		temp.Format(_T("%s\n"), temp);
		CString tmpcstr = _T("testing");
		char* tmpch;

		int sLen = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
		tmpch = new char[sLen + 1];
		WideCharToMultiByte(CP_ACP, 0, temp, -1, tmpch, sLen, NULL, NULL);

		//사용 후, 마지막에 동적할당 된 메모리를 제거해야 합니다.
		fprintf(fp, tmpch);
		delete[]tmpch;
	}

	fclose(fp);
	/*
	for (int i = 0; i < m_listRanking.GetCount(); i++) {
		CString tmp1, tmp2;
		tmp1 = L""; tmp2 = L"";
		for (int j = 1+i; j < m_listRanking.GetCount(); j++) {
			m_listRanking.GetText(i, tmp1);
			m_listRanking.GetText(j, tmp2);
			if (tmp2 > tmp1) {
				m_listRanking.DeleteString(i);
				m_listRanking.DeleteString(j);
				m_listRanking.InsertString(i, tmp2);
				m_listRanking.InsertString(j, tmp1);	
			}
		}
	}*/

	UpdateData(FALSE);
}


void CSub::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}
