module;

#include <cmath>
#include <cassert>
#include <concepts>
#include <iostream>
#include <type_traits>

export module arrt.vector;

import arrt.utility;

namespace arrt
{
    export
    {
        // Concepts
        /// <summary>
        /// Represents either a Float or int type.
        /// </summary>
        template <typename T>
        concept FloatOrInt = std::is_same_v<T, Float> || std::is_same_v<T, int>;

        /// <summary>
        /// Represent an arithmetic type.
        /// </summary>
        template <typename T>
        concept Arithmetic = std::is_arithmetic_v<T>;

        // TODO: Left off on section 4.2.
        
        /// <summary>
        /// Represents a three-element vector.
        /// </summary>
        template <FloatOrInt T>
        struct Vector3
        {
            // Constructors
            /// <summary>
            /// Constructs a zero vector.
            /// </summary>
            constexpr Vector3() = default;

            // TODO: Get rid of assert statements?
            /// <summary>
            /// Constructs a vector with the specified elements.
            /// </summary>
            /// <param name="x">The value of the x component</param>
            /// <param name="y">The value of the y component</param>
            /// <param name="z">The value of the z component</param>
            constexpr Vector3(T x, T y, T z)
                : x{ x }, y{ y }, z{ z }
            {
                assert(!has_nans());
            }

            // Functions
            /// <summary>
            /// Checks if any of the components are NaN (not a number).
            /// </summary>
            /// <returns><code>true</code>, if the vector has a NaN; <code>false</code>, otherwise</returns>
            constexpr bool has_nans() const
            {
                return is_nan(x) || is_nan(y) || is_nan(z);
            }

            /// <summary>
            /// Returns the squared length of the vector. This is useful when
            /// you only need the square and do not want to perform an
            /// "expensive" square root operation.
            /// </summary>
            /// <returns>The squared length of the vector</returns>
            constexpr Float length_squared() const
            {
                return x * x + y * y + z * z;
            }

            /// <summary>
            /// Returns the length of the vector.
            /// </summary>
            /// <returns>The length of the vector</returns>
            constexpr Float length() const
            {
                return std::sqrt(length_squared());
            }

            constexpr bool operator==(const Vector3<T>& v) const = default;

            constexpr T operator[](int i) const
            {
                assert(i >= 0 && i <= 2);
                if (i == 0) { return x; }
                if (i == 1) { return y; }
                return z;
            }

            constexpr T& operator[](int i)
            {
                assert(i >= 0 && i <= 2);
                if (i == 0) { return x; }
                if (i == 1) { return y; }
                return z;
            }

            constexpr Vector3<T> operator+(const Vector3<T>& v) const
            {
                assert(!v.has_nans());
                return Vector3(x + v.x, y + v.y, z + v.z);
            }

            constexpr Vector3<T>& operator+=(const Vector3<T>& v) const
            {
                assert(!v.has_nans());
                x += v.x;
                y += v.y;
                z += v.z;
                return *this;
            }

            constexpr Vector3<T> operator-() const
            {
                return Vector3<T>(-x, -y, -z);
            }

            constexpr Vector3<T> operator-(const Vector3<T>& v) const
            {
                assert(!v.has_nans());
                return Vector3(x - v.x, y - v.y, z - v.z);
            }

            constexpr Vector3<T> operator-=(const Vector3<T>& v) const
            {
                assert(!v.has_nans());
                x -= v.x;
                y -= v.y;
                z -= v.z;
                return *this;
            }

            template <Arithmetic U>
            constexpr Vector3<T> operator*(U scalar) const
            {
                return Vector3(scalar * x, scalar * y, scalar * z);
            }

            template <Arithmetic U>
            constexpr Vector3<T>& operator*=(U scalar)
            {
                assert(!is_nan(scalar));
                x *= scalar;
                y *= scalar;
                z *= scalar;
                return *this;
            }

            template <Arithmetic U>
            constexpr Vector3<T> operator/(U fraction) const
            {
                assert(fraction != 0);
                Float inverse = 1 / static_cast<Float>(fraction);
                return Vector3<T>(x * inverse, y * inverse, z * inverse);
            }

            template <Arithmetic U>
            constexpr Vector3<T>& operator/=(U fraction)
            {
                assert(fraction != 0);
                Float inverse = 1 / static_cast<Float>(fraction);
                x *= inverse;
                y *= inverse;
                z *= inverse;
                return *this;
            }

            // Data
            T x{ 0 };
            T y{ 0 };
            T z{ 0 };
        };

        // Aliases
        /// <summary>
        /// Represents a three-element vector of <code>Float</code>s.
        /// </summary>
        using Vector3f = Vector3<Float>;
        /// <summary>
        /// Represents a three-element vector of <code>int</code>s.
        /// </summary>
        using Vector3i = Vector3<int>;
        /// <summary>
        /// Represents a three-dimensional point of <code>Float</code>s.
        /// </summary>
        using Point3f = Vector3f;
        /// <summary>
        /// Represents a three-dimensional point of <code>int</code>s.
        /// </summary>
        using Point3i = Vector3i;
        /// <summary>
        /// Represents a three-channel color using <code>Float</code>s.
        /// </summary>
        using Color = Vector3f;

        // Non-member Vector3 functions
        template <FloatOrInt T, Arithmetic U>
        constexpr Vector3<T> operator*(U lhs_scalar, const Vector3<T>& rhs_v)
        {
            return rhs_v * lhs_scalar;
        }

        /// <summary>
        /// Formats the vector as "[ x, y, z ]".
        /// </summary>
        /// <param name="os">The output stream</param>
        /// <param name="v">The vector to output</param>
        /// <returns>The output stream with the formatted vector</returns>
        template <FloatOrInt T>
        constexpr std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
        {
            os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
            return os;
        }

        /// <summary>
        /// Returns a new vector where each element is the absolute value of
        /// the corresponding element of the input vector.
        /// </summary>
        /// <param name="v">The vector to get the absolute value of</param>
        /// <returns>A vector with the absolute value of each element of the
        /// input vector</returns>
        template <FloatOrInt T>
        constexpr Vector3<T> abs(const Vector3<T>& v)
        {
            return Vector3<T>(std::abs((v.x), std::abs(v.y), std::abs(v.z)));
        }

        /// <summary>
        /// Calculates the dot product of the two vectors. This operation is
        /// commutative, i.e., the order doesn't matter.
        /// </summary>
        /// <param name="lhs">The left-hand side vector</param>
        /// <param name="rhs">The right-hand side vector</param>
        /// <returns>The dot product of the two vectors</returns>
        template <FloatOrInt T>
        constexpr T dot(const Vector3<T>& lhs, const Vector3<T>& rhs)
        {
            assert(!lhs.has_nans() && !rhs.has_nans());
            return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
        }

        /// <summary>
        /// Calculates the dot product of the two vectors and takes the
        /// absolute value. This operation is commutative, i.e., the order
        /// doesn't matter.
        /// </summary>
        /// <param name="lhs">The left-hand side vector</param>
        /// <param name="rhs">The right-hand side vector</param>
        /// <returns>The absolute value of the dot product of the two vectors</returns>
        template <FloatOrInt T>
        constexpr T abs_dot(const Vector3<T>& lhs, const Vector3<T>& rhs)
        {
            assert(!lhs.has_nans() && !rhs.has_nans());
            return std::abs(dot(lhs, rhs));
        }

        /// <summary>
        /// Calculates the cross product of the two vectors. This operation is
        /// anti-commutative (that is, a x b = -b x a), which means the order
        /// of the parameters matters.
        /// </summary>
        /// <param name="lhs">The left-hand side vector</param>
        /// <param name="rhs">The right-hand side vector</param>
        /// <returns></returns>
        template <FloatOrInt T>
        constexpr Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs)
        {
            assert(!lhs.has_nans() && !rhs.has_nans());
            // The vector elements are converted to double-precision (regardless of the
            // type of Float) before the subtractions in the Cross() function. Using 
            // extra precision for 32-bit floating-point values here protects against 
            // error from catastrophic cancellation, a type of floating-point error that
            // can happen when subtracting two values that are very close together.
            // http://www.pbr-book.org/3ed-2018/Geometry_and_Transformations/Vectors.html
            double v1x = lhs.x;
            double v1y = lhs.y;
            double v1z = lhs.z;
            double v2x = rhs.x;
            double v2y = rhs.y;
            double v2z = rhs.z;
            return Vector3<T>(
                (v1y * v2z) - (v1z * v2y),
                (v1z * v2x) - (v1x * v2z),
                (v1x * v2y) - (v1y * v2x));
        }

