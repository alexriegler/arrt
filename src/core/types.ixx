export module arrt.types;

// Typedefs
#ifdef ARRT_FLOAT_AS_DOUBLE
	export typedef double Float;
#else
	export typedef float Float;
#endif // ARRT_FLOAT_AS_DOUBLE