#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);

	static constexpr float PI = M_PI;
};

