#include "stdafx.h"
#include "window.h"
#include "smallwin.h"
#include "menubut.h"
#include "modebut.h"




CSmallWindow::CSmallWindow(int X1, int Y1, int X2, int Y2, char*HeadingText,
	char**ConstText, char Reading, int ButtonNum,
	char*FirstButtonText, char*SecondButtonText)
{
	int i;
	Active = 1;
	this->X1 = X1;
	this->Y1 = Y1;
	this->HeadingText = HeadingText;
	for (i = 0; i < MaxSmallWinLinesNum; i++)
		if (ConstText[i] == NULL) break;
		else this->ConstText[i] = ConstText[i];
		LinesNum = i;
		if (LinesNum > MaxSmallWinLinesNum) LinesNum = MaxSmallWinLinesNum;
		if (X2 == 0)	this->X2 = X1 + 200;
		else this->X2 = X2;
		if (Y2 == 0)	this->Y2 = Y1 + LinesNum * 15 + 80;
		else this->Y2 = Y2;
		if (Reading) this->Y2 += 20;
		ReadText = NULL;
		this->Reading = Reading;
		this->ButtonNum = ButtonNum;
		char*Text = NULL;
		if (FirstButtonText == NULL)
		{
			Text = strdup("OK");
		}
		else
			Text = strdup(FirstButtonText);
		if (ButtonNum == 2)
		{
			TabBut[0] = new CMenuButton(Text, this->X1 + 15, this->Y2 - 30,
				(int)((this->X1 + this->X2) / 2 - 10), this->Y2 - 15);
			delete Text;
			if (SecondButtonText == NULL)
				Text = strdup("Cancel");
			else
				Text = strdup(SecondButtonText);
			TabBut[1] = new CMenuButton(Text, (int)((this->X1 + this->X2) / 2 + 10),
				this->Y2 - 30, this->X2 - 15, this->Y2 - 15);
		}
		else
			TabBut[0] = new CMenuButton(Text, this->X1 + 15, this->Y2 - 30,
				this->X2 - 15, this->Y2 - 15);
		delete Text;
}

CSmallWindow::~CSmallWindow()
{
	if (ReadText != NULL)
		delete ReadText;
	for (int i = 0; i < ButtonNum; i++)
		delete TabBut[i];
}

char CSmallWindow::Work()
{
	//struct REGPACK reg;
	POINT p;
	int x, y;
	if (ScreenToClient(GetActiveWindow(), &p))
	{
		x = p.x;
		y = p.y;
	}
	DrawSmallWin();
	//reg.r_ax = 0x1;
	//intr(0x33, &reg);//w��czenie
	if (kbhit())
		do
		{
			getch();
		} while (kbhit());
		do
		{
			if (kbhit())
				Read();
			//reg.r_ax = 0x3;
			//intr(0x33, &reg);
			if ((GetKeyState(VK_LBUTTON) & 0x100)) React(x, y);
		} while (Active);
		//reg.r_ax = 0x2;
		//intr(0x33, &reg);//wy��czenie
		return Result;
}

void CSmallWindow::React(int X, int Y)
{
	//struct REGPACK reg;
	CheckButtons(X, Y);
	do
	{
		//reg.r_ax = 0x3;
		//intr(0x33, &reg);
		ShowCursor(false);
	} while ((GetKeyState(VK_LBUTTON) & 0x100));//blokada-nic si� nie dzieje, gdy klawisz myszy
										//zosta� wci�ni�ty na pustym polu
}

void CSmallWindow::Read()
{
	//REGPACK reg;
	char TmpText[15];
	int Length;
	if (Reading)
	{
		Length = strlen(ReadText);
		strcpy(TmpText, ReadText);
	}
	else Length = 0;
	TmpText[Length] = getch();
	if ((int)TmpText[Length] == Enter)
	{
		if (Reading&&ReadText == NULL) return;
		Result = 1;
		Active = 0;
		return;//naci�ni�ty przycisk OK
	}
	if ((int)TmpText[Length] == Esc)
	{
		Result = 0;
		Active = 0;
		return;//naci�ni�ty przycisk Cancel
	}
	if (!Reading) return;//dalej jest obsluga pola do wprowadzania napisu
	//reg.r_ax = 0x2;
	//intr(0x33, &reg);//schowanie kursora
	//setfillstyle(1, BackgroundColour);
	SetBkColor(GetDC(GetActiveWindow()), BackgroundColour);
	//bar(X1 + 50, Y2 - 55, X1 + 150, Y2 - 40);//pole do odczytu
	drawLine(GetDC(GetActiveWindow()), X1 + 50, Y2 - 55, X1 + 150, Y2 - 40, black);
	TmpText[Length + 1] = '\x0';
	if ((int)TmpText[Length] == BackSpace&&Length > 0)
	{
		TmpText[Length - 1] = '\x0';
		Length -= 2;
	}//zmazanie ostatniego znaku
	else
	{
		if (Length >= 8)
		{
			TmpText[Length] = '\x0';
			Length--;
		}
		else
			if (!(((int)TmpText[Length] >= (int)'0' && (int)TmpText[Length] <= '9') ||
				((int)TmpText[Length] >= (int)'A' && (int)TmpText[Length] <= 'Z') ||
				((int)TmpText[Length] >= (int)'a' && (int)TmpText[Length] <= 'z')))
			{
				TmpText[Length] = '\x0';
				Length--;
			}
	}
//	TextOut(GetDC(GetActiveWindow()), X1 + 55, Y2 - 50, (LPCWSTR)TmpText, wcslen((LPCWSTR)TmpText));
	//reg.r_ax = 0x1;
	//intr(0x33, &reg);//pokazanie kursora
	ShowCursor(true);
	Length++;
	if (ReadText != NULL) delete ReadText;
	if (strlen(TmpText) == 0)
	{
		ReadText = NULL;
		return;
	}
	ReadText = strdup(TmpText);
}

