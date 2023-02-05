#pragma once


// ㄴㄴㄴ 대화 상자

class ㄴㄴㄴ : public CDialogEx
{
	DECLARE_DYNAMIC(ㄴㄴㄴ)

public:
	ㄴㄴㄴ(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ㄴㄴㄴ();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
