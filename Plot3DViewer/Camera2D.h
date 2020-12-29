#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double L, R, B, T;					// Мировые координаты границ рабочей области окна
	int W, H;							// Разрешение рабочей области окна
	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		//return 0;
		return (X-L)*W/(R-L);
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		//return 0;
		return (T-Y)*H/(T-B);
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		//return 0.0;
		return (X / W * (R - L) + L);
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		//return 0.0;
		return (T - Y / H * (T - B));
	}
	double PolToDecX(double r, double a)		// Переход от экранных координат к мировым (для абсциссы)
	{

		return r * cos(a);
	}
	double PolToDecY(double r, double a)		// Переход от экранных координат к мировым (для абсциссы)
	{

		return r * sin(a);
	}
private:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
public:
	Camera2D(double L, double R, double B, double T) : L(L), R(R), B(B), T(T)
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc, 0, 0, r.right, r.bottom);
		// Очистка рабочей области окна
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
		// Данная процедура вызывается при изменении размеров окна
		// В ней задаются значения величин W, H, а также настраиваются значения параметров L, R, B, T таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// Перемещение графического курсора (posX, posY)
		// Обратите внимание, что мы действуем в мировых координатах
	}
	void LineTo(HDC dc, double X, double Y)
	{

		MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), NULL);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
		// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
		// Обратите внимание, что мы действуем в мировых координатах
		// При отрисовке линии могут быть использованы WinApi функции
		// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
	}
	void Axes(HDC dc)
	{

		MoveTo(L, 0.0);
		LineTo(dc, R, 0.0);
		MoveTo(0.0, T);
		LineTo(dc, 0.0, B);
		// Отрисовка координатных осей
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

