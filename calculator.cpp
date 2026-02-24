#include <windows.h>
#include <stdio.h>

/* This is where all the input to the window goes to */
HWND textBox, NUM1, NUM2, B1, B2, B3, B4;
char textsaved1[100],textsaved2[100],result[100];
double x;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE: {
			textBox = CreateWindowExA(WS_EX_CLIENTEDGE,"STATIC","Please input two numbers",WS_VISIBLE|WS_CHILD,20,10,200,20,hwnd,NULL,NULL,NULL);
			NUM1 = CreateWindowExA(WS_EX_CLIENTEDGE,"EDIT","",WS_VISIBLE|WS_CHILD,60,40,120,20,hwnd,NULL,NULL,NULL);
			NUM2 = CreateWindowExA(WS_EX_CLIENTEDGE,"EDIT","",WS_VISIBLE|WS_CHILD,60,70,120,20,hwnd,NULL,NULL,NULL);
			B1 = CreateWindowExA(WS_EX_CLIENTEDGE,"BUTTON","+",WS_VISIBLE|WS_CHILD|WS_BORDER,25,110,42.5,42.5,hwnd,(HMENU) 1,NULL,NULL);
			B2 = CreateWindowExA(WS_EX_CLIENTEDGE,"BUTTON","-",WS_VISIBLE|WS_CHILD|WS_BORDER,75,110,42.5,42.5,hwnd,(HMENU) 2,NULL,NULL);
			B3 = CreateWindowExA(WS_EX_CLIENTEDGE,"BUTTON","*",WS_VISIBLE|WS_CHILD|WS_BORDER,125,110,42.5,42.5,hwnd,(HMENU) 3,NULL,NULL);
			B4 = CreateWindowExA(WS_EX_CLIENTEDGE,"BUTTON","/",WS_VISIBLE|WS_CHILD|WS_BORDER,175,110,42.5,42.5,hwnd,(HMENU) 4,NULL,NULL);
			break;
		}

		case WM_COMMAND: {
			switch(LOWORD(wParam)){
				case 1: {
					GetWindowTextA(NUM1, textsaved1, 100);
					GetWindowTextA(NUM2, textsaved2, 100);
					x = atof(textsaved1) + atof(textsaved2);
					sprintf(result,"%f", x);
					MessageBoxA(hwnd,result,"Result", MB_OK);
					
					break;
				}
				case 2:{
					GetWindowTextA(NUM1, textsaved1, 100);
					GetWindowTextA(NUM2, textsaved2, 100);
					x = atof(textsaved1) - atof(textsaved2);
					sprintf(result,"%f", x);
					MessageBoxA(hwnd,result,"Result", MB_OK);
					
					break;
				}
				case 3: {
					GetWindowTextA(NUM1, textsaved1, 100);
					GetWindowTextA(NUM2, textsaved2, 100);
					x = atof(textsaved1) * atof(textsaved2);
					sprintf(result,"%f", x);
					MessageBoxA(hwnd,result,"Result", MB_OK);
					break;
				}
				case 4: {
					GetWindowTextA(NUM1, textsaved1, 100);
					GetWindowTextA(NUM2, textsaved2, 100);
					x = atof(textsaved1) / atof(textsaved2);
					sprintf(result,"%f", x);
					MessageBoxA(hwnd,result,"Result", MB_OK);
					break;
				}
			}
			break;
		}
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_HOTLIGHT + 1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBoxA(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowExA(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBoxA(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
