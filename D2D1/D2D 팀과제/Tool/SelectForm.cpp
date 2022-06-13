// SelectForm.cpp : 구현 파일입니다.
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


// SelectForm 진단입니다.

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


// SelectForm 메시지 처리기입니다.


void CSelectForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	// 경로의 길이는 절대 520byte를 넘어선 안 된다.
	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MAX_STR] = L"";


	for (int i = 1; i <= 144; ++i)
	{
		swprintf_s(szFilePath, L"../Texture/Stage/Terrain/Tile/Tile-%03d.png", i);

		// CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);

		//PathFindFileName : 경로 중 파일 이름만 남기고 모두 제거하는 함수
		CString	strFileName = PathFindFileName(szFilePath);

		lstrcpy(szFileName, strFileName.GetString());

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(szFilePath);	// 해당 경로의 이미지 로드

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_Test.GetState() == BST_FOCUS)
	{
		return;
	}

	CFormView::OnLButtonDown(nFlags, point);
}
