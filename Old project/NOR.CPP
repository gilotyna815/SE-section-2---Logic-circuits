#include "nor.h"
#include "gate.h"

CNor::CNor(int X,int Y,int Colour)
{
	X1=X;
	Y1=Y;
	X2=X+25;
	Y2=Y+25;
	InNum=2;
	OutNum=1;
	for(int i=0;i<InNum;i++)
		TabPrevElem[i]=NULL;
	for(i=0;i<OutNum;i++)
		TabNextElem[i]=NULL;
	Output=error;
	Movable=yes;
}

void CNor::DrawElem(int Colour)
{
	if(Colour==0)
	{
		switch(Output)
		{
			case low:Colour=LowColour;break;
			case high:Colour=HighColour;break;
			case error:Colour=ErrorColour;break;
		}
	}
	setcolor(Colour);
	arc(X1+3,Y1+14,315,54,9);//�uk z lewej
	line(X1+3,Y1+12,X1+10,Y1+12);//we g.
	line(X1+3,Y1+17,X1+10,Y1+17);//we d.
	arc(X1+8,Y1+14,270,90,8);//�uk z prawej
	circle(X1+18,Y1+14,2);//negacja
	line(X1+21,Y1+14,X1+24,Y1+14);//wyj�cie
}

TOutput CNor::GetOutput(int AskElemNum,int MaxNum)
{
	if(AskElemNum==MaxNum) return Output;
		//rekurencja wpad�a w p�tl� sprz��enia zwrotnego
	if(Output==error)	Output=low;//warto�� wyj�ciowa
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
			else Value+=TmpValue;
			if(Value>1) Value=1;
		}
	}
	if(Value==low) Value=high;
	else Value=low;
	if(Output!=error) Output=Value;
	return Output;
}

TElementType CNor::ElementType()
{
	return nor;
}

void CNor::ClickElement()
{}
