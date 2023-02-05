// ㄴㄴㄴ.cpp: 구현 파일
//

#include "stdafx.h"
#include "C++Project Snake Game.h"
#include "ㄴㄴㄴ.h"
#include "afxdialogex.h"


// ㄴㄴㄴ 대화 상자

IMPLEMENT_DYNAMIC(ㄴㄴㄴ, CDialogEx)

ㄴㄴㄴ::ㄴㄴㄴ(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ㄴㄴㄴ::~ㄴㄴㄴ()
{
}

void ㄴㄴㄴ::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ㄴㄴㄴ, CDialogEx)
END_MESSAGE_MAP()


// ㄴㄴㄴ 메시지 처리기
