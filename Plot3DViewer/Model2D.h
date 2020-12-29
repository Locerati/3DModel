#ifndef MODEL_2D_H
#define MODEL_2D_H

#include <string>
#include <fstream>
#include "Matrix.h"
#include "AffineTransform.h"

class Model2D
{
private:
	Matrix<> Vertices;
	Matrix<int> Edges;
	Matrix<> ComulativeAT;
	Matrix<> InitialVertices;
public:
	Model2D() : Vertices(), Edges(), ComulativeAT(Identity()), InitialVertices(Vertices)  {}
	Model2D(const Matrix<> Vertices, const Matrix<int> Edges) :
		Vertices(Vertices), Edges(Edges), ComulativeAT(Identity()), InitialVertices(Vertices) {}
	Model2D(string, string);
	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }
	bool Parametric=false;
	double GetVertexX(int);
	double GetVertexY(int);
	double GetVertexMainX(int);
	double GetVertexMainY(int);
	double GetVertexMainZ(int);
	void Apply(Matrix<>);
	void Copy(Matrix<>, Matrix<int>);
};

void Model2D::Copy(Matrix<> vertices, Matrix<int> edges)
{
	Vertices = vertices;
	Edges = edges;

}

Model2D::Model2D(string path1, string path2)
{
	string line;

	ifstream in(path1); // окрываем файл для чтения
	ifstream in2(path2); // окрываем файл для чтения
	if (in.is_open() && in2.is_open())
	{
		int numberVertices;
		in >> numberVertices;
		Matrix<> V(4, numberVertices);
		in >> V;
		Vertices = V;
		 

		 int numberVectrors;
		 in2 >> numberVectrors;
		 Matrix<int> E(numberVectrors, 2);
		 in2 >> E;
		 Edges = E;


	}
	in.close();
	in2.close();// закрываем файл
}

double Model2D::GetVertexX(int p)
{
	return Vertices(1,p)/ Vertices(3,p);
}

double Model2D::GetVertexY(int p)
{
	return Vertices(2, p) / Vertices(3, p);
}
double Model2D::GetVertexMainX(int p)
{
	return Vertices(1, p) / Vertices(4, p);
}

double Model2D::GetVertexMainY(int p)
{
	return Vertices(2, p) / Vertices(4, p);
}
double Model2D::GetVertexMainZ(int p)
{
	return Vertices(3, p) / Vertices(4, p);
}



void Model2D::Apply(Matrix<>T)
{
	Vertices =T* Vertices;
	
}

#endif MODEL_2D_H