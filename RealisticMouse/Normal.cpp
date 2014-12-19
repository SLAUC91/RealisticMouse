#include "Normal.h"

#include <Windows.h>
#include <math.h>
#include <time.h>

double Normal::NextGaussian()
{
	srand(time(NULL));
	static double v, fac;
	static int phase = 0;
	double S, Z, U1, U2, u;

	if (phase)
		Z = v * fac;
	else
	{
		do
		{
			U1 = (double)rand() / RAND_MAX;
			U2 = (double)rand() / RAND_MAX;

			u = 2. * U1 - 1.;
			v = 2. * U2 - 1.;
			S = u * u + v * v;
		} while (S >= 1 || S == 0);

		fac = sqrt(-2. * log(S) / S);
		Z = u * fac;
	}

	phase = 1 - phase;

	return Z;
}

Normal::Normal(){}