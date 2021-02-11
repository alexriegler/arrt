import arrt.core;
import arrt.vector;

#include <iostream>

int main(int argc, char* argv[]) {
	arrt::ImageOptions img_opt(1.0 / 1.0, 100, 100, 50);
	arrt::Renderer rt(img_opt);

	rt.render();

	arrt::Vector3f v1;
	std::cout << v1 << std::endl;
}