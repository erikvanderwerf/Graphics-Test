#pragma once

#include <math.h>

template <typename T>
double magnitude(T vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

template <typename T>
T normalize(T vector)
{
	float mag = (float)magnitude(vector);
	if (0.0 == mag) {
		return T(0, 0);
	}
	else {
		return T(vector.x / mag, vector.y / mag);	
	}
}

template <typename T>
T normalize(T vector, float to)
{
	float mag = (float)magnitude(vector);
	if (0.0 == mag) {
		return T(0, 0);
	}
	else {
		return T(to * vector.x / mag, to * vector.y / mag);
	}
}

template <typename T>
T maximize(T vector, float to)
{
	float mag = (float)magnitude(vector);
	if (mag > to) {
		return normalize(vector, to);
	}
	else {
		return vector;
	}
}