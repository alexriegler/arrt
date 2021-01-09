#include "utility.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

int main() {
	int inside_circle = 0;
	int runs = 0;
	std::cout << std::fixed << std::setprecision(12);
	while (true) {
		runs++;
		auto x = random_double(-1, 1);
		auto y = random_double(-1, 1);
		if ((x * x) + (y * y) < 1) {
			inside_circle++;
		}

		if (runs % 100000 == 0) {
			auto pi_estimate = 4 * static_cast<double>(inside_circle) / runs;
			std::cout << "Estimate of Pi = " << pi_estimate << '\r';
		}
	}
}