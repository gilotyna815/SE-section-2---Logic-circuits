#ifndef DefJunction
#define DefJunction

#include "element.h"

class CJunction:public CElement
{
 public:
	char Move(int X,int Y,CElement**TabElem,int NumOfElem);
	void DrawElem(int Colour=0);
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	char LinkNextElem(CElement*NextElem,int X,int Y);
	char LinkPrevElem(CElement*PrevElem,int X,int Y);
	TElementType ElementType();
	CJunction(int X,int Y,int Colour=0);
	char DelNextElem(CElement*DelElem);
	int DeleteConnections(CElement**TabElem,int NumOfElem,char Main=1);
};

#endif