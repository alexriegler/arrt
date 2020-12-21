#pragma once

#include "utility.h"

class material;

// TODO: Should normals be unit length (it is convenient for shading)?
struct hit_record {
	point3 p;
	vec3 normal;
	shared_ptr<material> mat_ptr;
	double t{};
	bool front_face{};

	// TODO: Normals can either always point outward from surface or always point against the incident ray.
	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

// TODO: Change name of hittable to something else.
class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
