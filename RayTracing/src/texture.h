#pragma once

#include "utility.h"

#include "perlin.h"

// TODO: Optionally could keep constant colors and textures in separate classes.
class texture {
public:
	virtual color value(double u, double v, const point3& p) const = 0;
};

class solid_color : public texture {
public:
	// Constructors
	solid_color() = default;
	solid_color(color c) : color_value(c) {}

	solid_color(double red, double green, double blue) 
		: solid_color(color(red, green, blue)) {}

	// Member function
	virtual color value(double u, double v, const point3& p) const override {
		return color_value;
	}

private:
	color color_value;
};

class checker_texture : public texture {
public:
	// Constructors
	checker_texture() = default;

	checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd)
		: even(_even), odd(_odd) {}

	checker_texture(color c1, color c2)
		: even(make_shared<solid_color>(c1)), odd(make_shared<solid_color>(c2)) {}

	// Member function
	virtual color value(double u, double v, const point3& p) const override {
		auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
		if (sines < 0) {
			return odd->value(u, v, p);
		}
		else {
			return even->value(u, v, p);
		}
	}

public:
	shared_ptr<texture> odd;
	shared_ptr<texture> even;
};

class noise_texture : public texture {
public:
	// Constructors
	noise_texture() = default;
	noise_texture(double sc) : scale(sc) {}

	// Member function
	virtual color value(double u, double v, const point3& p) const override {
		// TODO: Rename perlin noise so we don't have noise.noise.
		return color(1, 1, 1) * noise.turb(scale * p);
		
		// Marbled pattern:
		// return color(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p)));
	}

public:
	perlin noise;
	double scale;
};
