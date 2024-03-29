#pragma once

#include "vec3.h"

class ray {
public:
	// Constructors
	ray() = default;
	ray(const point3& origin, const vec3& direction, double time = 0.0)
		: orig(origin), dir(direction), tm(time)
	{}

	// Member functions
	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }
	double time() const { return tm; }

	point3 at(double t) const {
		return orig + t * dir;
	}

	// TODO: Make private?
public:
	point3 orig;
	vec3 dir;
	double tm;
};