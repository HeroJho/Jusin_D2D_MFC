#pragma once
#include "afxwin.h"



// SelectForm 폼 뷰입니다.

class CSelectForm : public CFormView
{
	DECLARE_DYNCREATE(CSelectForm)

protected:
	CSelectForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CSelectForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_IamgeIcon[6];

	//CImage : jpeg, gif, bmp, png 형식을 지원하는 클래스
	map<CString, CImage*>		m_MapPngImg;
	virtual void OnInitialUpdate();
	CButton m_Test;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


