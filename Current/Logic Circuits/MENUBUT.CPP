#include "stdafx.h"
#include "menubut.h"
#include "gate.h"




CMenuButton::CMenuButton(char*Text, int X1, int Y1, int X2, int Y2)
{
	DrawingColour = 16;
	ButtonColour = FrameColour;
	Insert = false;
	Active = true;
	this->X1 = X1;
	this->X2 = X2;
	this->Y1 = Y1;
	this->Y2 = Y2;
	ButtonText = NULL;
	ButtonText = strdup(Text);
};

CMenuButton::~CMenuButton()
{
	delete ButtonText;
}

void CMenuButton::DrawButton()
{
	//setfillstyle(1,LineColour);
	//setcolor(LineColour);	//todo
	drawLine(GetDC(GetActiveWindow()), X1, Y1, X2, Y1, black);
	drawLine(GetDC(GetActiveWindow()), X2, Y1, X2, Y2, black);
	drawLine(GetDC(GetActiveWindow()), X2, Y2, X1, Y2, black);
	drawLine(GetDC(GetActiveWindow()), X1, Y2, X1, Y1, black);
	//setfillstyle(1,ButtonColour);	//todo
	//bar(X1+1,Y1+1,X2-1,Y2-1);
	drawLine(GetDC(GetActiveWindow()), X1 + 1, Y1 + 1, X2 - 1, Y2 - 1, black);
	//setfillstyle(1,DrawingColour);	//todo
	//setcolor(DrawingColour);	//todo
	int X;
	int Y;
	if (X2 - X1 < 20) X = X1 + 2;
	else X = (int)(X1 + X2) / 2 - (strlen(ButtonText) / 2) * 9;
	if (Y2 - Y1 < 15) Y = Y1 + 2;
	else Y = (Y1 + Y2) / 2 - 3;
	TextOut(GetDC(GetActiveWindow()), X, Y, (LPCWSTR)ButtonText, wcslen((LPCWSTR)ButtonText));
}

void CMenuButton::ChangeText(char*Text)
{
	delete ButtonText;
	ButtonText = NULL;
	ButtonText = strdup(Text);
	this->DrawButton();
}

int CMenuButton::ClickButton()
{
	if (Active == false) return 0;
	POINT p;
	int x, y;
	if (ScreenToClient(GetActiveWindow(), &p))
	{
		x = p.x;
		y = p.y;
	}
	//struct REGPACK reg;
	//reg.r_ax=0x2;
	//intr(0x33,&reg);//schowanie myszy
	this->ChangeInsertMode();//zmiana
	//reg.r_ax=0x1;//pokazanie myszy
	//intr(0x33,&reg);
	int ButtonArea = 1;//flaga=1, gdy kursor jest na przycisku
	do
	{
		//reg.r_ax=0x3;
		//intr(0x33,&reg);//sprawdzenie
		if (!ButtonArea&&this->IsYourArea(x, y))
		{
			//reg.r_ax=0x2;
			//intr(0x33,&reg);//schowanie myszy
			this->ChangeInsertMode();//wci˜ni©cie
			//reg.r_ax=0x1;//pokazanie myszy
			//intr(0x33,&reg);
			ButtonArea = 1;
		}//kursor wszedˆ na pole przycisku
		if (ButtonArea && !(this->IsYourArea(x, y)))
		{
			//reg.r_ax=0x2;
			//intr(0x33,&reg);//schowanie myszy
			this->ChangeInsertMode(1);//puszczenie
			//reg.r_ax=0x1;//pokazanie myszy
			//intr(0x33,&reg);
			ButtonArea = 0;
		}//kursor opu˜ciˆ pole przycisku
		//reg.r_ax=0x3;
		//intr(0x33,&reg);
	} while ((GetKeyState(VK_LBUTTON) & 0x100));	//????????????????/
		//p©tla powtarza si©, gdy klawisz myszy jest wci˜ni©ty
	if (this->IsYourArea(x, y))
		//gdy klawisz zostaˆ puszczony na terenie przycisku
	{
		//reg.r_ax=0x2;
		//intr(0x33,&reg);//schowanie myszy
		this->ChangeInsertMode(1);//puszczenie
		//reg.r_ax=0x1;//pokazanie myszy
		//intr(0x33,&reg);
		return 1;//wykona† akcj© przycisku
	}
	//reg.r_ax=0x2;
	//intr(0x33,&reg);//schowanie myszy
	this->ChangeInsertMode(1);//wyˆ¥czenie przycisku
	//reg.r_ax=0x1;//pokazanie myszy
	//intr(0x33,&reg);
	return 0;//nic nie robi†
}
