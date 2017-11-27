#ifndef DefNot
#define DefNot

#include "element.h"

class CNot:public CElement
{
 public:
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	char LinkPrevElem(CElement*PrevElem,int X,int Y);
	TElementType ElementType();
	CNot(int X,int Y,int Colour=0);
};

#endif