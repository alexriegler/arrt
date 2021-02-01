export module arrt.constants;

// Modules
import arrt.types;

import std.core;

// Constants
export namespace arrt {
	inline constexpr Float infinity = std::numeric_limits<Float>::infinity();
	inline constexpr Float pi = std::numbers::pi_v<Float>;
}