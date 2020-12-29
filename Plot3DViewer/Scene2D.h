#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include "Model2D.h"
#include "Matrix.h"

class Scene2D : public Camera2D
{
private:
	typedef double(*Func)(double);
	Matrix<> Vertices;
	Matrix<int> Edges;
public:
	Model2D model;
	Scene2D(double L, double R, double B, double T, Model2D Model) : Camera2D(L, R, B, T), model(Model)
	{
	}
	double z=2;
	
	void Render(HDC dc)
	{

		Model2D tempmodel=model;
		if (model.Parametric == true)
		{
			tempmodel.Apply(Display2(z));
		}
		else {
			tempmodel.Apply(Display());
		}
		
		Edges = model.GetEdges();
		
		Axes(dc);
		
		double y;
		for (int i=1;i<=Edges.size_x;i++)
		{
			MoveTo(tempmodel.GetVertexX(Edges(i, 1)), tempmodel.GetVertexY(Edges(i, 1)));
			LineTo(dc, tempmodel.GetVertexX(Edges(i,2)), tempmodel.GetVertexY(Edges(i,2)));
			
		}
	}
};

#endif SCENE_2D_H