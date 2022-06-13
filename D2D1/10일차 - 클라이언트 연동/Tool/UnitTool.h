#pragma once
#include "afxwin.h"

#include "Include.h"

// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();

	afx_msg void OnPushString();
	afx_msg void OnAdd_Charactor();
	afx_msg void OnListBox();
	afx_msg void OnDestroy();
	afx_msg void OnDeleteData();
	afx_msg void OnSearchData();

public:
	// value
	CString m_strTemp;
	CString m_strCopy;
	CString m_strName;
	CString m_strSearchData;

	int m_iHp;
	int m_iAttack;

	// control
	CListBox m_ListBox;
	CButton m_Radio[3];
	CButton m_Check[3];
	CButton m_Bitmap;

	// general
	map<CString, UNITDATA*>			m_MapUnitData;


	afx_msg void OnSaveData();
	afx_msg void OnLoadData();
};

// 저장, 불러오기, 삭제
// 검색 : 에디트 컨트롤로 문자열을 입력받으면 리스트 박스에 해당 셀이 선택되어지도록 만들어라