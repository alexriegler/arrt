module;

#include <iostream>

export module arrt.renderer;

import arrt.utility;
import arrt.imageio;

namespace arrt {
	export class Renderer {
    public:
        // Constructors
        Renderer(ImageOptions img_opt)
            : m_img_opt(img_opt) {}

		// Functions
		void render() {
			// TODO: Add ability to render other image types.
			std::cout << "P3\n" << m_img_opt.width << ' ' << m_img_opt.height << "\n255\n";

			for (int j = m_img_opt.height - 1; j >= 0; --j) {
				// Progress indicator
				std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
				for (int i = 0; i < m_img_opt.width; ++i) {
					/*color pixel_color(0, 0, 0);
					for (int s = 0; s < m_img_opt.samples_per_pixel; ++s) {
						Float u = (i + random_float()) / (static_cast<Float>(m_img_opt.width) - 1);
						Float v = (j + random_float()) / (static_cast<Float>(m_img_opt.height) - 1);
						ray r = cam.get_ray(u, v);
						pixel_color += ray_color(r, background, world, lights, max_depth);
					}
					write_color(std::cout, pixel_color, m_img_opt.samples_per_pixel);*/
				}
			}

			std::cerr << "\nDone.\n";
		}

    private:
		ImageOptions m_img_opt;
	};
}