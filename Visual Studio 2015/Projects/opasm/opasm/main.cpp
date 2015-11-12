#include <Windows.h>
#include <stdio.h>

#define wname L"Assignment"

LRESULT CALLBACK WndProc(HWND h, UINT im, WPARAM wp, LPARAM lp);

int APIENTRY  WinMain(HINSTANCE his,	//���α׷��� �ν��Ͻ� �ڵ�
	HINSTANCE prev,						//�ٷξտ� ����� ���� ���α׷��� �ν��Ͻ� �ڵ�, ȣȯ���� ���� ����
	LPSTR cmd,							//��������� �Էµ� ���α׷� �μ� argv�� �ش�
	int cshow							//���α׷��� ����� ���� �ּ�ȭ âũ�� ���� ����
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

	wc.hInstance = his;                    // ���μ��� �ڵ� 
	wc.lpszClassName = wname;            // ������ �̸�
	wc.lpfnWndProc = (WNDPROC)WndProc;    // �޽��� ó�� �Լ� 

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
