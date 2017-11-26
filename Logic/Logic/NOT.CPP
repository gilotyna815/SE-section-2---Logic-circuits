#include "not.h"
#include "gate.h"

CNot::CNot(int X,int Y,int Colour)
{
	X1=X;
	Y1=Y;
	X2=X+25;
	Y2=Y+25;
	InNum=1;
	OutNum=1;
	for(int i=0;i<InNum;i++)
		TabPrevElem[i]=NULL;
	for(int i=0;i<OutNum;i++)
		TabNextElem[i]=NULL;
	Output=error;
	Movable=yes;
}


TOutput CNot::GetOutput(int AskElemNum,int MaxNum)
{
	if(AskElemNum==MaxNum) return Output;
		//rekurencja wpadˆa w p©tl© sprz©¾enia zwrotnego
	if(TabPrevElem[0]==NULL)//bramka jednowej˜ciowa
	{
		Output=error;
		return Output;
	}
	TOutput TmpValue=TabPrevElem[0]->GetOutput(AskElemNum+1,MaxNum);
	if(TmpValue==high) Output=low;
	else if(TmpValue==low) Output=high;
	else Output=error;
	return Output;
}

TElementType CNot::ElementType()
{
	return not;
}

void CNot::ClickElement()
{}

char CNot::LinkPrevElem(CElement*PrevElem,int X,int Y)
{
	if(PrevElem->ElementType()!=wire) return 0;
		//gate can be only connected with wire
	X-=X1;
	Y-=Y1;//X and Y are the position of gate
	if(TabPrevElem[0]!=NULL) return 0;
	TabPrevElem[0]=PrevElem;
	PrevElem->MoveEnd(X1+3,Y1+14);
	return 1;
}
