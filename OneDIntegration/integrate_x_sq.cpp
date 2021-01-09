#include "utility.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

int main() {
	int N = 1000000;
	auto sum = 0.0;
	for (int i = 0; i < N; ++i) {
		auto x = random_double(0, 2);
		sum += x * x;
	}
	auto integral = 2 * sum / N;
	std::cout << std::fixed << std::setprecision(12);
	std::cout << "I = " << integral << '\n';
}