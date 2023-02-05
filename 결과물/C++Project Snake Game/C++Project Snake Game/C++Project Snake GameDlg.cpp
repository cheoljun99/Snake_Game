
// C++Project Snake GameDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "C++Project Snake Game.h"
#include "C++Project Snake GameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
Linkedlist A;//Linked list class declares variable A as a global variable for convenience.
int xrand = rand()% (MapHorizontalityMax - 2) + 1;//Declare a variable to store the feed location as a global variable for convenience. Also, initialize it with rand () function.
int yrand = rand()% (MapVerticalityMax - 2) + 1;//Declare a variable to store the feed location as a global variable for convenience. Also, initialize it with rand () function.
char KeyBoardCheck = 'A';//Declare the variable to store the motion as a global variable for convenience, and store A as the initial motion is left.
int FoodEatCount = 0;//Declare a variable to store the number of times you eat the feed as a global variable for convenience.
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCProjectSnakeGameDlg 대화 상자



CCProjectSnakeGameDlg::CCProjectSnakeGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CPROJECTSNAKEGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCProjectSnakeGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCProjectSnakeGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CCProjectSnakeGameDlg 메시지 처리기

BOOL CCProjectSnakeGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	if (MessageBox(L"이 게임은 뱀에 대하 잔혹한 묘사가 포함되어 있습니다.\n무서운 것에 서투른 분은 플레이를 삼가해 주십시오.\n게임 진행을 원하십니까?", L"경고문", MB_YESNO) == IDNO)
		this->DestroyWindow();
	else
		MoveWindow(0, 0, 560, 590);
	// TODO: 여기에 추가 초기화 작업을 추가합니다.



	SetTimer(2, SnakeSpeed, nullptr); //2:timer id, 55: period(ms)

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCProjectSnakeGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCProjectSnakeGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		CPaintDC dc(this);
		
		// Double buffering: DC and BITMAP generation for double buffering
		CDC mDC;
		CBitmap mBitmap;
		CRect rect;// Object to store the full window size information
		GetClientRect(&rect);

		// Double buffering: Define and set the current dc in MDC and bitmap
		mDC.CreateCompatibleDC(&dc);
		mBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		mDC.SelectObject(&mBitmap);
		mDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);



		for (int i = 0; i < MapVerticalityMax; i++)//Drawing Process 25x25 Movable Map and Wall.
		{
			for (int j = 0; j < MapHorizontalityMax; j++)
			{

				if (i == 0)//wall
				{
					CBrush brush(RGB(0, 0, 0));
					CBrush* pOldBrush = mDC.SelectObject(&brush);
					mDC.Rectangle(j * 20, i * 20, j * 20 + 20, i * 20 + 20);
					mDC.SelectObject(pOldBrush);
				}
				else if (i == (MapVerticalityMax-1))//wall
				{
					CBrush brush(RGB(0, 0, 0));
					CBrush* pOldBrush = mDC.SelectObject(&brush);
					mDC.Rectangle(j * 20, i * 20, j * 20 + 20, i * 20 + 20);
					mDC.SelectObject(pOldBrush);
				}
				else if (j == MapHorizontalityMax-1)//wall
				{
					CBrush brush(RGB(0, 0, 0));
					CBrush* pOldBrush = mDC.SelectObject(&brush);
					mDC.Rectangle(j * 20, i * 20, j * 20 + 20, i * 20 + 20);
					mDC.SelectObject(pOldBrush);
				}
				else if (j == 0)//wall
				{
					CBrush brush(RGB(0, 0, 0));
					CBrush* pOldBrush = mDC.SelectObject(&brush);
					mDC.Rectangle(j * 20, i * 20, j * 20 + 20, i * 20 + 20);
					mDC.SelectObject(pOldBrush);
				}
				else//Movable Map
				{
					CBrush brush(RGB(93, 93, 93));
					CBrush* pOldBrush = mDC.SelectObject(&brush);
					mDC.Rectangle(j * 20, i * 20, j * 20 + 20, i * 20 + 20);
					mDC.SelectObject(pOldBrush);

				}
				
			}
		}
		if (FoodEatCount == (MapVerticalityMax - 2) * (MapHorizontalityMax - 2) - 3)//The process of drawing food
		{
			CBrush brush(RGB(93, 93, 93));
			CBrush* pOldBrush = mDC.SelectObject(&brush);
			mDC.Rectangle(xrand * 20, yrand * 20, xrand * 20 + 20, yrand * 20 + 20);
			mDC.SelectObject(pOldBrush);
		}
		else//The process of drawing food
		{
			CBrush brush_snake_food(RGB(255, 0, 0));
			mDC.SelectObject(brush_snake_food);
			mDC.Rectangle(xrand * 20, yrand * 20, xrand * 20 + 20, yrand * 20 + 20);

		}
		


		Snake * temp = A.Head;
		while (temp != NULL)//The process of drawing a snake
		{
			if (temp == A.Head)//Head
			{
				CBrush brush_snake_head(RGB(0, 255, 0));
				mDC.SelectObject(brush_snake_head);
				mDC.Ellipse((temp->x) * 20, (temp->y) * 20, (temp->x) * 20 + 20, (temp->y) * 20 + 20);

			}
			else if (temp->next == NULL)//Tail
			{
				CBrush brush_snake_tail(RGB(0, 216, 255));
				mDC.SelectObject(brush_snake_tail);
				mDC.Ellipse((temp->x) * 20, (temp->y) * 20, (temp->x) * 20 + 20, (temp->y) * 20 + 20);

			}
			else//Body
			{
				CBrush brush_snake_body(RGB(255, 255, 0));
				mDC.SelectObject(brush_snake_body);
				mDC.Rectangle((temp->x) * 20, (temp->y) * 20, (temp->x) * 20 + 20, (temp->y) * 20 + 20);
			}
			temp = temp->next;
		}
		
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &mDC, 0, 0, SRCCOPY);

	

		



	}
	

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCProjectSnakeGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCProjectSnakeGameDlg::OnTimer(UINT_PTR nIDEvent)//When the timer runs
{
	int BlockCheck = 0;//Variable declared to see if it hit the wall
	int BodyCheck = 0;//Variable declared to see if it hit  Body
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
		
		case 1: // When I enter W
		{
			/*The process of moving a snake*/
			Snake* temp = A.Head;
			int xPre=0;
			int yPre = 0;
			if ((temp->y) - 1 == yrand && temp->x == xrand)//When Snake's head hit food
			{
				xPre = temp->x;
				yPre = temp->y;
				temp->y = (temp->y) - 1;
				FoodHit(xPre, yPre);//Function to increase body by one when hit with food
				KeyBoardCheck = 'W';//Save current direction of movement

			}

			else
			{
				while (temp != NULL)//The process of moving a snake by one
				{

					if (temp == A.Head)//Confirm that the snake's head is hitting the body and hitting the wall.
					{
						xPre = temp->x;
						yPre = temp->y;
						temp->y = (temp->y) - 1;
						if (temp->y == 0)//When the head hits the wall
						{
							BlockCheck++;//Exit the case statement, incrementing the variable declared to see if the head hit the wall.
							break;
						}
						else if (BodyHit() == 1)//When a snake hits into his body
						{
							BodyCheck++;//Exit the case statement while incrementing the declared variable to see if the head hit the body.
							break;

						}
						Invalidate(FALSE);//Update the state while executing the Onpaint function.
					}
					else
					{
						int xtemp = temp->x;
						int ytemp = temp->y;
						temp->x = xPre;
						temp->y = yPre;
						xPre = xtemp;
						yPre = ytemp;

					}
					temp = temp->next;

				}

			}
			KeyBoardCheck = 'W';//Save current direction of movement

		}
		break;


		case 2: // When I enter A
		{
			/*The process of moving a snake*/
			//The process is the same as in the case above
			Snake* temp = A.Head;
			int xPre = 0;
			int yPre = 0;
			if ((temp->x) - 1 == xrand && temp->y == yrand)//When Snake's head hit food
			{
				xPre = temp->x;
				yPre = temp->y;
				temp->x = (temp->x) - 1;
				FoodHit(xPre, yPre);//Function to increase body by one when hit with food
				KeyBoardCheck = 'A';//Save current direction of movement

			}
			else
			{
				while (temp != NULL)//The process of moving a snake by one
				{

					if (temp == A.Head)//Confirm that the snake's head is hitting the body and hitting the wall.
					{
						xPre = temp->x;
						yPre = temp->y;
						temp->x = (temp->x) - 1;
						if (temp->x == 0)//When the head hits the wall
						{
							BlockCheck++;//Exit the case statement, incrementing the variable declared to see if the head hit the wall.
							break;
						}
						else if (BodyHit() == 1)//When a snake hits into his body
						{
							BodyCheck++;//Exit the case statement while incrementing the declared variable to see if the head hit the body.
							break;
						}
						Invalidate(FALSE);//Update the state while executing the Onpaint function.
					}
					else
					{
						int xtemp = temp->x;
						int ytemp = temp->y;
						temp->x = xPre;
						temp->y = yPre;
						xPre = xtemp;
						yPre = ytemp;
					}



					temp = temp->next;

				}
			}
			KeyBoardCheck = 'A';//Save current direction of movement
				
		}
		break;


		case 3: // When I enter D
		{
			/*The process of moving a snake*/
			//The process is the same as in the case above
			Snake* temp = A.Head;
			int xPre = 0;
			int yPre = 0;
			if ((temp->x) + 1 == xrand && temp->y == yrand)//When Snake's head hit food
			{
				xPre = temp->x;
				yPre = temp->y;
				temp->x = (temp->x) + 1;
				FoodHit(xPre, yPre);//Function to increase body by one when hit with food
				KeyBoardCheck = 'D';//Save current direction of movement
			}
			else
			{
				while (temp != NULL)//The process of moving a snake by one
				{

					if (temp == A.Head)//Confirm that the snake's head is hitting the body and hitting the wall.
					{

						xPre = temp->x;
						yPre = temp->y;
						temp->x = (temp->x) + 1;
						if (temp->x == (MapVerticalityMax-1))//When the head hits the wall
						{
							BlockCheck++;//Exit the case statement, incrementing the variable declared to see if the head hit the wall.
							break;
						}
						else if (BodyHit() == 1)//When a snake hits into his body
						{
							BodyCheck++;//Exit the case statement while incrementing the declared variable to see if the head hit the body.
							break;
						}
						Invalidate(FALSE);//Update the state while executing the Onpaint function.

					}
					else
					{
						int xtemp = temp->x;
						int ytemp = temp->y;
						temp->x = xPre;
						temp->y = yPre;
						xPre = xtemp;
						yPre = ytemp;
					}

					temp = temp->next;

				}

			}
			KeyBoardCheck = 'D';//Save current direction of movement


		}	
		break;

		case 4:  // When I enter S
		{
			/*The process of moving a snake*/
			//The process is the same as in the case above
			Snake* temp = A.Head;
			int xPre = 0;
			int yPre = 0;
			if ((temp->y) + 1 == yrand && temp->x == xrand)//When Snake's head hit food
			{
				xPre = temp->x;
				yPre = temp->y;
				temp->y = (temp->y) + 1;
				FoodHit(xPre, yPre);//Function to increase body by one when hit with food
				KeyBoardCheck = 'S';//Save current direction of movement
			}
			else
			{
				while (temp != NULL)//The process of moving a snake by one
				{

					if (temp == A.Head)//Confirm that the snake's head is hitting the body and hitting the wall.
					{
						xPre = temp->x;
						yPre = temp->y;
						temp->y = (temp->y) + 1;
						if (temp->y == (MapHorizontalityMax-1))//When the head hits the wall
						{
							BlockCheck++;//Exit the case statement, incrementing the variable declared to see if the head hit the wall.
							break;
						}
						else if (BodyHit() == 1)//When a snake hits into his body
						{
							BodyCheck++;//Exit the case statement while incrementing the declared variable to see if the head hit the body.
							break;
						}
						Invalidate(FALSE);//Update the state while executing the Onpaint function.
					}
					else
					{
						int xtemp = temp->x;
						int ytemp = temp->y;
						temp->x = xPre;
						temp->y = yPre;
						xPre = xtemp;
						yPre = ytemp;

					}
					temp = temp->next;

				}
			

			}
			KeyBoardCheck = 'S';//Save current direction of movement



		}
			
		break;

		
	}
	 if (BlockCheck == 1)//If snake'head hit a wall
	{

		KillTimer(1);
		KillTimer(2);
		KillTimer(3);
		KillTimer(4);
		if (MessageBox(L"벽에 쿵!", L"실패", MB_ICONHAND) == IDOK)
		{
			this->DestroyWindow();

		}
	}
	else if (BodyCheck == 1)//If snake'head hit a Body
	{
		KillTimer(1);
		KillTimer(2);
		KillTimer(3);
		KillTimer(4);
		if (MessageBox(L"몸에 쿵!", L"실패", MB_ICONHAND) == IDOK)
		{
			this->DestroyWindow();

		}
	}
		CDialogEx::OnTimer(nIDEvent);
	
}


void CCProjectSnakeGameDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)//Function to handle keyboard input.
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) 
	{
		
	case 'w': 
	case 'W':
		
		if (KeyBoardCheck != 's'&&KeyBoardCheck != 'S')//Turning 180 degrees is blocked
		{
			KillTimer(2);
			KillTimer(3);
			KillTimer(4);
			
			SetTimer(1, SnakeSpeed, nullptr); //1:timer id, 55: period(ms)
			
		}
		
		break; 

	case 'a':
	case 'A':

		if (KeyBoardCheck != 'd'&&KeyBoardCheck != 'D')//Turning 180 degrees is blocked
		{
			KillTimer(1);
			KillTimer(3);
			KillTimer(4);
			
			SetTimer(2, SnakeSpeed, nullptr); //2:timer id, 55: period(ms)
	
		}
		break;

	case 'd':
	case 'D':

		if (KeyBoardCheck != 'a'&&KeyBoardCheck != 'A')//Turning 180 degrees is blocked
		{
			KillTimer(1);
			KillTimer(2);
			KillTimer(4);
			SetTimer(3, SnakeSpeed, nullptr); //3:timer id, 55: period(ms)
		}
		break;

	case 's':
	case 'S':

		
		if (KeyBoardCheck != 'w'&& KeyBoardCheck != 'W')//Turning 180 degrees is blocked
		{
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			
			SetTimer(4, SnakeSpeed, nullptr); //4:timer id, 55: period(ms) 
		}
		break;

	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

int CCProjectSnakeGameDlg::BodyHit()//Function to check if head hit  body.
{
	Snake * temp = A.Head;
	int xtemp = A.Head->x;
	int ytemp = A.Head->y;
	int check = 0;
	while(temp!=NULL)
	{
		if (temp != A.Head)
		{
			if (xtemp == temp->x&&ytemp == temp->y)
			{
				check++;
				break;
			}
		}
		temp = temp->next;
	}
	if (check > 0)
	{
		return 1;

	}
	else
	{
		return 0;
	}
	
}

void CCProjectSnakeGameDlg::FoodHit(int xPre,int yPre)//Function to check if head hit food.
{
	Snake * temp = A.Head;
	int xtemp=temp->x;
	int ytemp = temp->y;
	if (xtemp == xrand && ytemp == yrand)
	{
		FoodEatCount++;
		A.AddSnake(xPre, yPre);
		if (FoodEatCount == (MapVerticalityMax-2) * (MapHorizontalityMax-2) - 3)//When the body of the snake and tail of the head are completely filled with the map
		{
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			KillTimer(4);
			Invalidate(FALSE);

			if (MessageBox(L"뱀은 배가 부릅니다.", L"성공", MB_ICONASTERISK) == IDOK)
			{
				this->DestroyWindow();

			}
		}
		else
		{
			FoodPositionChange();
		}
		
	}
}

void CCProjectSnakeGameDlg::FoodPositionChange()//A function that redefines the location of food through random functions.
{
	/*The position of the food should not be in the body of the snake, so declare it as a recursive function to prevent this situation.*/
	Snake * temp = A.Head;
	xrand = rand() % (MapVerticalityMax-2) + 1;
	yrand = rand() % (MapVerticalityMax - 2) + 1;
	while (temp != NULL)
	{
		if (xrand == temp->x && yrand == temp->y)
		{
			FoodPositionChange();
			return;
		}
		temp = temp->next;
	}
	Invalidate(FALSE);//Update Map
}


