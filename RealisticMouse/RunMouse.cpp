#include "RunMouse.h"

#include <Windows.h>
#include <random>
//#include <iostream>

//Random Number Generator
int RunMouse::Random(int lowerBound, int upperBound){
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
	std::mt19937 engine(rd()); // Mersenne twister MT19937
	int value = distribution(engine);
	return value;
}

//Standard mouse move function via SendInput
void RunMouse::MouseMoveInternal(float x, float y){
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);
	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);

	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;
	::SendInput(1, &Input, sizeof(INPUT));
}

void RunMouse::MoveMouse(int x, int y){
	//Accuracy to desired pixel
	int Acc = 3;

	int targetX = x + (int)(Acc * targetDistribution.NextGaussian());
	int targetY = y + (int)(Acc * targetDistribution.NextGaussian());

	//Declare the original pointer position
	POINT p;
	GetCursorPos(&p);
	int originalX = (int) p.x;
	int originalY = (int) p.y;

	//Find a mid point between original and target position
	int midPointX = (x - targetX) / 2;
	int midPointY = (y - targetY) / 2;

	//Points normal to the straight line between start and end point
	int factor = 6;
	int bezierMidPointX = (int)((midPointX / factor) * (midpointDistribution.NextGaussian()));
	int bezierMidPointY = (int)((midPointY / factor) * (midpointDistribution.NextGaussian()));

	BezierCurve bc;
	double input[] = { originalX, originalY, bezierMidPointX, bezierMidPointY, targetX, targetY };

	//Change numberOfPoints for more or less control points
	const int numberOfPoints = 500;

	//Don't change numberOfDataPoints
	const int numberOfDataPoints = numberOfPoints*2;
	double output[numberOfDataPoints];

	//control points are couplets of two so / 2
	bc.Bezier2D(input, numberOfDataPoints / 2, output);

	/*for (int i = 0; i < 1000; i++){

		std::cout << output[i] << std::endl;

	}*/

	//std::vector<POINT> points;
	POINT A;

	for (int count = 1; count != numberOfDataPoints - 1; count += 2)
	{
		A.x = (int)output[count + 1];
		A.y = (int)output[count];

		//points.push_back(A);

		MouseMoveInternal( (float) A.x, (float) A.y);

		////Testing - sleep for a vaule between 0-20
		Sleep(Random(0, 20));
		////

	}

	//return points;
}

RunMouse::RunMouse(){};
RunMouse::~RunMouse(){};