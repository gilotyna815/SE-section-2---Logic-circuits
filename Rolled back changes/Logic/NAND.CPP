#include "nand.h"
#include "gate.h"

CNand::CNand(int X,int Y,int Colour)
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


TOutput CNand::GetOutput(int AskElemNum,int MaxNum)
{
	if(AskElemNum==MaxNum) return Output;
		//rekurencja wpad�a w p�tl� sprz��enia zwrotnego
	if(Output==error) Output=high;
	TOutput Value=high;
	for(int i=0;i<InNum;i++)
	{
		if(TabPrevElem[i]==NULL)
			Output=error;
		else
		{
			TOutput TmpValue=TabPrevElem[i]->GetOutput(AskElemNum+1,MaxNum);
			if(TmpValue==error)
				Output=error;
			else Value = (TOutput)(Value * TmpValue);
		}
	}
	if(Value==low) Value=high;
	else Value=low;
	if(Output!=error) Output=Value;
	return Output;
}

TElementType CNand::ElementType()
{
	return nand;
}

void CNand::ClickElement()
{}
