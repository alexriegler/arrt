#pragma once

#include "utility.h"

#include "hittable.h"
#include "onb.h"
#include "texture.h"

class material {
public:
	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& albedo, ray& scattered, double& pdf
	) const {
		return false;
	}

	virtual double scattering_pdf(
		const ray& r_in, const hit_record& rec, const ray& scattered
	) const {
		return 0;
	}

	virtual color emitted(double u, double v, const point3& p) const {
		return color(0, 0, 0);
	}
};

class lambertian : public material {
public:
	// Constructors
	lambertian(const color& a) : albedo(make_shared<solid_color>(a)) {}
	lambertian(shared_ptr<texture> a) : albedo(a) {}

	// Functions
	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& alb, ray& scattered, double& pdf
	) const override {
		onb uvw;
		// TODO: Should this be the constructor?
		uvw.build_from_w(rec.normal);
		auto direction = uvw.local(random_cosine_direction());
		scattered = ray(rec.p, unit_vector(direction), r_in.time());
		alb = albedo->value(rec.u, rec.v, rec.p);
		pdf = dot(uvw.w(), scattered.direction()) / pi;
		return true;
	}

	virtual double scattering_pdf(
		const ray& r_in, const hit_record& rec, const ray& scattered
	) const override {
		auto cosine = dot(rec.normal, unit_vector(scattered.direction()));
		return cosine < 0 ? 0 : cosine / pi;
	}

public:
	shared_ptr<texture> albedo;
};

//class metal : public material {
//public:
//	// Constructor
//	metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
//
//	// Member functions
//	virtual bool scatter(
//		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
//	) const override {
//		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
//		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time());
//		attenuation = albedo;
//		return (dot(scattered.direction(), rec.normal) > 0);
//	}
//
//public:
//	color albedo;
//	double fuzz;	// TODO: Rename fuzz to something more descriptive.
//};
//
//class dielectric : public material {
//public:
//	// Constructor
//	dielectric(double index_of_refraction) : ir(index_of_refraction) {}
//
//	// Member functions
//	virtual bool scatter(
//		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
//	) const override {
//		attenuation = color(1.0, 1.0, 1.0);
//		double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
//
//		vec3 unit_direction = unit_vector(r_in.direction());
//		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
//		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
//
//		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
//		vec3 direction;
//
//		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
//			direction = reflect(unit_direction, rec.normal);
//		}
//		else {
//			direction = refract(unit_direction, rec.normal, refraction_ratio);
//		}
//
//		scattered = ray(rec.p, direction, r_in.time());
//		return true;
//	}
//
//public:
//	double ir;	// Index of Refraction
//
//private:
//	static double reflectance(double cosine, double ref_idx) {
//		// Use Shlick's approximation for reflectance.
//		auto r0 = (1 - ref_idx) / (1 + ref_idx);
//		r0 = r0 * r0;
//		return r0 + (1 - r0) * pow((1 - cosine), 5); 
//	}
//};

class diffuse_light : public material {
public:
	// Constructors
	diffuse_light(shared_ptr<texture> a) : emit(a) {}
	diffuse_light(color c) : emit(make_shared<solid_color>(c)) {}

	// Member functions
	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered, double& pdf
	) const override {
		return false;
	}

	// TODO: Could also add emit function to hit_record instead.
	virtual color emitted(double u, double v, const point3& p) const override {
		return emit->value(u, v, p);
	}

public:
	shared_ptr<texture> emit;
};

//class isotropic : public material {
//public:
//	// Constructors
//	isotropic(color c) : albedo(make_shared<solid_color>(c)) {}
//	isotropic(shared_ptr<texture> a) : albedo(a) {}
//
//	// Function
//	virtual bool scatter(
//		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
//	) const override {
//		scattered = ray(rec.p, random_in_unit_sphere(), r_in.time());
//		attenuation = albedo->value(rec.u, rec.v, rec.p);
//		return true;
//	}
//
//public:
//	shared_ptr<texture> albedo;
//};
