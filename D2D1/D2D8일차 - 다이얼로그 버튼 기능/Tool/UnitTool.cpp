// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strTemp(_T(""))
	, m_strCopy(_T(""))
	, m_strName(_T(""))
	, m_iHp(0)
	, m_iAttack(0)
{

}

CUnitTool::~CUnitTool()
{
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	// DoDataExchange : UpdateData�Լ��� ȣ���� ������ �ڵ�ȣ��Ǵ� �Լ�


	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_strTemp);
	DDX_Text(pDX, IDC_EDIT2, m_strCopy);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iHp);
	DDX_Text(pDX, IDC_EDIT5, m_iAttack);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);

	DDX_Control(pDX, IDC_CHECK1, m_Check[0]);
	DDX_Control(pDX, IDC_CHECK2, m_Check[1]);
	DDX_Control(pDX, IDC_CHECK3, m_Check[2]);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnPushString)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnAdd_Charactor)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnListBox)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnPushString()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);  // ���̾�α� �ڽ��κ��� �Է��� ������ ����
		
	m_strCopy = m_strTemp;

	UpdateData(FALSE);  // ������ ����� ������ ���̾�α� �ڽ��� �ݿ�

}


void CUnitTool::OnAdd_Charactor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	UNITDATA*		pUnit = new UNITDATA;

	pUnit->strName = m_strName;
	pUnit->iAttack = m_iAttack;
	pUnit->iHp = m_iHp;

	for (int i = 0; i < 3; ++i)
	{
		// GetCheck : ���� ���� ��ư�� üũ�Ǿ��ִ��� ���� �Ǵ�
		if (m_Radio[i].GetCheck())
		{
			pUnit->byJobIndex = i;
			break;
		}
	}



	// AddString : ����Ʈ �ڽ��� ���ڿ��� �߰� ��
	m_ListBox.AddString(pUnit->strName);

	m_MapUnitData.insert({pUnit->strName, pUnit});

	UpdateData(FALSE);
}


void CUnitTool::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString		strFindName;

	// GetCurSel : ���� ����Ʈ �ڽ����� ���õ� ���� �ε��� ���� ��ȯ
	int iSelect = m_ListBox.GetCurSel();

	// GetText : ���� �ε����� �ش��ϴ� ���ڿ��� ����Ʈ �ڽ��κ��� ����
	m_ListBox.GetText(iSelect, strFindName);

	auto	iter = m_MapUnitData.find(strFindName);

	if (iter == m_MapUnitData.end())
		return;

	m_strName = iter->second->strName;
	m_iAttack = iter->second->iAttack;
	m_iHp = iter->second->iHp;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE);	// ��� ���� ��ư üũ ����

	m_Radio[iter->second->byJobIndex].SetCheck(TRUE);

	UpdateData(FALSE);
}


void CUnitTool::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	for_each(m_MapUnitData.begin(), m_MapUnitData.end(), CDeleteMap());
	m_MapUnitData.clear();

}


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_Radio[0].SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
