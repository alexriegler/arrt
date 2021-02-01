export module arrt.renderer;

import arrt.utility;
import arrt.image;
import std.core;

namespace arrt {
	export class Renderer {
    public:
        // Constructors
        Renderer(ImageOptions image_options)
            : m_image_options(image_options) {}

		// Functions
		void render() {
			// TODO: Add ability to render other image types.
			//std::cout << "P3\n" << m_image_width << ' ' << m_image_height << "\n255\n";

			//for (size_t j = m_image_height - 1; j >= 0; --j) {
			//	// Progress indicator
			//	std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
			//	for (size_t i = 0; i < m_image_width; ++i) {
			//		color pixel_color(0, 0, 0);
			//		for (size_t s = 0; s < samples_per_pixel; ++s) {
			//			auto u = (i + random_double()) / (double(m_image_width) - 1);
			//			auto v = (j + random_double()) / (double(m_image_height) - 1);
			//			ray r = cam.get_ray(u, v);
			//			pixel_color += ray_color(r, background, world, lights, max_depth);
			//		}
			//		write_color(std::cout, pixel_color, samples_per_pixel);
			//	}
			//}

			std::cerr << "\nDone.\n";
		}

    private:
		ImageOptions m_image_options;
	};
}