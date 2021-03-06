#include "stdafx.h"
#include "modebut.h"
#include "gate.h"
#include "and.h"
#include "or.h"
#include "not.h"
#include "nand.h"
#include "nor.h"
#include "xor.h"
#include "output.h"
#include "wire.h"




CModeButton::CModeButton(TElementType ButtonType, int X1, int Y1, int X2, int Y2)
{
	this->X1 = X1;
	this->X2 = X2;
	this->Y1 = Y1;
	this->Y2 = Y2;
	DrawingColour = 16;
	ButtonColour = FrameColour;
	Insert = false;
	Active = true;
	ButtonElement = NULL;
	switch (ButtonType)
	{
	case and:ButtonElement = new CAnd(X1, Y1, DrawingColour); break;
	case or :ButtonElement = new COr(X1, Y1, DrawingColour); break;
	case not:ButtonElement = new CNot(X1, Y1, DrawingColour); break;
	case nor:ButtonElement = new CNor(X1, Y1, DrawingColour); break;
	case nand:ButtonElement = new CNand(X1, Y1, DrawingColour); break;
	case xor:ButtonElement = new CXor(X1, Y1, DrawingColour); break;
	case output:ButtonElement = new COutput(X1, Y1, DrawingColour); break;
	case wire:ButtonElement = new CWire(X1, Y1, DrawingColour); break;
	};
}

CModeButton::~CModeButton()
{
	delete ButtonElement;
}

void CModeButton::DrawButton()
{
	//setcolor(LineColour);	todo
	drawLine(GetDC(GetActiveWindow()), X1, Y1, X2, Y1, black);
	drawLine(GetDC(GetActiveWindow()), X2, Y1, X2, Y2, black);
	drawLine(GetDC(GetActiveWindow()), X2, Y2, X1, Y2, black);
	drawLine(GetDC(GetActiveWindow()), X1, Y2, X1, Y1, black);
	//	setfillstyle(1,ButtonColour);		//todo
	//bar(X1+1,Y1+1,X2-1,Y2-1);
	drawLine(GetDC(GetActiveWindow()), X1 + 1, Y1 + 1, X2 - 1, Y2 - 1, black);
	ButtonElement->DrawElem(DrawingColour);
}

void CModeButton::ChangeText(char*Text)
{}

int CModeButton::ClickButton()
{
	if (Active == true) return 1;
	return 0;
}
