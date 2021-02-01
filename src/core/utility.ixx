export module arrt.utility;

// Headers

// Modules
import arrt.constants;
import arrt.types;

import std.core;

// Functions
export namespace arrt {
	// Converts a given degree value to radians.
	constexpr Float degrees_to_radians(Float degrees) {
		return degrees * pi / static_cast<Float>(180.0);
	}

	// Returns a random float in the range [0, 1).
	inline Float random_float() {
		static std::uniform_real_distribution<Float> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	// Returns a random float in the range [min, max).
	inline Float random_float(Float min, Float max) {
		return min + (max - min) * random_float();
	}

	// Returns a random integer in [min, max].
	inline int random_int(int min, int max) {
		return static_cast<int>(random_float(static_cast<Float>(min), static_cast<Float>(max + 1)));
	}

	// Constrains x between min and max.
	constexpr Float clamp(Float x, Float min, Float max) {
		if (x < min) {
			return min;
		}
		else if (x > max) {
			return max;
		}
		else {
			return x;
		}
	}
}