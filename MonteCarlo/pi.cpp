#include "utility.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

int main() {
	int N = 1000;
	int inside_circle = 0;
	for (int i = 0; i < N; ++i) {
		auto x = random_double(-1, 1);
		auto y = random_double(-1, 1);
		if ((x * x) + (y * y) < 1) {
			inside_circle++;
		}
	}
	auto pi_estimate = 4 * static_cast<double>(inside_circle) / N;
	std::cout << std::fixed << std::setprecision(12);
	std::cout << "Estimate of Pi = " << pi_estimate << '\n';
}