#include "and.h"


CAnd::CAnd(int X,int Y,int Colour)
{
	X1=X;
	Y1=Y;
	X2=X+25;
	Y2=Y+25;
	InNum=2;
	OutNum=1;
	for(int i=0;i<InNum;i++)
		TabPrevElem[i]=NULL;
	for(int i=0;i<OutNum;i++)
		TabNextElem[i]=NULL;
	Output=error;
	Movable=yes;
}

TOutput CAnd::GetOutput(int AskElemNum, int MaxNum)
{
		if (AskElemNum == MaxNum) return Output;
		//rekurencja wpadˆa w petle sprzezenia zwrotnego
		if (Output == error) Output = high;
		TOutput Value;
		Value= high;
		for (int i = 0; i<InNum; i++)
		{
			if (TabPrevElem[i] == NULL)
				Output = error;
			else
			{
				TOutput TmpValue = TabPrevElem[i]->GetOutput(AskElemNum + 1, MaxNum);
				if (TmpValue == error)
					Output = error;
				else Value = (TOutput)(Value * TmpValue);
			}
		}
		if (Output != error) Output = Value;
		return Output;
}


TElementType CAnd::ElementType()
{
	return and;
}

void CAnd::ClickElement()
{}
