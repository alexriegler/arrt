#ifndef RT_STB_IMAGE_H
#define RT_STB_IMAGE_H

// Disable pedantic warnings for stb_image.h.
#ifdef _MSC_VER
	// Microsoft Visual C++ Compiler
	#pragma warning (push, 0)
#endif // _MSC_VER

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Restore warning levels.
#ifdef _MSC_VER
	// Microsoft Visual C++ Compiler
	#pragma warning (pop)
#endif // _MSC_VER

#endif // !RT_STB_IMAGE_H