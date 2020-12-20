#pragma once

#include "ray.h"

// TODO: Should normals be unit length (it is convenient for shading)?
struct hit_record {
	point3 p;
	vec3 normal;
	double t;
};

// TODO: Change name of hittable to something else.
class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
