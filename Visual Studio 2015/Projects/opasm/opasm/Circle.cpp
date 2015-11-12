#include<Windows.h>

void Circle(HDC hdc, int getX, int getY, int curX, int curY) {
	//한 가운데 점
	int hx = (curX + getX) / 2;
	int hy = (curY + getY) / 2;

	//한 가운데에서 가장 멀어진 곳을 반지름으로 잡음
	int r = max(abs(hx - getX), abs(hy-getY));
	r = max(r, abs(curX - hx));
	r = max(r, abs(curY - hy));

	Ellipse(hdc, hx - r, hy - r, hx + r, hy + r);
}

int movinCircle(HDC hdc, int getX, int getY, int setX, int setY) {
	int hx = (setX + getX) / 2;
	int hy = (setY + getY) / 2;

	//타이머 함수와 충돌을 우려해서 x축만 기준으로 원을 만듬
	int r = abs(setX - getX);
	
	Ellipse(hdc, hx - r, hy - r, hx + r, hy + r);

	return r;
}

