
// C++Project Snake GameDlg.h: 헤더 파일
//

#pragma once


// CCProjectSnakeGameDlg 대화 상자
class CCProjectSnakeGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CCProjectSnakeGameDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPROJECTSNAKEGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);//Timer function declaration to perform different actions on keyboard input.


public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);//Function to handle keyboard input.
	int BodyHit(); // Function to check if head hit  body.
	void FoodHit(int xPre, int yPre);//Function to check if head hit food.
	void FoodPositionChange();//function that redefines the location of food through random functions.


};
