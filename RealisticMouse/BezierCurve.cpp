#include "BezierCurve.h"

#include <iostream>
#include <math.h>

BezierCurve::BezierCurve(){
	BezierCurve::CreateFactorialTable();
}

double BezierCurve::factorial(int n)
{
	if (n < 0) { std::cout << "n is less than 0" << std::endl; }
	if (n > 32) { std::cout << "n is greater than 32" << std::endl; }

	return Table[n]; //returns the value n! as a approx. point number
}

void BezierCurve::CreateFactorialTable()
{
	Table[0] = 1.0;
	Table[1] = 1.0;
	Table[2] = 2.0;
	Table[3] = 6.0;
	Table[4] = 24.0;
	Table[5] = 120.0;
	Table[6] = 720.0;
	Table[7] = 5040.0;
	Table[8] = 40320.0;
	Table[9] = 362880.0;
	Table[10] = 3628800.0;
	Table[11] = 39916800.0;
	Table[12] = 479001600.0;
	Table[13] = 6227020800.0;
	Table[14] = 87178291200.0;
	Table[15] = 1307674368000.0;
	Table[16] = 20922789888000.0;
	Table[17] = 355687428096000.0;
	Table[18] = 6402373705728000.0;
	Table[19] = 121645100408832000.0;
	Table[20] = 2432902008176640000.0;
	Table[21] = 51090942171709440000.0;
	Table[22] = 1124000727777607680000.0;
	Table[23] = 25852016738884976640000.0;
	Table[24] = 620448401733239439360000.0;
	Table[25] = 15511210043330985984000000.0;
	Table[26] = 403291461126605635584000000.0;
	Table[27] = 10888869450418352160768000000.0;
	Table[28] = 304888344611713860501504000000.0;
	Table[29] = 8841761993739701954543616000000.0;
	Table[30] = 265252859812191058636308480000000.0;
	Table[31] = 8222838654177922817725562880000000.0;
	Table[32] = 263130836933693530167218012160000000.0;
}

double BezierCurve::Ni(int n, int i)
{
	double ni;
	double a1 = BezierCurve::factorial(n);
	double a2 = BezierCurve::factorial(i);
	double a3 = BezierCurve::factorial(n - i);
	ni = a1 / (a2 * a3);
	return ni;
}

// Calculate Bernstein basis
double BezierCurve::Bernstein(int n, int i, double t)
{
	double basis;
	double t_i;		// t^i
	double t_ni;	// (1 - t)^i 

	//Make sure pow is right

	if (t == 0.0 && i == 0)
		t_i = 1.0;
	else
		t_i = pow(t, i);

	if (n == i && t == 1.0)
		t_ni = 1.0;
	else
		t_ni = pow((1 - t), (n - i));

	//Bernstein basis
	basis = Ni(n, i) * t_i * t_ni;
	return basis;
}

void BezierCurve::Bezier2D(double b[], int ControlPoints, double p[])
{
	int sizeB = 6;
	int j = (sizeB) / 2;

	int icount, jcount;
	double step, t;

	// Calculate points on curve

	icount = 0;
	t = 0;
	step = (double)1.0 / (ControlPoints - 1);

	for (int i1 = 0; i1 != ControlPoints; i1++)
	{
		if ((1.0 - t) < 5e-6)
			t = 1.0;

		jcount = 0;
		p[icount] = 0.0;
		p[icount + 1] = 0.0;

		for (int i = 0; i != j; i++)
		{
			double basis = Bernstein(j - 1, i, t);
			p[icount] += basis * b[jcount];
			p[icount + 1] += basis * b[jcount + 1];
			jcount = jcount + 2;
		}

		icount += 2;
		t += step;
	}
}