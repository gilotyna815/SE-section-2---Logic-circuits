#ifndef DefNor
#define DefNor

#include "element.h"

class CNor:public CElement
{
 public:
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	TElementType ElementType();
	CNor(int X,int Y,int Colour=0);
};

#endif