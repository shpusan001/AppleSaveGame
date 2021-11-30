#pragma once
#include <afxdockablepane.h>
#include "CSub.h"
class CSubPane :
	public CDockablePane
{

public:
	CSubPane();
	virtual ~CSubPane();
	CSub* m_Sub = new CSub;
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

