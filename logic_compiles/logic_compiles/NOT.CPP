#include "stdafx.h"
#include "not.h"
#include "gate.h"




CNot::CNot(int X, int Y, int Colour)
{
	X1 = X;
	Y1 = Y;
	X2 = X + 25;
	Y2 = Y + 25;
	InNum = 1;
	OutNum = 1;
	for (int i = 0; i < InNum; i++)
		TabPrevElem[i] = NULL;
	for (int i = 0; i < OutNum; i++)
		TabNextElem[i] = NULL;
	Output = error;
	Movable = true;
}

void CNot::DrawElem(int Colour)
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
	drawLine(GetDC(GetActiveWindow()), X1 + 8, Y1 + 7, X1 + 8, Y1 + 22, black);//linia z lewej
	drawLine(GetDC(GetActiveWindow()), X1 + 3, Y1 + 14, X1 + 8, Y1 + 14, black);//wej�cie
	drawLine(GetDC(GetActiveWindow()), X1 + 8, Y1 + 7, X1 + 17, Y1 + 14, black);//linia z g�ry
	drawLine(GetDC(GetActiveWindow()), X1 + 8, Y1 + 22, X1 + 17, Y1 + 14, black);//linia z do�u
	drawCircle(GetDC(GetActiveWindow()), X1 + 19, Y1 + 14, 2, black);//negacja
	drawLine(GetDC(GetActiveWindow()), X1 + 21, Y1 + 14, X1 + 24, Y1 + 14, black);//wyj�cie
}

TOutput CNot::GetOutput(int AskElemNum, int MaxNum)
{
	if (AskElemNum == MaxNum) return Output;
	//rekurencja wpad�a w p�tl� sprz��enia zwrotnego
	if (TabPrevElem[0] == NULL)//bramka jednowej�ciowa
	{
		Output = error;
		return Output;
	}
	TOutput TmpValue = TabPrevElem[0]->GetOutput(AskElemNum + 1, MaxNum);
	if (TmpValue == high) Output = low;
	else if (TmpValue == low) Output = high;
	else Output = error;
	return Output;
}

TElementType CNot::ElementType()
{
	return not;
}

void CNot::ClickElement()
{}

char CNot::LinkPrevElem(CElement*PrevElem, int X, int Y)
{
	if (PrevElem->ElementType() != wire) return 0;
	//bramka mo�e by� po��czona tylko z drutem
	X -= X1;
	Y -= Y1;//zmienne X i Y okre�laj� wzgl�dne po�o�enie
	if (TabPrevElem[0] != NULL) return 0;
	TabPrevElem[0] = PrevElem;
	PrevElem->MoveEnd(X1 + 3, Y1 + 14);
	return 1;
}
