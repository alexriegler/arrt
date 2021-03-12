module;

// #include <concepts>
#include <cmath>
#include <cassert>
#include <iostream>

export module arrt.vector;

import arrt.core;

namespace arrt {
	// Vector3
	// TODO: T is only Float or int; enforce with concept.
	export
	template <typename T>
	struct Vector3 {
		// Constructors
		Vector3() : x(0), y(0), z(0) {}
		Vector3(T x, T y, T z) : x(x), y(y), z(z) { assert(!has_nans()); }

		// Assignments
		
		// Destructor
		
		// Functions
		constexpr bool has_nans() const { return is_nan(x) || is_nan(y) || is_nan(z); }

		constexpr bool operator==(const Vector3<T>& v) const = default;

		constexpr T operator[](int i) const {
			assert(i >= 0 && i <= 2);
			if (i == 0) { return x; }
			if (i == 1) { return y; }
			return z;
		}

		constexpr T& operator[](int i) {
			assert(i >= 0 && i <= 2);
			if (i == 0) { return x; }
			if (i == 1) { return y; }
			return z;
		}

		constexpr Vector3<T> operator+(const Vector3<T>& v) const {
			assert(!v.has_nans());
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		constexpr Vector3<T>& operator+=(const Vector3<T>& v) const {
			assert(!v.has_nans());
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		constexpr Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }

		constexpr Vector3<T> operator-(const Vector3<T>& v) const {
			assert(!v.has_nans());
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		constexpr Vector3<T> operator-=(const Vector3<T>& v) const {
			assert(!v.has_nans());
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		template <typename U>
		constexpr Vector3<T> operator*(U scalar) const {
			return Vector3(scalar * x, scalar * y, scalar * z);
		}

		template <typename U>
		constexpr Vector3<T>& operator*=(U scalar) {
			assert(!is_nan(scalar));
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		template <typename U>
		constexpr Vector3<T> operator/(U fraction) const {
			assert(fraction != 0);
			Float inverse = 1 / static_cast<Float>(fraction);
			return Vector3<T>(x * inverse, y * inverse, z * inverse);
		}

		template <typename U>
		constexpr Vector3<T>& operator/=(U fraction) {
			assert(fraction != 0);
			Float inverse = 1 / static_cast<Float>(fraction);
			x *= inverse;
			y *= inverse;
			z *= inverse;
			return *this;
		}

		constexpr Float length_squared() const { return x * x + y * y + z * z; }
		constexpr Float length() const { return std::sqrt(length_squared()); }

		// Data
		T x;
		T y;
		T z;
	};

	// Typedefs
	export typedef Vector3<Float> Vector3f;
	export typedef Vector3<int> Vector3i;
	
	// Vector3 inline functions
	export {
		template <typename T, typename U>
		constexpr Vector3<T> operator*(U lhs_scalar, const Vector3<T>& rhs_v) {
			return rhs_v * lhs_scalar;
		}

		// TODO: Should this be constexpr? Does it make sense?
		template <typename T>
		constexpr std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
			os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
			return os;
		}

		// TODO: Does Float need a special print case?
		/*template <>
		inline std::ostream& operator<<(std::ostream& os, const Vector3<Float>& v) {
			os << StringPrintf("[ %f, %f, %f ]", v.x, v.y, v.z);
			return os;
		}*/

		// Gets the absolute value of the vector.
		template <typename T>
		constexpr Vector3<T> abs(const Vector3<T>& v) {
			return Vector3<T>(std::abs((v.x), std::abs(v.y), std::abs(v.z)));
		}

		// Calculates the the dot product between the two vectors.
		template <typename T>
		constexpr T dot(const Vector3<T>& v1, const Vector3<T>& v2) {
			assert(!v1.has_nans() && !v2.has_nans());
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		// Calculates the absolute value of the dot product between the two vectors.
		template <typename T>
		constexpr T abs_dot(const Vector3<T>& v1, const Vector3<T>& v2) {
			assert(!v1.has_nans() && !v2.has_nans());
			return std::abs(dot(v1, v2));
		}

		// Calculates the cross product between the two vectors.
		template <typename T>
		constexpr Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2) {
			assert(!v1.has_nans() && !v2.has_nans());
			// The vector elements are converted to double-precision (regardless of the
			// type of Float) before the subtractions in the Cross() function. Using 
			// extra precision for 32-bit floating-point values here protects against 
			// error from catastrophic cancellation, a type of floating-point error that
			// can happen when subtracting two values that are very close together.
			// http://www.pbr-book.org/3ed-2018/Geometry_and_Transformations/Vectors.html
			double v1x = v1.x;
			double v1y = v1.y;
			double v1z = v1.z;
			double v2x = v2.x;
			double v2y = v2.y;
			double v2z = v2.z;
			return Vector3<T>(
				(v1y * v2z) - (v1z * v2y),
				(v1z * v2x) - (v1x * v2z),
				(v1x * v2y) - (v1y * v2x));
		}

		// Normalizes a vector; does not normalize the vector in place.
		template <typename T>
		constexpr Vector3<T> normalize(const Vector3<T>& v) {
			return v / v.length();
		}

		// Returns the smallest coordinate value.
		template <typename T>
		constexpr T min_component(const Vector3<T>& v) {
			return std::min(v.x, std::min(v.y, v.z));
		}

		// Returns the largest coordinate value.
		template <typename T>
		constexpr T max_component(const Vector3<T>& v) {
			return std::max(v.x, std::max(v.y, v.z));
		}

		// Returns the index of the component with the largest value.
		template <typename T>
		constexpr int max_dimension(const Vector3<T>& v) {
			return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) :
				((v.y > v.z) ? 1 : 2);
		}

		// Returns a vector that is the result of the component-wise minimums.
		template <typename T>
		constexpr Vector3<T> min(const Vector3<T>& v1, const Vector3<T>& v2) {
			return Vector3<T>(
				std::min(v1.x, v2.x),
				std::min(v1.y, v2.y),
				std::min(v1.z, v2.z));
		}

		// Returns a vector that is the result of the component-wise maximums.
		template <typename T>
		constexpr Vector3<T> max(const Vector3<T>& v1, const Vector3<T>& v2) {
			return Vector3<T>(
				std::max(v1.x, v2.x),
				std::max(v1.y, v2.y),
				std::max(v1.z, v2.z));
		}

		// Permutes the coordinate values according to the index values provided.
		template <typename T>
		constexpr Vector3<T> permute(const Vector3<T>& v, int x, int y, int z) {
			return Vector3<T>(v[x], v[y], v[z]);
		}

		// TODO: Do I need this function?
		// Assumes that v1 is normalized.
		// Produces an orthonormal basis.
		/*template <typename T>
		constexpr void coordinate_system(const Vector3<T>& v1, Vector3<T>* v2, Vector3<T>* v3) {
			if (std::abs(v1.x) > std::abs(v1.y)) {
				*v2 = Vector3<T>(-v1.z, 0, v1.x) /
					std::sqrt(v1.x * v1.x + v1.z * v1.z);
			}
			else {
				*v2 = Vector3<T>(0, v1.z, -v1.y) /
					std::sqrt(v1.y * v1.y + v1.z * v1.z);
			}
			*v3 = Cross(v1, *v2);
		}*/
	}
}