        /// <summary>
        /// Returns a new vector that is the normalized version of the input
        /// vector.
        /// </summary>
        /// <param name="v">The vector to get the normalized version of</param>
        /// <returns>A vector representing the input vector after being normalized</returns>
        template <FloatOrInt T>
        constexpr Vector3<T> normalize(const Vector3<T>& v)
        {
            return v / v.length();
        }

        // Returns the smallest coordinate value.

        /// <summary>
        /// Returns the smallest element.
        /// </summary>
        /// <param name="v">The vector to search</param>
        /// <returns>The smallest element</returns>
        template <FloatOrInt T>
        constexpr T min_component(const Vector3<T>& v)
        {
            return std::min(v.x, std::min(v.y, v.z));
        }

        /// <summary>
        /// Returns the largest element.
        /// </summary>
        /// <param name="v">The vector to search</param>
        /// <returns>The largest element</returns>
        template <FloatOrInt T>
        constexpr T max_component(const Vector3<T>& v)
        {
            return std::max(v.x, std::max(v.y, v.z));
        }

        /// <summary>
        /// Returns the index of the element with the largest value.
        /// </summary>
        /// <param name="v">The vector to search</param>
        /// <returns>The index containing the element with the largest value</returns>
        template <FloatOrInt T>
        constexpr int max_dimension(const Vector3<T>& v)
        {
            return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) :
                ((v.y > v.z) ? 1 : 2);
        }

        /// <summary>
        /// Returns a new vector that is the result of the component-wise minimums.
        /// </summary>
        /// <param name="v1">The first input vector</param>
        /// <param name="v2">The second input vector</param>
        /// <returns>A vector that is the result of the component-wise minimums</returns>
        template <FloatOrInt T>
        constexpr Vector3<T> min(const Vector3<T>& v1, const Vector3<T>& v2)
        {
            return Vector3<T>(
                std::min(v1.x, v2.x),
                std::min(v1.y, v2.y),
                std::min(v1.z, v2.z));
        }

        /// <summary>
        /// Returns a new vector that is the result of the component-wise maximums.
        /// </summary>
        /// <param name="v1">The first input vector</param>
        /// <param name="v2">The second input vector</param>
        /// <returns>A vector that is the result of the component-wise maximums</returns>
        template <FloatOrInt T>
        constexpr Vector3<T> max(const Vector3<T>& v1, const Vector3<T>& v2)
        {
            return Vector3<T>(
                std::max(v1.x, v2.x),
                std::max(v1.y, v2.y),
                std::max(v1.z, v2.z));
        }

        /// <summary>
        /// Returns a new vector with the elements being the permutation of the
        /// coordinate values of the input vector according to the index values
        /// provided.
        /// </summary>
        /// <param name="v">The input vector</param>
        /// <param name="x">The index for the x component to take on</param>
        /// <param name="y">The index for the y component to take on</param>
        /// <param name="z">The index for the z component to take on</param>
        /// <returns><A vector that is permutated from the input vector/returns>
        template <FloatOrInt T>
        constexpr Vector3<T> permute(const Vector3<T>& v, int x, int y, int z)
        {
            assert((x >= 0 && x <= 2) && (y >= 0 && y <= 2) && (z >= 0 && z <= 2));
            return Vector3<T>(v[x], v[y], v[z]);
        }

        // TODO: Do I need this function?
        /// <summary>
        /// Produces an orthonormal basis. Assumes that v1 is normalized.
        /// </summary>
        /// <param name="v1"></param>
        /// <param name="v2"></param>
        /// <param name="v3"></param>
        /*template <FloatOrInt T>
        constexpr void coordinate_system(const Vector3<T>& v1, Vector3<T>* v2, Vector3<T>* v3) {
            if (std::abs(v1.x) > std::abs(v1.y)) {
                *v2 = Vector3<T>(-v1.z, 0, v1.x) /
                    std::sqrt(v1.x * v1.x + v1.z * v1.z);
            }
            else {
                *v2 = Vector3<T>(0, v1.z, -v1.y) /
                    std::sqrt(v1.y * v1.y + v1.z * v1.z);
            }
            *v3 = cross(v1, *v2);
        }*/
    }
}