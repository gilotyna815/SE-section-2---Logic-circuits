// Main.cpp: Okre�la punkt wej�cia dla aplikacji.
//

#include "stdafx.h"
#include "window.h"
#include "smallwin.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib,"Gdiplus.lib")


#define MAX_LOADSTRING 100
#define IDC_SE_CURRENT 100
#define IDI_SE_CURRENT 100

// Zmienne globalne:
HINSTANCE hInst;                                // bie��ce wyst�pienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytu�u
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna g��wnego


extern Gdiplus::Color black(255, 0, 0, 0);
extern Gdiplus::Color red(255, 255, 0, 0);
extern Gdiplus::Color blue(255, 0, 0, 255);
extern Gdiplus::Color gray(255, 169, 169, 169);
extern Gdiplus::Color orange(255, 255, 165, 0);
extern Gdiplus::Color white(255, 255, 255, 255);

// Przeka� dalej deklaracje funkcji do��czonych w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: W tym miejscu umie�� kod.

	// Zainicjuj ci�gi globalne
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SE_CURRENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Wykonaj inicjacje aplikacji:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SE_CURRENT));

	MSG msg;

	FirstInfo();

	// idk where to put this part ------------------------------------------------------------------------------
	do
	{
		Control();
	} while (!ConfirmQuit());
	// ---------------------------------------------------------------------------------------------------------


	// G��wna p�tla wiadomo�ci:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}



	return (int)msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klas� okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SE_CURRENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SE_CURRENT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje doj�cie wyst�pienia i tworzy okno g��wne
//
//   KOMENTARZE:
//
//        W tej funkcji doj�cie wyst�pienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wy�wietlane okno g��wne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Przechowuj doj�cie wyst�pienia w zmiennej globalnej

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	// currentWin = GetDC(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza wiadomo�ci dla okna g��wnego.
//
//  WM_COMMAND � przetwarzaj menu aplikacji
//  WM_PAINT � pomaluj okno g��wne
//  WM_DESTROY � opublikuj komunikat o rezygnacji i wr��
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizuj zaznaczenia menu:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: tutaj dodaj kod rysowania u�ywaj�cy elementu hdc...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//Procedura obs�ugi wiadomo�ci dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//Funkcje dodatkowe
/*void InitGraph(char *path = "f:/borlandc/bgi")
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, path);//"c:/borlandc/bgi");
	errorcode = graphresult();
	if (errorcode)
	{
		gotoxy(23, 8);
		printf("Graphic's error has appeared!");
		gotoxy(12, 10);
		printf("While running this programm please write an access path");
		gotoxy(27, 12);
		printf("to a file \"egavga.bgi\".");
		gotoxy(25, 20);
		printf("Press any key to continue...");
		getch();
	}
}*/

