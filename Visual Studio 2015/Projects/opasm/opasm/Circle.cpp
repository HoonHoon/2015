#include<Windows.h>

void Circle(HDC hdc, int getX, int getY, int curX, int curY) {
	//�� ��� ��
	int hx = (curX + getX) / 2;
	int hy = (curY + getY) / 2;

	//�� ������� ���� �־��� ���� ���������� ����
	int r = max(abs(hx - getX), abs(hy-getY));
	r = max(r, abs(curX - hx));
	r = max(r, abs(curY - hy));

	Ellipse(hdc, hx - r, hy - r, hx + r, hy + r);
}

int movinCircle(HDC hdc, int getX, int getY, int setX, int setY) {
	int hx = (setX + getX) / 2;
	int hy = (setY + getY) / 2;

	//Ÿ�̸� �Լ��� �浹�� ����ؼ� x�ุ �������� ���� ����
	int r = abs(setX - getX);
	
	Ellipse(hdc, hx - r, hy - r, hx + r, hy + r);

	return r;
}

