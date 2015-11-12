#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#define wname L"Assignment#2"
#define MSLOT L"\\\\.\\mailslot\\lotto"

LRESULT CALLBACK WndProc(HWND h, UINT im, WPARAM wp, LPARAM lp);
DWORD WINAPI ThreadFunc(LPVOID);

typedef struct _ball_info {
	int id;			// 고유값
	int x, y;		// 위치
	int dir;		// 방향
	HANDLE sep;
	HDC hdc;
	HWND h;
}BALL;

PROCESS_INFORMATION pi;
BALL balls[45];
BALL winballs[7];
DWORD threadID;
HANDLE sep;
HANDLE threadArray[45];
HDC hdc;
int width, height;
int randomX[45], randomY[45];
bool isServer;

LRESULT CALLBACK WndProc(HWND h, UINT im, WPARAM wp, LPARAM lp) {
	switch (im) {
	case WM_CREATE: {
		HANDLE mailslot;
		DWORD recvSize;
		
		// 메일슬롯 만들기
		mailslot = CreateFile(MSLOT, GENERIC_WRITE, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (mailslot == INVALID_HANDLE_VALUE) {
			mailslot = CreateMailslot(MSLOT, 0, 0, NULL);
			isServer = true;
		}
		else {
			isServer = false;
		}

		// Random Seed
		srand((unsigned)time(NULL));

		// 0.1초마다 갱신
		SetTimer(h, 0, 100, NULL);

		// 화면 얻기
		RECT rect;
		GetClientRect(h, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;

		// 세마포어
		sep = CreateSemaphore(NULL, 1, 1, L"");
		
		// 공 45개 만들기
		// 서버일 경우
		if (isServer) {
			for (int i = 0; i < 45; i++) {
				balls[i].id = i + 1;
				balls[i].x = 50 + 100 * (i % 9);			// row
				balls[i].y = 50 + 100 * (i / 9);		// column
				balls[i].hdc = hdc;
				balls[i].sep = sep;
				balls[i].h = h;

				// 랜덤 이동 변수 -1 ~ 1
				randomX[i] = 3 * ((rand() % 2) * 2 - 1);
				randomY[i] = 3 * ((rand() % 2) * 2 - 1);
			}
		}
		// 클라이언트 일 경우
		else {
			for (int i = 0; i < 7; i++) {
				balls[i].id = (rand() % 45) + 1;
				for (int j = 0; j < i; j++) {
					if (balls[j].id == balls[i].id) {
						i--;
						break;
					}
				}
				balls[i].h = h;
				balls[i].hdc = hdc;
				balls[i].sep = sep;
				balls[i].x = 200 + 100 * i;
				balls[i].y = height / 2;

				// 랜덤 이동 변수 -1 ~ 1
				randomX[i] = (rand() % 2);
				randomY[i] = (rand() % 2);
			}
		}
		break;
	}
	case WM_TIMER: {
		// 서버일 경우
		if (isServer) {
			for (int i = 0; i < 45; i++) {
				balls[i].x += randomX[i];
				balls[i].y += randomY[i];
				if (balls[i].x < 0 || balls[i].x > width) {
					randomX[i] *= -1;
				}
				if (balls[i].y<0 || balls[i].y>height) {
					randomY[i] *= -1;
				}
				threadArray[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&balls[i], 0, &threadID);
			}

			// THREAD JOIN
			if (threadArray != NULL) {
				WaitForMultipleObjects(45, threadArray, TRUE, INFINITE);
			}
		}
		// 클라이언트인 경우
		else {
			for (int i = 0; i < 7; i++) {
				balls[i].x += randomX[i];
				balls[i].y += randomY[i];
				threadArray[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&balls[i], 0, &threadID);
				Sleep(1000);
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
		if (isServer) {
			// 자식 프로세스 생성
			wchar_t title[10] = L"Lotto.exe";
			STARTUPINFO si = { 0, };
			CreateProcess(NULL, title, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi);
		}
		else {
			// 종료
			PostQuitMessage(0);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(h, im, wp, lp));
}

DWORD WINAPI ThreadFunc(LPVOID lp) {
	BALL ball = *(BALL *)lp;
	RECT rect;

	// 창 정보
	GetClientRect(ball.h, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 개체 정보
	RECT ballrect;
	ballrect.left = ball.x - 33;
	ballrect.top = ball.y - 33;
	ballrect.right = ball.x + 33;
	ballrect.bottom = ball.y + 33;

	ball.hdc = GetDC(ball.h);

	WaitForSingleObject(ball.sep, INFINITE);

	// 글씨체 설정
	HFONT font = CreateFont(30, 0, 0, 0, 0, false, false, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, L"Arial");
	SelectObject(ball.hdc, font);

	// 그리기
	FillRect(ball.hdc, &ballrect, CreateSolidBrush(RGB(255, 255, 255)));
	Ellipse(ball.hdc, ball.x - 30, ball.y - 30, ball.x + 30, ball.y + 30);
	wchar_t buf[10];
	swprintf_s(buf, 10, L"%d", ball.id);
	TextOut(ball.hdc, ball.x - 12, ball.y - 12, buf, 2);

	ReleaseSemaphore(ball.sep, 1, NULL);

	ReleaseDC(ball.h, ball.hdc);

	return 0;
}

int APIENTRY WinMain(HINSTANCE his, HINSTANCE prev, LPSTR cmd, int cshow) {
	WNDCLASS wc;
	MSG msg;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = his;					// process
	wc.lpszClassName = wname;			// window name;
	wc.lpfnWndProc = (WNDPROC)WndProc;	// msg event

	RegisterClass(&wc);

	HWND h = CreateWindow(wname, wname, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, his, NULL);
	ShowWindow(h, cshow);

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
