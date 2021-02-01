import arrt.core;
import arrt.image;
import arrt.renderer;

int main(int argc, char* argv[]) {
	arrt::ImageOptions img_opt(1.0 / 1.0, 600, 100, 50);
	arrt::Renderer rt(img_opt);

	rt.render();
}