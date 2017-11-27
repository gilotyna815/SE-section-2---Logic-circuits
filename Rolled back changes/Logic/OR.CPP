#include "or.h"
#include "gate.h"

COr::COr(int X,int Y,int Colour)
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


TOutput COr::GetOutput(int AskElemNum,int MaxNum)
{
	if(AskElemNum==MaxNum) return Output;
		//rekurencja wpadˆa w p©tl© sprz©¾enia zwrotnego
	if(Output==error)	Output=low;//warto˜† wyj˜ciowa
	TOutput Value=low;
	for(int i=0;i<InNum;i++)
	{
		if(TabPrevElem[i]==NULL)
			Output=error;
		else
		{
			TOutput TmpValue=TabPrevElem[i]->GetOutput(AskElemNum+1,MaxNum);
			if(TmpValue==error)
				Output=error;
			else Value=(TOutput)(Value+TmpValue);
			if(Value>1) Value = high;
		}
	}
	if(Output!=error) Output=Value;
	return Output;
}

TElementType COr::ElementType()
{
	return or;
}

void COr::ClickElement()
{}
