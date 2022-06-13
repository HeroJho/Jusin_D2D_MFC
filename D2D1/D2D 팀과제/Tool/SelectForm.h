#pragma once
#include "afxwin.h"



// SelectForm �� ���Դϴ�.

class CSelectForm : public CFormView
{
	DECLARE_DYNCREATE(CSelectForm)

protected:
	CSelectForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_IamgeIcon[6];

	//CImage : jpeg, gif, bmp, png ������ �����ϴ� Ŭ����
	map<CString, CImage*>		m_MapPngImg;
	virtual void OnInitialUpdate();
	CButton m_Test;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


