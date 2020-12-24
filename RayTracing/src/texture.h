#pragma once

#include "utility.h"

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

	// Member functions
	virtual color value(double u, double v, const point3& p) const override {
		return color_value;
	}

private:
	color color_value;
};
