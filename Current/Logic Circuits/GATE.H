#pragma once

#include "resource.h"
#include "stdafx.h"

#include <dos.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <io.h>
#include <SYS\STAT.H>
#include <malloc.h>
#include <process.h>

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#define BackSpace 8
#define Enter 13
#define Esc 27
#define MenuButNum 9
#define ButNum 16
#define HighColour 4
#define LowColour 1
#define ErrorColour 2
#define BasketColour 1
#define FrameColour 7
#define BackgroundColour 15
#define HeadingColour 1
#define HeadingTextColour 15
#define LineColour 16
#define InsertTextColour 12
#define CustomTextColour 16
#define NumberOfInBuses 6
#define NumberOfImages 8
#define MaxBreakpointsNum 4
#define MaxJunctionNum 10
#define MaxBusJunctionNum 30
#define MaxNumOfElem 100
#define MaxWinNum 99
#define MaxNextElemNum 1
#define MaxPrevElemNum 2
#define MaxSmallWinLinesNum 4

enum TElementType { and, or , not, nor, nand, xor, output, wire, junction, inbus, cbus };
enum TOutput { low = 0, high = 1, error = -1 };

//void InitGraph(char *path = "f:/borlandc/bgi");

//int CheckMouse();



void Control();

void FirstInfo();

char ConfirmQuit();

void drawPie(HDC hdc, int x, int y, float startAngle, float sweepAngle, int width);
void drawArc(HDC hdc, int x, int y, float startAngle, float sweepAngle, int width);
void drawLine(HDC hdc, int x1, int y1, int x2, int y2);
void drawBar(HDC hdc, int x1, int y1, int x2, int y2);
void drawBasket(HDC hdc, int X, int Y);

//main();