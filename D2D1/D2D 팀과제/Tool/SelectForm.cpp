// SelectForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "SelectForm.h"
#include "FileInfo.h"


// SelectForm

IMPLEMENT_DYNCREATE(CSelectForm, CFormView)

CSelectForm::CSelectForm()
	: CFormView(IDD_SELECTFORM)
{

}

CSelectForm::~CSelectForm()
{
}

void CSelectForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_IamgeIcon[0]);
	DDX_Control(pDX, IDC_PIC2, m_IamgeIcon[1]);
	DDX_Control(pDX, IDC_PIC3, m_IamgeIcon[2]);
	DDX_Control(pDX, IDC_PIC4, m_IamgeIcon[3]);
	DDX_Control(pDX, IDC_PIC5, m_IamgeIcon[4]);
	DDX_Control(pDX, IDC_PIC6, m_IamgeIcon[5]);
	DDX_Control(pDX, IDC_BUTTON1, m_Test);
}

BEGIN_MESSAGE_MAP(CSelectForm, CFormView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// SelectForm �����Դϴ�.

#ifdef _DEBUG
void CSelectForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SelectForm �޽��� ó�����Դϴ�.


void CSelectForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	// ����� ���̴� ���� 520byte�� �Ѿ �� �ȴ�.
	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MAX_STR] = L"";


	for (int i = 1; i <= 144; ++i)
	{
		swprintf_s(szFilePath, L"../Texture/Stage/Terrain/Tile/Tile-%03d.png", i);

		// CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);

		//PathFindFileName : ��� �� ���� �̸��� ����� ��� �����ϴ� �Լ�
		CString	strFileName = PathFindFileName(szFilePath);

		lstrcpy(szFileName, strFileName.GetString());

		// ������ Ȯ���� ���� �����ϴ� �Լ�
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(szFilePath);	// �ش� ����� �̹��� �ε�

			m_MapPngImg.insert({ strFileName, pPngImg });

		}

	}


	UpdateData(TRUE);

	auto& iter = m_MapPngImg.begin();

	for (int i = 0; i < 6; ++i)
	{
		m_IamgeIcon[i].SetBitmap(*(iter->second));
		++iter;
	}

	HCURSOR tep;
	tep = m_IamgeIcon[0].GetCursor();

	if (tep == nullptr)
		return;

	UpdateData(FALSE);
}


void CSelectForm::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (m_Test.GetState() == BST_FOCUS)
	{
		return;
	}

	CFormView::OnLButtonDown(nFlags, point);
}
