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
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;
	virtual double pdf_value(const point3& o, const vec3& v) const {
		return 0.0;
	}

	virtual vec3 random(const vec3& o) const {
		return vec3(1, 0, 0);
	}
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

class rotate_y : public hittable {
public:
	// Constructor
	rotate_y(shared_ptr<hittable> p, double angle);

	// Functions
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
		output_box = bbox;
		return hasbox;
	}

public:
	shared_ptr<hittable> ptr;
	double sin_theta;
	double cos_theta;
	bool hasbox;
	aabb bbox;
};

rotate_y::rotate_y(shared_ptr<hittable> p, double angle) : ptr(p) {
	auto radians = degrees_to_radians(angle);
	sin_theta = sin(radians);
	cos_theta = cos(radians);
	hasbox = ptr->bounding_box(0, 1, bbox);

	point3 min(infinity, infinity, infinity);
	point3 max(-infinity, -infinity, -infinity);

	for (__int64 i = 0; i < 2; i++) {
		for (__int64 j = 0; j < 2; j++) {
			for (__int64 k = 0; k < 2; k++) {
				auto x = i * bbox.max().x() + (1 - i) * bbox.min().x();
				auto y = j * bbox.max().y() + (1 - j) * bbox.min().y();
				auto z = k * bbox.max().z() + (1 - k) * bbox.min().z();

				auto newx = (cos_theta * x) + (sin_theta * z);
				auto newz = (-sin_theta * x) + (cos_theta * z);

				vec3 tester(newx, y, newz);

				for (int c = 0; c < 3; c++) {
					min[c] = fmin(min[c], tester[c]);
					max[c] = fmax(max[c], tester[c]);
				}
			}
		}
	}

	bbox = aabb(min, max);
}

bool rotate_y::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	auto origin = r.origin();
	auto direction = r.direction();

	origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
	origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

	direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
	direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

	ray rotated_r(origin, direction, r.time());

	if (!(ptr->hit(rotated_r, t_min, t_max, rec))) {
		return false;
	}

	auto p = rec.p;
	auto normal = rec.normal;

	p[0] =  cos_theta * rec.p[0] + sin_theta * rec.p[2];
	p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

	normal[0] =  cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
	normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

	rec.p = p;
	rec.set_face_normal(rotated_r, normal);

	return true;
}

class flip_face : public hittable {
public:
	// Constructor
	flip_face(shared_ptr<hittable> p) : ptr(p) {}

	// Functions
	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec
	) const override {
		if (!ptr->hit(r, t_min, t_max, rec)) {
			return false;
		}
		else {
			rec.front_face = !rec.front_face;
			return true;
		}
	}

	virtual bool bounding_box(
		double time0, double time1, aabb& output_box
	) const override {
		return ptr->bounding_box(time0, time1, output_box);
	}

public:
	shared_ptr<hittable> ptr;
};