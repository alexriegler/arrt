export module arrt.ray;

import arrt.utility;
import arrt.vector;

namespace arrt
{
    /// <summary>
    /// Represents a ray of light.
    /// </summary>
    export class Ray
    {
    public:
        // Constructors
        /// <summary>
        /// Default constructs a ray.
        /// </summary>
        Ray() = default;

        /// <summary>
        /// Constructs a ray from a given origin, direction, and time.
        /// </summary>
        /// <param name="origin">The origin position of the ray</param>
        /// <param name="direction">The direction vector of the ray</param>
        /// <param name="time">The time of the ray</param>
        Ray(const Point3f& origin, const Vector3f& direction, Float time)
            : m_origin(origin), m_direction(direction), m_time(time)
        {}

        /// <summary>
        /// Constructs a ray from a given origin and direction.
        /// </summary>
        /// <param name="origin">The origin position of the ray</param>
        /// <param name="direction">The direction vector of the ray</param>
        Ray(const Point3f& origin, const Vector3f& direction)
            : Ray(origin, direction, 0.0_fl)
        {}

        // Functions
        /// <summary>
        /// Gets the origin position of the ray.
        /// </summary>
        /// <returns>The origin position of the ray</returns>
        auto origin() const { return m_origin; }

        /// <summary>
        /// Gets the direction vector of the ray.
        /// </summary>
        /// <returns>The direction vector of the ray</returns>
        auto direction() const { return m_direction; }

        /// <summary>
        /// Gets the time of the ray.
        /// </summary>
        /// <returns>The time of the ray</returns>
        auto time() const { return m_time; }

        /// <summary>
        /// Gets the position of the ray at time t along the direction vector.
        /// </summary>
        /// <param name="t">The time along the ray</param>
        /// <returns>The position of the ray at time t</returns>
        auto at(Float t) const
        {
            return m_origin + t * m_direction;
        }

    private:
        // Data
        Point3f m_origin{};
        Vector3f m_direction{};
        Float m_time{};
    };
}