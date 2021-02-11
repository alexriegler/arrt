module;

export module arrt.imageio;

import arrt.utility;

namespace arrt {
	export struct ImageOptions {
		// Constructor
		ImageOptions(Float aspect_ratio, int image_width, int samples_per_pixel, int max_depth) :
			aspect_ratio(aspect_ratio),
			width(image_width), 
			height(static_cast<int>(image_width / aspect_ratio)),
			samples_per_pixel(samples_per_pixel),
			max_depth(max_depth)
		{}
		
		// This would be ambiguous.
		/*ImageOptions(int image_width, int image_height, int samples_per_pixel, int max_depth) :
			aspect_ratio(image_width / static_cast<Float>(image_height)),
			image_width(image_width),
			image_height(image_height),
			samples_per_pixel(samples_per_pixel),
			max_depth(max_depth)
		{}*/

		// Variables
		Float aspect_ratio;
		int width;
		int height;
		int samples_per_pixel;
		int max_depth;
	};
}