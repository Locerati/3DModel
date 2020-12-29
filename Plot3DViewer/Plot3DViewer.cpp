#include <windows.h>
#include <windowsx.h>
#include <string>
#include "Data.h"
#include "Scene2D.h"


#define moveCoeff	0.1
#define	scalCoeff	0.05
#define	rotateCoeff	0.1
#define	distCoeff	1

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основная процедура
{
	// Первая составляющая часть основной процедуры - создание окна: сначала описывается оконный класс wc, затем создаётся окно hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// имя оконной процедуры, закрепленной за данным классом
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// идентификатор приложения, содержащий адрес начала выделенной ему области памяти
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// имя оконного класса, используемое при создании экземпляров окна
	RegisterClass(&wc);								// регистрация класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функция создания окна заполняет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// имя оконного класса
		//(LPCSTR)"Plot2D Viewer",					// заголовок окна
		(LPCSTR)"Lab3 - 3D Engine",
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200,200,400,400,							// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// Вторая составляющая часть основной процедуры - основной цикл обработки системных сообщений, который ожидает сообщения и рассылает их соответствующим окнам
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// функция GetMessage выбирает из очереди сообщение и заносит его в структуру msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// функция DispatchMessage оповещает систему о необходимости вызова оконной процедуры
	}

	return 0;
}

// В основном модуле объявляется только одна глобальная переменная - создаётся объект класса Scene2D
// Все дальнейшие действия осуществляются посредством обращения к методам, реализованным в этом классе
//Scene2D scene(L,R,B,T);
//Scene2D scene(L, R, B, T, NULL);

/**/

double v[16] = { 3.0, 1.0,-1.0,-3.0,
                 0.5, 1.0, 1.0,  0.5,
				 1, -1, 1,  -1,
	             1.0, 1.0,1.0,1.0};
Matrix<double>V(4, 4, v);
int e[6] = { 0, 1, 1, 2, 2, 3 };
Matrix<int>E(3, 2, e);
Model2D model("Vertices.txt", "Vectors.txt");

/*
Model2D model("vertices.txt", "edges.txt");
*/
Scene2D scene(L, R, B, T, model);



LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
{
	switch(msg)
	{

	case WM_PAINT:
		{
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);				// Вызов реализованного в классе Camera2D метода, отвечающего за очистку рабочей области окна hWnd
			//scene.Plot(dc, Sinusoid);		// Вызов реализованного в классе Scene2D метода, отвечающего за отрисовку графика синусоиды
			scene.Render(dc);
			ReleaseDC(hWnd,dc);
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}

	case WM_SIZE:
		{
			HDC dc = GetDC(hWnd);
			scene.SetResolution(dc);
			ReleaseDC(hWnd,dc);
			InvalidateRect(hWnd,nullptr,false);
			return 0;
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_MOUSEWHEEL:
	{
		
		POINT P;
		P.x = GET_X_LPARAM(lParam);
		P.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &P);
		
		int Delta = GET_WHEEL_DELTA_WPARAM(wParam);
		if (scene.z != 0 || Delta > 0)
		{
			int del = scene.Zoom(Delta, P.x, P.y);
			scene.z += del;
			InvalidateRect(hWnd, nullptr, false);
		}
		break;
	}
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_UP:
				{
					scene.model.Apply(Translation(0, 1,0));
					break;
				}
			case VK_DOWN:
				{
				scene.model.Apply(Translation(0, -1,0));
					break;
				}
			case VK_LEFT:
				{
				  scene.model.Apply(Translation(-1, 0,0));
					break;
				}
			case VK_RIGHT:
				{
				scene.model.Apply(Translation(1, 0,0));
					break;
				}
			case 'P':
			{
				scene.model.Parametric=true;
				break;
			}
			case 'O':
			{
				scene.model.Parametric = false;
				break;
			}
			case 'E':
			{
				scene.model.Apply(RotationX(1));
				break;
			}
			case 'Q':
			{
				scene.model.Apply(RotationY(-1));
				break;
			}
			case 'S':
			{
				scene.model.Apply(Scaling(2,2,2));
				break;
			}
			case'X':
			{
				double X1 = scene.model.GetVertexMainX(1);
				double Y1 = scene.model.GetVertexMainY(1);
				double Z1 = scene.model.GetVertexMainZ(1);

				double X2 = scene.model.GetVertexMainX(4);
				double Y2 = scene.model.GetVertexMainY(4);
				double Z2 = scene.model.GetVertexMainZ(4);
				scene.model.Apply(Translation(-X1, -Y1, -Z1));

				double A = X2 - X1;
				double B = Y2 - Y1;
				double C = Z2 - Z1;
				double d = B / sqrt(B * B + C * C);
				
				double d1 = -C / sqrt(B * B + C * C);
				
				if (sqrt(B * B + C * C)!=0 && sqrt(B * B + C * C) != 0)
				scene.model.Apply(RotationX2(B/sqrt(B*B+C*C),-C/sqrt(B*B+C*C)));
				ofstream off("Output2.txt");
				off << scene.model.GetVertices();
				if (sqrt(A * A + B * B + C * C) != 0 && sqrt(A * A + B * B + C * C) != 0)
				scene.model.Apply(RotationZ2(A / sqrt(A*A+B* B + C * C), -sqrt(B*B+C*C) / sqrt(A * A + B * B + C * C)));


				scene.model.Apply(RotationX(1));
				if (sqrt(A * A + B * B + C * C) != 0 && sqrt(A * A + B * B + C * C) != 0)
				scene.model.Apply(RotationZ2(A / sqrt(A *A + B * B + C * C), sqrt(B* B + C * C) / sqrt(A * A + B * B + C * C)));
				if (sqrt(B * B + C * C) != 0 && sqrt(B * B + C * C) != 0)
				scene.model.Apply(RotationX2(B / sqrt(B * B + C * C), C / sqrt(B * B + C * C)));


				scene.model.Apply(Translation(X1, Y1, Z1));
				break;
			}
			case'V':
			{
				
				scene.model.Apply(RotationZ(-1));
				break;
			}
			
			case 0x57: //W
				{
					
					break;
				}			
			}
			InvalidateRect(hWnd, NULL, false);
			return 0;
		}

	default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}
	return 0;
}
