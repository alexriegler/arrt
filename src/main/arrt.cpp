import arrt.core;
import arrt.vector;

#include <iostream>

using namespace arrt;

int main(/* int argc, char* argv[] */)
{
    ImageOptions img_opt(
        1.0 / 1.0,  // Aspect ratio
        256,        // Width
        100,        // Samples per pixel
        50          // Maximum depth
    );
    Renderer rt(img_opt);
    rt.render();
}