module;

#include <algorithm>
#include <iostream>

#include <fstream>

export module arrt.renderer;

import arrt.imageio;
import arrt.utility;
import arrt.vector;

namespace arrt
{
    /// <summary>
    /// Represents the renderer that produces images.
    /// </summary>
    export class Renderer
    {
    public:
        // Constructors
        /// <summary>
        /// Constructs a renderer object with the specified options.
        /// </summary>
        /// <param name="img_opt">The options to be used for producing images</param>
        explicit Renderer(const ImageOptions& img_opt)
            : m_img_opt(img_opt)
        {}

        // Functions
        /// <summary>
        /// Starts the rendering process.
        /// </summary>
        void render()
        {
            auto& os = std::cout;

            // TODO: Add ability to render other image types.
            os << "P3\n" << m_img_opt.width << ' ' << m_img_opt.height << "\n255\n";

            for (int j = m_img_opt.height - 1; j >= 0; --j)
            {
                // TODO: Add progress indicator.
                std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
                for (int i = 0; i < m_img_opt.width; ++i)
                {
                    // TODO: Remove.
                    Color pixel_color(Float(i) / (m_img_opt.width - 1), Float(j) / (m_img_opt.height - 1), 0.25);
                    write_color(os, pixel_color, 1);

                    // TODO: Add ray class
                    /*Vector3f pixel_color(0, 0, 0);
                    for (int s = 0; s < m_img_opt.samples_per_pixel; ++s) {
                        Float u = (i + random_float()) / (static_cast<Float>(m_img_opt.width) - 1);
                        Float v = (j + random_float()) / (static_cast<Float>(m_img_opt.height) - 1);
                        ray r = cam.get_ray(u, v);
                        pixel_color += ray_color(r, background, world, lights, max_depth);
                    }
                    write_color(std::cout, pixel_color, m_img_opt.samples_per_pixel);*/
                }
            }

            // TODO: Add completion indicator.
            std::cerr << "\nDone.\n";
        }

    private:
        // TODO: Add alternative file writing formats, e.g., png, jpeg, etc.
        /// <summary>
        /// Writes a color in the PPM format to the std::ostream.
        /// </summary>
        /// <param name="out">The output stream to write the color to</param>
        /// <param name="pixel_color">The color of the pixel</param>
        /// <param name="samples_per_pixel">The number of samples taken for the pixel</param>
        void write_color(std::ostream& out, Color pixel_color, int samples_per_pixel) const
        {
            // Extract components
            Float r = pixel_color.x;
            Float g = pixel_color.y;
            Float b = pixel_color.z;

            // Replace NaN components with zero.
            if (r != r) { r = 0.0_fl; }
            if (g != g) { g = 0.0_fl; }
            if (b != b) { b = 0.0_fl; }

            // Divide the color by the number of samples and gamma-correct for gamma=2.0.
            // TODO: Try other gamma correction techniques.
            Float scale = 1 / static_cast<Float>(samples_per_pixel);
            r = std::sqrt(scale * r);
            g = std::sqrt(scale * g);
            b = std::sqrt(scale * b);

            // Write the translated [0, 255] value of each color component.
            constexpr Float lo = 0.0_fl;
            constexpr Float hi = 0.999_fl;
            out << static_cast<int>(256 * std::clamp(r, lo, hi)) << ' '
                << static_cast<int>(256 * std::clamp(g, lo, hi)) << ' '
                << static_cast<int>(256 * std::clamp(b, lo, hi)) << '\n';
        }

        // Data
        ImageOptions m_img_opt;
    };
}