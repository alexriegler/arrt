export module arrt.image;

import arrt.core;

namespace arrt {
	export struct ImageOptions {
		// Constructor
		ImageOptions(Float aspect_ratio, size_t image_width, size_t samples_per_pixel, size_t max_depth) :
			aspect_ratio(aspect_ratio),
			image_width(image_width), 
			image_height(static_cast<int>(image_width / aspect_ratio)),
			samples_per_pixel(samples_per_pixel),
			max_depth(max_depth)
		{}
		
		// This would be ambiguous.
		/*ImageOptions(size_t image_width, size_t image_height, size_t samples_per_pixel, size_t max_depth) :
			aspect_ratio(image_width / static_cast<Float>(image_height)),
			image_width(image_width),
			image_height(image_height),
			samples_per_pixel(samples_per_pixel),
			max_depth(max_depth)
		{}*/

		// Variables
		Float aspect_ratio;
		size_t image_width;
		size_t image_height;
		size_t samples_per_pixel;
		size_t max_depth;
	};
}