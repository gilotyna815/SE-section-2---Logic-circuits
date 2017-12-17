#include "output.h"
#include "gate.h"

COutput::COutput(int X, int Y, int Colour)
{
	X1 = X;
	Y1 = Y;
	X2 = X + 25;
	Y2 = Y + 25;
	InNum = 1;
	OutNum = 0;
	TabPrevElem[0] = NULL;
	Output = high;
	Movable = true;
}

void COutput::DrawElem(int Colour)
{
	Color color = black;
	//setcolor(FrameColour);	//todo
	TextOut(GetDC(GetActiveWindow()), X1 + 17, Y1 + 10, L"?", 1);
	TextOut(GetDC(GetActiveWindow()), X1 + 17, Y1 + 10, L"0", 1);
	TextOut(GetDC(GetActiveWindow()), X1 + 17, Y1 + 10, L"1", 1);
	//zmazanie napisu
	if (Colour == 0)
	{
		switch (Output)
		{
		case low:Colour = LowColour; break;
		case high:Colour = HighColour; break;
		case error:Colour = ErrorColour; break;
		}
	}
	switch (Colour) {
	case LowColour: color = blue;
	case HighColour: color = red;
	case ErrorColour: color = orange;
	}
	//setcolor(Colour);	//todo
	//setfillstyle(1, Colour);	//todo
	drawLine(GetDC(GetActiveWindow()), X1 + 1, Y1 + 8, X1 + 10, Y1 + 13, color);
	drawLine(GetDC(GetActiveWindow()), X1 + 10, Y1 + 13, X1 + 1, Y1 + 18, color);
	char Text[2];
	switch (Output)
	{
	case low:Text[0] = '0'; break;
	case high:Text[0] = '1'; break;
	case error:Text[0] = '?'; break;
	}
	Text[1] = '\0';
	TextOut(GetDC(GetActiveWindow()), X1 + 17, Y1 + 10, (LPCWSTR)Text, wcslen((LPCWSTR)Text));
}

TOutput COutput::GetOutput(int AskElemNum, int MaxNum)
{
	if (TabPrevElem[0] == NULL) Output = error;
	else Output = TabPrevElem[0]->GetOutput(AskElemNum + 1, MaxNum);
	return Output;
}

TElementType COutput::ElementType()
{
	return output;
}

void COutput::ClickElement()
{}

int COutput::IsOnBoard()
{
	if (X1 < 611 || Y1 < 61 || Y2>440) return 0;
	X1 = 611;
	X2 = X1 + 25;	//autoformatowanie
	return 1;
}

char COutput::LinkNextElem(CElement*NextElem,int X,int Y)
{
	return 0;
}
