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
		
		//case �̿� ��Ȳ�� �߻��ص� ������� �ʴ´�

		//â�� �����Ǳ� ���� �ѹ��� ����
	case WM_CREATE:
		//Ÿ�̸� ����
		timecount = 0;
		memset(bubup, 0, 100);
		memset(random, 0, 100);
		SetTimer(h, TIMER, 1000, NULL);
		SetTimer(h, BUBBLE, 1, NULL);

		//�����
		count = 0;
		for (int i = 0; i < 100; i++) {
			random[i] = rand() % 5 + 1;
		}

		//â�� �����Ǳ� ���̶� GetDC�� �� �ʿ䰡 ���°ǰ�

		//hdc�� ȣȯ�Ǵ� �޸�dc�� �����
		mdc = CreateCompatibleDC(hdc);

		//�̹����� �ε��Ͽ� ��Ʈ�ʿ� �ִ´�
		hbm = (HBITMAP)LoadImageW(NULL, L"intothesea.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		//â�� ������ �����ͼ� RECT����ü�� ��´�
		GetClientRect(h, &rect);

		//RECTó�� HBITMAP�� ������ �����ͼ� BITMAP����ü�� ��´�
		GetObjectW(hbm, sizeof(bm), &bm);

		//mdc�� hbm�� �ִ´�
		SelectObject(mdc, hbm);

		break;
	case WM_PAINT:	//â�� ������ �� �ѹ� ����, â�� ��ȭ�� ���涧 ���� ����

		//ȭ����¿� �ʿ��� ��� ������ ������ ����ü
		hdc = GetDC(h);

		//mdc�� �ִ� ������ hdc�� ����
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, mdc, 0, 0, SRCCOPY);

		ReleaseDC(h, hdc);
		break;
	case WM_TIMER:
		//��Ÿ�̸� 2��° �μ��� �ĺ���
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
			//�귯���� ��������� �Ѵ�
			SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
			for (int i = 0; i < count; i++) {


				bubup[i]++;
				if ((argY[i] - random[i] * bubup[i]) < 0) {
					//����� ��Ʈ����
					pop(i);
				}
				movinCircle(hdc, argX[i], argY[i] - random[i]* 2 * bubup[i], arsX[i], arsY[i]);

			}
			ReleaseDC(h, hdc);
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:		//ó�� ���콺�� ������ �� ����Ǵ� ���
		hdc = GetDC(h);
		getX = LOWORD(lp);
		getY = HIWORD(lp);

		argX[count] = getX;
		argY[count] = getY;
		ReleaseDC(h, hdc);
		break;
	case WM_LBUTTONUP:				//ó�� ���콺�� �� ��
		setX = LOWORD(lp);
		setY = HIWORD(lp);

		arsX[count] = setX;
		arsY[count] = setY;

		bubup[count] = 0;

		//���� hdc�� ȭ���� mdc�� �����Ѵ�
		BitBlt(mdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdc, 0, 0, SRCCOPY);

		//����� ����
		count++;
		break;
	case WM_MOUSEMOVE:
		curX = LOWORD(lp);
		curY = HIWORD(lp);

		//�����鼭 �̵��Ҷ�
		if (wp == MK_LBUTTON) {
			//ȭ����¿� �ʿ��� ��� ������ ������ ����ü
			hdc = GetDC(h);

			//����� �ð������ʱ�ȭ�� �Ǿ ���� �߰��� �ʿ䰡 ����

			//�귯���� ��������� �Ѵ�
			SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
			//���� �׸��� �Լ�
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
	//stack�� pop�� ����
	for (int j = i; j < count; j++) {

		argX[j] = argX[j+1];
		argY[j] = argY[j+1];
		arsX[j] = arsX[j+1];
		arsY[j] = arsY[j+1];
		bubup[j] = bubup[j + 1];		//�����带 ��������ʾƼ� �����������ִµ�
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