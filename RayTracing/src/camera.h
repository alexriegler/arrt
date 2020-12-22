#pragma once

#include "utility.h"

// TODO: Look into stratification for antialiasing.
// TODO: You could define a direction to look in instead of a point to look at.
class camera {
public:
	// Constructors
	camera(
		point3 lookfrom,
		point3 lookat,
		vec3 vup,
		double vfov,	// vertical field-of-view in degrees
		double aspect_ratio
	) {
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h;
		auto viewport_width = aspect_ratio * viewport_height;
		
		auto w = unit_vector(lookfrom - lookat);
		auto u = unit_vector(cross(vup, w));
		auto v = cross(w, u);

		origin = lookfrom;
		horizontal = viewport_width * u;
		vertical = viewport_height * v;
		lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - w;
	}

	// Member functions
	ray get_ray(double s, double t) const {
		return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
	}

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};
