module;

#include <limits>
#include <numbers>
#include <random>

export module arrt.utility;

namespace arrt {
	// Typedefs
	#ifdef ARRT_FLOAT_AS_DOUBLE
		export typedef double Float;
	#else
		export typedef float Float;
	#endif // ARRT_FLOAT_AS_DOUBLE

	// Constants
	export inline constexpr Float infinity = std::numeric_limits<Float>::infinity();
	export inline constexpr Float pi = std::numbers::pi_v<Float>;

	// Utility functions
	// Converts a given degree value to radians.
	export constexpr Float degrees_to_radians(Float degrees) {
		return degrees * pi / static_cast<Float>(180.0);
	}

	// Returns a random float in the range [0, 1).
	export inline Float random_float() {
		static std::uniform_real_distribution<Float> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	// Returns a random float in the range [min, max).
	export inline Float random_float(Float min, Float max) {
		return min + (max - min) * random_float();
	}

	// Returns a random integer in [min, max].
	export inline int random_int(int min, int max) {
		return static_cast<int>(random_float(static_cast<Float>(min), static_cast<Float>(max + 1)));
	}

	// Constrains x between min and max.
	export constexpr Float clamp(Float x, Float min, Float max) {
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

	// Checks if x is not a number.
	export template <typename T>
	inline bool is_nan(const T x) {
		return std::isnan(x);
	}

	// Checks if x is not a number.
	export template <>
	inline bool is_nan(const int x) {
		return false;
	}
}