#include <Windows.h>
#include <stdio.h>

#define wname L"Assignment"

LRESULT CALLBACK WndProc(HWND h, UINT im, WPARAM wp, LPARAM lp);

int APIENTRY  WinMain(HINSTANCE his,	//프로그램의 인스턴스 핸들
	HINSTANCE prev,						//바로앞에 실행된 현재 프로그램의 인스턴스 핸들, 호환성을 위해 존재
	LPSTR cmd,							//명령행으로 입력된 프로그램 인수 argv에 해당
	int cshow							//프로그램이 실행될 형태 최소화 창크기 등이 전달
	) {

	WNDCLASS wc;
	MSG Message;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	wc.hInstance = his;                    // 프로세스 핸들 
	wc.lpszClassName = wname;            // 윈도우 이름
	wc.lpfnWndProc = (WNDPROC)WndProc;    // 메시지 처리 함수 

	RegisterClass(&wc);

	HWND h = CreateWindow(wname, wname, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, his, NULL);

	ShowWindow(h, cshow);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
}
