module;

#include <limits>
#include <numbers>
#include <random>

export module arrt.utility;

namespace arrt
{
    export
    {
        // Aliases
        // NOTE: There might be some benefit between one or the other, double vs float, but benchmarks need to
        //       be performed to know for sure.
#ifdef ARRT_FLOAT_AS_DOUBLE
        using Float = double;
#else
        using Float = float;
#endif // ARRT_FLOAT_AS_DOUBLE

        /// <summary>
        /// Converts a floating point value to Float.
        /// </summary>
        /// <param name="val">The floating point value to convert</param>
        /// <returns>The equivalent value as a Float</returns>
        constexpr Float operator"" _fl(long double val)
        {
            return static_cast<Float>(val);
        }

        // Constants
        /// <summary>
        /// Represents infinity.
        /// </summary>
        inline constexpr Float infinity = std::numeric_limits<Float>::infinity();

        /// <summary>
        /// Represent pi, the ratio of a circle’s circumference to its diameter.
        /// </summary>
        inline constexpr Float pi = std::numbers::pi_v<Float>;

        // Utility functions
        /// <summary>
        /// Converts degrees to radians.
        /// </summary>
        /// <param name="degrees">The degree value to convert</param>
        /// <returns>The equivalent value in radians</returns>
        constexpr Float degrees_to_radians(Float degrees)
        {
            return degrees * pi / 180.0_fl;
        }

        /// <summary>
        /// Returns a random float in the range [0, 1).
        /// </summary>
        /// <returns>A random float in the range [0, 1)</returns>
        inline Float random_float()
        {
            static std::uniform_real_distribution<Float> distribution(0.0_fl, 1.0_fl);
            static std::mt19937 generator;
            return distribution(generator);
        }

        /// <summary>
        /// Returns a random float in the range [min, max).
        /// </summary>
        /// <param name="min">The minimum value to generate, inclusive</param>
        /// <param name="max">The maximum value to generate, exclusive</param>
        /// <returns>A random float in the range [min, max)</returns>
        inline Float random_float(Float min, Float max)
        {
            return min + (max - min) * random_float();
        }

        /// <summary>
        /// Returns a random integer in [min, max].
        /// </summary>
        /// <param name="min">The minimum value to generate, inclusive</param>
        /// <param name="max">The maximum value to generate, inclusive</param>
        /// <returns>A random integer in the range [min, max]</returns>
        inline int random_int(int min, int max)
        {
            return static_cast<int>(random_float(static_cast<Float>(min), static_cast<Float>(max + 1)));
        }

        // TODO: Remove these functions since std::isnan does the same thing?
        /// <summary>
        /// Checks if the floating point number is a not-a-number (NaN) value.
        /// </summary>
        /// <typeparam name="FloatingPointType"></typeparam>
        /// <param name="x"></param>
        /// <returns></returns>
        template <typename FloatingPointType>
        constexpr bool is_nan(const FloatingPointType x)
        {
            return std::isnan(x);
        }

        // Checks if x is not a number.
        template <>
        constexpr bool is_nan(const int)
        {
            return false;
        }
    }
}