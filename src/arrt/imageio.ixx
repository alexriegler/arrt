module;

export module arrt.imageio;

import arrt.utility;

namespace arrt
{
    /// <summary>
    /// Represents the possible options for an image generated by the ray tracer.
    /// </summary>
    export struct ImageOptions
    {
        // Constructor
        /// <summary>
        /// Constructs an image options object.
        /// </summary>
        /// <param name="aspect_ratio">The aspect ratio of the image, width / height</param>
        /// <param name="image_width">The width of the image</param>
        /// <param name="samples_per_pixel">The amount of rays to send per pixel. In general, more rays gives a better image</param>
        /// <param name="max_depth">The maximum amount of bounces for rays</param>
        ImageOptions(Float aspect_ratio, int image_width, int samples_per_pixel, int max_depth) :
            aspect_ratio(aspect_ratio),
            width(image_width),
            height(static_cast<int>(image_width / aspect_ratio)),
            samples_per_pixel(samples_per_pixel),
            max_depth(max_depth)
        {}

        // Variables
        Float aspect_ratio;
        int width;
        int height;
        int samples_per_pixel;
        int max_depth;
    };
}