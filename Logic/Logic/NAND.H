#ifndef DefNand
#define DefNand

#include "element.h"

class CNand:public CElement
{
 public:
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	TElementType ElementType();
	CNand(int X,int Y,int Colour=0);
};

#endif