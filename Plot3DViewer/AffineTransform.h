#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

Matrix<> Translation(double x, double y,double z)
{
	double T[16] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
	    0, 0, 0, 1};
	return Matrix<>(4, 4, T);
}

Matrix<> Identity()
{
	double I[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
	    0, 0, 0, 1};
	return Matrix<>(4, 4, I);
}
Matrix<> RotationY(double t)
{
	double I[16] = {
		 cos(t), 0, sin(t), 0,
		 0, 1, 0, 0,
		-sin(t),0, cos(t), 0,
		0, 0, 0, 1 };
	return Matrix<>(4, 4, I);
}
Matrix<> RotationX(double t)
{
	double I[16] = {
		 1, 0, 0, 0,
		 0, cos(t), -sin(t), 0,
		0,sin(t), cos(t), 0,
		0,0, 0, 1 };
	return Matrix<>(4, 4, I);
}
Matrix<> RotationZ(double t)
{
	double I[16] = {
		 cos(t), -sin(t),0, 0,
		sin(t), cos(t),0, 0,
         0, 0, 1, 0,
		0, 0, 0, 1 };
	return Matrix<>(4, 4, I);
}
Matrix<> RotationY2(double cos, double sin)
{
	double I[16] = {
		 cos, 0, sin, 0,
		 0, 1, 0, 0,
		-sin,0, cos, 0,
		0, 0, 0, 1 };
	return Matrix<>(4, 4, I);
}
Matrix<> RotationX2(double cos, double sin)
{
	double I[16] = {
		 1, 0, 0, 0,
		 0, cos, -sin, 0,
		0,sin, cos, 0,
		0,0, 0, 1 };
	return Matrix<>(4, 4, I);
}
Matrix<> RotationZ2(double cos, double sin)
{
	double I[16] = {
		 cos, -sin,0, 0,
		sin, cos,0, 0,
		 0, 0, 1, 0,
		0, 0, 0, 1 };
	return Matrix<>(4, 4, I);
}

Matrix<> Display()
{
	double I[12] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1 };
	return Matrix<>(3, 4, I);
}
Matrix<> Display2(double d)
{
	double I[12] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, -1/d, 1 };
	return Matrix<>(3, 4, I);
}
Matrix<> ReturnDisplay(double d)
{
	double I[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 1/d, 1 };
	return Matrix<>(4, 4, I);
}

Matrix<> Scaling(int kx, int ky,int kz)
{
	double I[16] = {
		 kx , 0, 0,0,
		 0, ky, 0, 0,
		 0, 0, kz, 0,
		 0, 0, 0, 1 };
	return Matrix<>(4, 4, I);
}
Matrix<> Reflection()
{
	double I[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	return Matrix<>(4, 4, I);
}
#endif AFFINE_TRANSFORM_H
// ����� ��������� ����������� �������, ������������ ������� ������� ��:
// Identity() - ������������� ��;
// Rotation(t) - ������� �� ���� t;
// Rotation(c, s) - ������� �� ����, ������� � ����� �������� ��������������� ��������� c � s;
// Scaling(kx, ky) - ���������������;
// Mapping (��������� ���� ���������) - �� �������, ��� �������� ������ ��������� ����� ������������ ������� Scaling.

// � ���������� ������� ������������ ����������� ������� �� ������.
// �������������� ���� � ������ �������� �������� ������.
// ��������, ����� �������, ��������� ��������� �������,
// � ����������� ���������������� ��������� � �������������.