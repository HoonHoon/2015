#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>

#define TIMER 0
#define BUBBLE 1

RECT rect;
HDC hdc, mdc;
HBITMAP hbm;
BITMAP bm;
HRGN bubble;

static int timecount, bubup[100];
static wchar_t buff[10];
static wchar_t buff2[12];
static int getX, getY, curX, curY, setX, setY, count;
static int argX[100], argY[100], arsX[100], arsY[100], r[100];
static int random[100];

void Circle(HDC hdc, int getX, int getY, int curX, int curY);
int movinCircle(HDC hdc, int getX, int getY, int setX, int setY);
void pop(int i);

LRESULT CALLBACK WndProc(HWND h, UINT im, WPARAM wp, LPARAM lp) {
	switch (im) {
		
		//case 이외 상황이 발생해도 실행되지 않는다

		//창이 생성되기 전에 한번만 실행
	case WM_CREATE:
		//타이머 가동
		timecount = 0;
		memset(bubup, 0, 100);
		memset(random, 0, 100);
		SetTimer(h, TIMER, 1000, NULL);
		SetTimer(h, BUBBLE, 1, NULL);

		//물방울
		count = 0;
		for (int i = 0; i < 100; i++) {
			random[i] = rand() % 5 + 1;
		}

		//창이 생성되기 전이라서 GetDC를 할 필요가 없는건가

		//hdc와 호환되는 메모리dc를 만든다
		mdc = CreateCompatibleDC(hdc);

		//이미지를 로딩하여 비트맵에 넣는다
		hbm = (HBITMAP)LoadImageW(NULL, L"intothesea.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		//창의 정보를 가져와서 RECT구조체에 담는다
		GetClientRect(h, &rect);

		//RECT처럼 HBITMAP의 정보를 가져와서 BITMAP구조체에 담는다
		GetObjectW(hbm, sizeof(bm), &bm);

		//mdc에 hbm을 넣는다
		SelectObject(mdc, hbm);

		break;
	case WM_PAINT:	//창이 생성된 후 한번 실행, 창에 변화가 생길때 마다 실행

		//화면출력에 필요한 모든 정보를 가지는 구조체
		hdc = GetDC(h);

		//mdc에 있던 내용을 hdc에 복사
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, mdc, 0, 0, SRCCOPY);

		ReleaseDC(h, hdc);
		break;
	case WM_TIMER:
		//셋타이머 2번째 인수가 식별함
		switch (wp) {
		case TIMER:
			hdc = GetDC(h);
			swprintf_s(buff, L"Time: %d", timecount++);
			TextOut(hdc, bm.bmWidth, 0, buff, ARRAYSIZE(buff));
			ReleaseDC(h, hdc);
			break;
		case BUBBLE:
			hdc = GetDC(h);
			BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, mdc, 0, 0, SRCCOPY);
			//브러쉬를 투명색으로 한다
			SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
			for (int i = 0; i < count; i++) {


				bubup[i]++;
				if ((argY[i] - random[i] * bubup[i]) < 0) {
					//물방울 터트리기
					pop(i);
				}
				movinCircle(hdc, argX[i], argY[i] - random[i]* 2 * bubup[i], arsX[i], arsY[i]);

			}
			ReleaseDC(h, hdc);
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:		//처음 마우스를 눌렀을 때 저장되는 요소
		hdc = GetDC(h);
		getX = LOWORD(lp);
		getY = HIWORD(lp);

		argX[count] = getX;
		argY[count] = getY;
		ReleaseDC(h, hdc);
		break;
	case WM_LBUTTONUP:				//처음 마우스를 뗄 때
		setX = LOWORD(lp);
		setY = HIWORD(lp);

		arsX[count] = setX;
		arsY[count] = setY;

		bubup[count] = 0;

		//현재 hdc의 화면을 mdc에 복사한다
		BitBlt(mdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdc, 0, 0, SRCCOPY);

		//물방울 갯수
		count++;
		break;
	case WM_MOUSEMOVE:
		curX = LOWORD(lp);
		curY = HIWORD(lp);

		//누르면서 이동할때
		if (wp == MK_LBUTTON) {
			//화면출력에 필요한 모든 정보를 가지는 구조체
			hdc = GetDC(h);

			//배경은 시간마다초기화가 되어서 딱히 추가할 필요가 없다

			//브러쉬를 투명색으로 한다
			SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
			//원을 그리는 함수
			movinCircle(hdc, getX, getY, curX, curY);
			
			ReleaseDC(h, hdc);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(h, im, wp, lp));
}

void pop(int i) {
	//stack의 pop과 유사
	for (int j = i; j < count; j++) {

		argX[j] = argX[j+1];
		argY[j] = argY[j+1];
		arsX[j] = arsX[j+1];
		arsY[j] = arsY[j+1];
		bubup[j] = bubup[j + 1];		//스레드를 사용하지않아서 멈춤현상이있는듯
		r[j] = r[j+1];

		argX[j+1] = 0;
		argY[j+1] = 0;
		arsX[j+1] = 0;
		arsY[j+1] = 0;
		r[j + 1] = 0;
		bubup[j+1] = 0;
	}
	count--;
}