/*int CheckMouse()
{
	struct REGPACK reg;
	reg.r_ax = 0x0;
	intr(0x33, &reg);
	if (reg.r_ax == 0)
	{
		printf("\n\n\t\tError!!!\n\n\tMouse not installed!!!");
		return 0;
	}
	return 1;
}*/
//put pixel at (x,y)
void putPixel(HDC hdc, int x, int y, Gdiplus::Color color)
{
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen pen(color, 1.0f); //Alpha(transparency), Red, Green, Blue, penWidth
	graphics.DrawLine(&pen, x, y, x + 1, y + 1);

}
//draws a pie centered at (x,y) with radius given by width. The pie travels from startAngle to sweepAngle
void drawPie(HDC hdc, int x, int y, float startAngle, float sweepAngle, int width, Gdiplus::Color color) {

	sweepAngle = sweepAngle * 2;
	y = (y - width);
	x = (x - width);
	width = width * 2;
	int height = width;
	Gdiplus::Graphics graphics(hdc);
	// Draw the pie.
	Gdiplus::Pen pen(color, 1.0f); //Alpha(transparency), Red, Green, Blue, penWidth
	graphics.DrawPie(&pen, x, y, width, height, startAngle, sweepAngle);
}
//draws an arc centered at (x,y) with radius given by width. The arc travels from startAngle to sweepAngle
void drawArc(HDC hdc, int x, int y, float startAngle, float sweepAngle, int width, Gdiplus::Color color) {

	sweepAngle = sweepAngle * 2;
	y = (y - width);
	x = (x - width);
	width = width * 2;
	int height = width;
	Gdiplus::Graphics graphics(hdc);
	// Draw the pie.
	Gdiplus::Pen pen(color, 1.0f); //Alpha(transparency), Red, Green, Blue, penWidth
						  //y = (y - 4);
	graphics.DrawArc(&pen, x, y, width, height, startAngle, sweepAngle);
}
//draws line from point (x1,y1) to point (x2,y2)
void drawLine(HDC hdc, int x1, int y1, int x2, int y2, Gdiplus::Color color)
{
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen pen(color, 5.0f);
	graphics.DrawLine(&pen, x1, y1, x2, y2);
}
//draws basket with left upper corner coordinate (X,Y)
void drawBasket(HDC hdc, int X, int Y)
{
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen basketPen(Gdiplus::Color(255, 0, 0, 255), 1.0f); //Alpha(transparency), Red, Green, Blue, penWidth
	Gdiplus::Pen squarePen(Gdiplus::Color(255, 0, 0, 0), 1.0f);
	Gdiplus::Pen fatPen(Gdiplus::Color(255, 0, 0, 255), 3.0f);
	//Square containing basket
	graphics.DrawLine(&squarePen, X, Y, X, Y + 30);
	graphics.DrawLine(&squarePen, X, Y + 30, X + 26, Y + 30);
	graphics.DrawLine(&squarePen, X + 26, Y + 30, X + 26, Y);
	graphics.DrawLine(&squarePen, X + 26, Y, X, Y);
	//basket
	graphics.DrawLine(&fatPen, X + 6, Y + 27, X + 20, Y + 27); //bottom
	graphics.DrawLine(&basketPen, X + 6, Y + 26, X + 2, Y + 4);
	graphics.DrawLine(&basketPen, X + 20, Y + 26, X + 24, Y + 4);
	graphics.DrawLine(&basketPen, X + 8, Y + 10, X + 9, Y + 26);
	graphics.DrawLine(&basketPen, X + 13, Y + 10, X + 13, Y + 26);

	graphics.DrawLine(&basketPen, X + 18, Y + 10, X + 17, Y + 26);
	graphics.DrawLine(&basketPen, X + 4, Y + 10, X + 22, Y + 10);
	graphics.DrawLine(&basketPen, X + 5, Y + 14, X + 21, Y + 14);
	graphics.DrawLine(&basketPen, X + 5, Y + 18, X + 21, Y + 18);
	graphics.DrawLine(&basketPen, X + 6, Y + 22, X + 20, Y + 22);

}
//draw image with left upper corner at (X,Y)
//TO DO try to use this function instead of putImage in window.cpp
void drawImage(HDC hdc, int X, int Y, HDC hdcMem, HGDIOBJ oldBitmap, BITMAP bitmap, HBITMAP hBitmap) {
	//hdcMem = CreateCompatibleDC(hdc);
	//oldBitmap = SelectObject(hdcMem, hBitmap);
	//GetObject(hBitmap, sizeof(bitmap), &bitmap);

	BitBlt(hdc, X, Y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
}
//draws a rectangle with: 
//left upper corner coordinate (x1,y1)
//right bottom corner coordinate (x2, y2)
void drawBar(HDC hdc, int x1, int y1, int x2, int y2, Gdiplus::Color color) {
	int width = x2 - x1;
	int height = y2 - y1;
	Gdiplus::Graphics graphics(hdc);
	//Pen pen(Color(100, 0, 0, 0), 5.0f);
	Gdiplus::SolidBrush blackBrush(color);
	//graphics.DrawRectangle(&pen, x1, y1, width, height);
	graphics.FillRectangle(&blackBrush, x1, y1, width, height);
}

void drawCircle(HDC hdc, int x, int y, int radius, Gdiplus::Color color)
{
	int X1, Y1;
	X1 = x - radius;
	Y1 = y - radius;

	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen pen(color, 1.0f); //Alpha(transparency), Red, Green, Blue, penWidth
	graphics.DrawEllipse(&pen, X1, Y1, 2 * radius, 2 * radius);

}

void Control()
{
	int CurrentWinNum = 0;//numer aktualnie otwartego okna
	int TotalWinNum = 1;//ilo�� wszystkich otwartych okien
	char NewPossib = 1;//flaga m�wi�ca, czy mo�e powsta� nowe okno
	char IsNew = 1;//flaga m�wi�ca, czy okno jest nowe
	char IsPrev;//flaga m�wi�ca, czy istnieje okno wcze�niejsze
	char IsNext;//flaga m�wi�ca, czy istnieje okno nast�pne
	int TabWin[MaxWinNum];//tablica flag m�wi�cych, czy okno istnieje
	for (int i = 0; i < MaxWinNum; i++) TabWin[i] = 0;
	TabWin[0] = 1;
	do
	{
		IsPrev = 0;
		IsNext = 0;
		for (int i = 0; i < CurrentWinNum; i++)
			if (TabWin[i] == 1)
			{
				IsPrev = 1;
				break;
			}
		for (int i = CurrentWinNum + 1; i < MaxWinNum; i++)
			if (TabWin[i] == 1)
			{
				IsNext = 1;
				break;
			}
		CWindow*Window = new CWindow(GetDC(GetActiveWindow()), CurrentWinNum + 1, IsPrev, IsNext, NewPossib, IsNew);
		IsNew = 0;
		char WinResult = Window->Work();	//cursor
		if (WinResult == 0)//okno zostaje zamkni�te
		{
			TabWin[CurrentWinNum] = 0;
			TotalWinNum--;
			if (NewPossib == 0) NewPossib = 1;
			//skasowane zosta�o jakie� okno, wi�c mo�na utworzy� nowe okno
			int i;
			for (i = CurrentWinNum + 1; i < MaxWinNum; i++)
				if (TabWin[i] == 1)
				{
					CurrentWinNum = i;
					break;
				}
			if (i >= MaxWinNum)//nie zosta�o znalezione nast�pne otwarte okno
				for (i = CurrentWinNum - 1; i >= 0; i--)
					if (TabWin[i] == 1)
					{
						CurrentWinNum = i;
						break;
					}
			if (i < 0) TotalWinNum = 0;//okno zamkni�te by�o ostatnie
		}
		else
			if (WinResult == -1)//wy�wietlone ma by� okno poprzednie
			{
				int i;
				for (i = CurrentWinNum - 1; i >= 0; i--)
					if (TabWin[i] == 1) break;
				CurrentWinNum = i;
				if (i < 0) TotalWinNum = 0;//wyst�pi� b��d
			}
			else
				if (WinResult == 1)//wy�wietlone ma by� okno nast�pne
				{
					int i;
					for (i = CurrentWinNum + 1; i < MaxWinNum; i++)
						if (TabWin[i] == 1) break;
					CurrentWinNum = i;
					if (i >= MaxWinNum) TotalWinNum = 0;//wyst�pi� b��d
				}
				else
					if (WinResult == 2)//ma powsta� nowe okno
					{
						int i;
						for (i = 0; i < MaxWinNum; i++)
							if (TabWin[i] == 0) break;
						CurrentWinNum = i;
						TabWin[CurrentWinNum] = 1;
						TotalWinNum++;
						if (i >= MaxWinNum) TotalWinNum = 0;//wyst�pi� b��d
						if (i == MaxWinNum - 1) NewPossib = 0;
						IsNew = 1;//kolejne okno b�dzie nowym oknem
					}
		delete Window;
	} while (TotalWinNum > 0);
}

char ConfirmQuit()
{
	char*TabText[3];
	int i;
	TabText[0] = new char[40];
	TabText[1] = new char[40];
	strcpy(TabText[0], "You have closed the last window...");
	for (i = 0; i < 5; i++) TabText[1][i] = ' ';
	TabText[1][i] = '\x0';
	strcat(TabText[1], "Do you really want to quit?");
	TabText[2] = NULL;
	CSmallWindow*Window = new CSmallWindow(155, 130, 470, 0, "Confirm",
		TabText, 0, 2, "Yes", "No");
	char Result = Window->Work();
	delete Window;
	delete TabText[0];
	delete TabText[1];
	//REGPACK reg;
	//reg.r_ax = 0x2;
	//intr(0x33, &reg);//schowanie kursora
	//ShowCursor(false);
	//setfillstyle(1, BackgroundColour);
	SetBkColor(GetDC(GetActiveWindow()), BackgroundColour);
	//bar(155, 130, 470, 300);//zamalowanie okienka
	drawLine(GetDC(GetActiveWindow()), 155, 130, 470, 300, black);	//maybe we should use rectangle?
	//reg.r_ax = 0x1;
	//intr(0x33, &reg);//pokazanie kursora
	//ShowCursor(true);	//why though
	return Result;
}

void FirstInfo()
{
	int i;
	//setfillstyle(1, BackgroundColour);
	//setcolor(FrameColour);
	SetBkColor(GetDC(GetActiveWindow()), BackgroundColour);
	//bar(1, 1, 639, 479);
	drawLine(GetDC(GetActiveWindow()), 1, 1, 639, 479, black);	//maybe we should use rectangle?
	char*TabText[2];
	TabText[0] = new char[40];
	for (int i = 0; i < 4; i++) TabText[0][i] = ' ';
	TabText[0][i] = '\x0';
	strcat(TabText[0], "LOGIC CIRCUITS 1.0");
	TabText[1] = NULL;
	CSmallWindow*Window = new CSmallWindow(195, 130, 430, 0, "Information",
		TabText, 0, 1);
	Window->Work();
	delete Window;
	delete TabText[0];
}

/*main()
{
	long int a = stackavail();
	clrscr();
	if (!CheckMouse()) return 0;
	//InitGraph();
	FirstInfo();
	do
	{
		Control();
	} while (!ConfirmQuit());
	//closegraph();
	long int b = stackavail();
	printf("%ld\n%ld\n%ld\n", a, b, a - b);
	return 0;
}*/