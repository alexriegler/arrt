#include "utility.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

inline double pdf(double x) {
	return 3 * x * x / 8;
}

int main() {
	int N = 1;
	auto sum = 0.0;
	for (int i = 0; i < N; ++i) {
		auto x = pow(random_double(0, 8), 1.0/3.0);
		sum += x * x / pdf(x);
	}
	auto integral = sum / N;
	std::cout << std::fixed << std::setprecision(12);
	std::cout << "I = " << integral << '\n';
}