#pragma once



// CSelectView ���Դϴ�.

class CSelectView : public CScrollView
{
	DECLARE_DYNCREATE(CSelectView)

protected:
	CSelectView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CSelectView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.

	DECLARE_MESSAGE_MAP()
};


