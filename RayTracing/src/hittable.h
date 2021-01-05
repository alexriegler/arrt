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
	double u;
	double v;
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

class translate : public hittable {
public:
	// Constructor
	translate(shared_ptr<hittable> p, const vec3& displacement)
		: ptr(p), offset(displacement) {}

	// Functions
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

public:
	shared_ptr<hittable> ptr;
	vec3 offset;
};

bool translate::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	ray moved_r(r.origin() - offset, r.direction(), r.time());
	if (!(ptr->hit(moved_r, t_min, t_max, rec))) {
		return false;
	}

	rec.p += offset;
	rec.set_face_normal(moved_r, rec.normal);

	return true;
}

bool translate::bounding_box(double time0, double time1, aabb& output_box) const {
	if (!(ptr->bounding_box(time0, time1, output_box))) {
		return false;
	}

	output_box = aabb(output_box.min() + offset, output_box.max() + offset);

	return true;
}