int CSmallWindow::GetReadTextLength()
{
	return strlen(ReadText) + 1;
}

char CSmallWindow::GetReadText(char*ReadText)
{
	if (ReadText == NULL) return 0;
	strcpy(ReadText, this->ReadText);
	return 1;
}

void CSmallWindow::CheckButtons(int X, int Y)
{
	for (int i = 0; i < ButtonNum; i++)
		if (TabBut[i]->IsYourArea(X, Y))
			if (TabBut[i]->ClickButton())
				Action(i);
}

void CSmallWindow::DrawSmallWin()
{
	//setfillstyle(1, 8);
	//setcolor(8);	//todo
	drawLine(GetDC(GetActiveWindow()), X1, Y2, X2, Y2, black);
	drawLine(GetDC(GetActiveWindow()), X2, Y2, X2, Y1, black);
	drawLine(GetDC(GetActiveWindow()), X2, Y1, X1, Y1, black);
	//setfillstyle(1, HeadingColour);	//todo
	//bar(X1 + 1, Y1 + 1, X2 - 1, Y1 + 20);
	drawLine(GetDC(GetActiveWindow()), X1 + 1, Y1 + 1, X2 - 1, Y1 + 20, black);
	//setcolor(HeadingTextColour);	//todo
	//TextOut(GetDC(GetActiveWindow()), (int)(X1 + X2) / 2 - (strlen(HeadingText) / 2) * 9, Y1 + 8, (LPCWSTR)HeadingText, wcslen((LPCWSTR)HeadingText));
	//setfillstyle(1, FrameColour);	//todo
	//bar(X1 + 1, Y1 + 21, X2 - 1, Y2 - 1);//szare pole
	drawLine(GetDC(GetActiveWindow()), X1 + 1, Y1 + 21, X2 - 1, Y2 - 1, black);
	//setfillstyle(1, CustomTextColour);	//todo
	//setcolor(CustomTextColour);	//todo
	for (int i = 0; i < LinesNum; i++)
	{
		char*Text = ConstText[i];
		//TextOut(GetDC(GetActiveWindow()), X1 + 15, Y1 + 30 + i * 15, (LPCWSTR)Text, wcslen((LPCWSTR)Text));
	}
	if (Reading)
	{
		//setfillstyle(1, BackgroundColour);
		SetBkColor(GetDC(GetActiveWindow()), BackgroundColour);
		//bar(X1 + 50, Y2 - 55, X1 + 150, Y2 - 40);//pole do odczytu
		drawLine(GetDC(GetActiveWindow()), X1 + 50, Y2 - 55, X1 + 150, Y2 - 40, black);
		//setcolor(LineColour);	//todo
		drawLine(GetDC(GetActiveWindow()), X1 + 49, Y2 - 56, X1 + 49, Y2 - 39, black);
		drawLine(GetDC(GetActiveWindow()), X1 + 49, Y2 - 39, X1 + 151, Y2 - 39, black);
		drawLine(GetDC(GetActiveWindow()), X1 + 151, Y2 - 39, X1 + 151, Y2 - 56, black);
		drawLine(GetDC(GetActiveWindow()), X1 + 151, Y2 - 56, X1 + 49, Y2 - 56, black);
	}
	for (int i = 0; i < ButtonNum; i++)
		TabBut[i]->DrawButton();
}

void CSmallWindow::Action(int ActNum)
{
	switch (ActNum)
	{
	case 0:if (ReadText == NULL&&Reading) return;
		Result = 1; Active = 0; break;//naci�ni�ty przycisk OK
	case 1:Result = 0; Active = 0; break;//naci�ni�ty przycisk Cancel
	}
}
