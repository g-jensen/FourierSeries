#pragma once

#include "FourierVector.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Math
{
public:
	static float Length(FourierVector v);
	static float Length(FourierVector v1, FourierVector v2);
	static FourierVector rotate(FourierVector vec, float angle_deg);
};

