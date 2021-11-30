#pragma once
#include <string>


// CSub 대화 상자

class CSub : public CDialogEx
{
	DECLARE_DYNAMIC(CSub)

public:
	CSub(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSub();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SUB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_recentScore;
	void inputData(int score);
	bool dbConnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnClose();
	CListBox m_listRanking;
//	CEdit m_editName;
	CString m_editName;
	bool rankToken = false;
	CString path = L"./save/score.txt";
};
