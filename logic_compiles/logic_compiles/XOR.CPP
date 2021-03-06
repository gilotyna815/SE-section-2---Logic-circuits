#include "stdafx.h"
#include "xor.h"
#include "gate.h"




CXor::CXor(int X, int Y, int Colour)
{
	X1 = X;
	Y1 = Y;
	X2 = X + 25;
	Y2 = Y + 25;
	InNum = 2;
	OutNum = 1;
	for (int i = 0; i < InNum; i++)
		TabPrevElem[i] = NULL;
	for (int i = 0; i < OutNum; i++)
		TabNextElem[i] = NULL;
	Output = error;
	Movable = true;
}

void CXor::DrawElem(int Colour)
{
	if (Colour == 0)
	{
		switch (Output)
		{
		case low:Colour = LowColour; break;
		case high:Colour = HighColour; break;
		case error:Colour = ErrorColour; break;
		}
	}
	//setcolor(Colour);	//todo
	drawArc(GetDC(GetActiveWindow()), X1 + 1, Y1 + 14, 315, 54, 9, black);
	drawArc(GetDC(GetActiveWindow()), X1 + 5, Y1 + 14, 315, 54, 9, black);//drugi �uk z lewej
	drawLine(GetDC(GetActiveWindow()), X1 + 3, Y1 + 12, X1 + 8, Y1 + 12, black);//we g.
	drawLine(GetDC(GetActiveWindow()), X1 + 3, Y1 + 17, X1 + 8, Y1 + 17, black);//we d.
	drawArc(GetDC(GetActiveWindow()), X1 + 10, Y1 + 14, 270, 90, 8, black);//�uk z prawej
	drawLine(GetDC(GetActiveWindow()), X1 + 19, Y1 + 14, X1 + 24, Y1 + 14, black);//wyj�cie
}

TOutput CXor::GetOutput(int AskElemNum, int MaxNum)
{
	if (AskElemNum == MaxNum) return Output;
	//rekurencja wpad�a w p�tl� sprz��enia zwrotnego
	if (Output == error)	Output = low;//warto�� wyj�ciowa
	TOutput Value = low;
	for (int i = 0; i < InNum; i++)
	{
		if (TabPrevElem[i] == NULL)
			Output = error;
		else
		{
			TOutput TmpValue = TabPrevElem[i]->GetOutput(AskElemNum + 1, MaxNum);
			if (TmpValue == error)
				Output = error;
			else Value = (TOutput)(Value + TmpValue);
			if (Value > 1) Value = low;
		}
	}
	if (Output != error)	Output = Value;
	return Output;
}

TElementType CXor::ElementType()
{
	return xor;
}

void CXor::ClickElement()
{}
