#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
	if (n <= 1) {
		return vector<int>();
	}

	if (n == 2) {
		return { 2 };
	}

	vector<int> primes;
	primes.emplace_back(2);


	for (int i = 3; i <= n; ++i) {
		if (i % 2 == 0) {
			continue;
		}

		int limit = std::sqrt(i);
		bool isPrime = true;
		for (int j = 3; j <= limit; ++j) {
			if (i % j == 0) {
				isPrime = false;
				break;
			}
		}

		if (isPrime) {
			primes.emplace_back(i);
		}
	}

	return primes;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "n" };
	return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
		&GeneratePrimes, DefaultComparator{}, param_names);
}
