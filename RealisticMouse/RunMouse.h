#ifndef __Mouse_H__
#define __Mouse_H__

#include "Normal.h"
#include "BezierCurve.h"

class RunMouse
{
private:
	Normal targetDistribution;
	Normal midpointDistribution;

	int Random(int lowerBound, int upperBound);
	void MouseMoveInternal(float x, float y);

public:
	void MoveMouse(int x, int y);

	RunMouse();
	~RunMouse();

};

#endif