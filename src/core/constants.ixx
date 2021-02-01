export module arrt.core:constants;

// Modules
import :types;

import std.core;

// Constants
export namespace arrt {
	inline constexpr Float infinity = std::numeric_limits<Float>::infinity();
	inline constexpr Float pi = std::numbers::pi_v<Float>;
}