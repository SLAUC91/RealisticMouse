#ifndef __Bez_H__
#define __Bez_H__

class BezierCurve
{
private:
	double Table[33];
	double factorial(int n);
	void CreateFactorialTable();
	double Ni(int n, int i);
	double Bernstein(int n, int i, double t);

public:
	BezierCurve();
	void Bezier2D(double b[], int cpts, double p[]);
};

#endif