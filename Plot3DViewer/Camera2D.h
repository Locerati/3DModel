#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double L, R, B, T;					// ������� ���������� ������ ������� ������� ����
	int W, H;							// ���������� ������� ������� ����
	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		//return 0;
		return (X-L)*W/(R-L);
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		//return 0;
		return (T-Y)*H/(T-B);
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		//return 0.0;
		return (X / W * (R - L) + L);
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		//return 0.0;
		return (T - Y / H * (T - B));
	}
	double PolToDecX(double r, double a)		// ������� �� �������� ��������� � ������� (��� ��������)
	{

		return r * cos(a);
	}
	double PolToDecY(double r, double a)		// ������� �� �������� ��������� � ������� (��� ��������)
	{

		return r * sin(a);
	}
private:
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
public:
	Camera2D(double L, double R, double B, double T) : L(L), R(R), B(B), T(T)
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc, 0, 0, r.right, r.bottom);
		// ������� ������� ������� ����
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		W = r.right + 1;
		H = r.bottom + 1;
		double L1, R1, B1, T1;
		L1 = L;
		R1 = R;
		B1 = (B + T) / 2 - (R - L) / 2 * H / W;
		T1 = (B + T) / 2 + (R - L) / 2 * H / W;
		L = L1;
		R = R1;
		B = B1;
		T = T1;
		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� L, R, B, T ����� �������, ����� ���������� ���������� �������� �� ������������ ����
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
	}
	void LineTo(HDC dc, double X, double Y)
	{

		MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), NULL);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
	}
	void Axes(HDC dc)
	{

		MoveTo(L, 0.0);
		LineTo(dc, R, 0.0);
		MoveTo(0.0, T);
		LineTo(dc, 0.0, B);
		// ��������� ������������ ����
	}
	int Zoom(int delta, int x, int y) {
		double xx = ScreenToWorldX(x);
		double yy = ScreenToWorldX(x);	
		int del = delta >= 0 ? 1 : -1;
		if (R > 1 && T > 1 || del < 0)
		{
			L += del;
			R -= del;
			B += del;
			T -= del;
		}
		return del;
	}
};

#endif CAMERA_2D_H

