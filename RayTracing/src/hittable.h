#pragma once

#include "utility.h"

#include "aabb.h"

class material;

// TODO: Normals are unit length (it is convenient for shading); should they be?
struct hit_record {
	point3 p;
	vec3 normal;
	shared_ptr<material> mat_ptr;
	double t;
	bool front_face;

	// TODO: Normals can either always point outward from surface or always point against the incident ray.
	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

// TODO: Change name of hittable to something else.
class hittable {
public:
	// TODO: Use std::optional output instead of output parameter (hit and bounding_box).
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;
};
