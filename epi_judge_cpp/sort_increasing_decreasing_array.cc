#include <algorithm>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

struct RangedIterator
{
	vector<int>::const_iterator current;
	vector<int>::const_iterator end;

	bool operator>(const RangedIterator& other) const {
		return *current > *other.current;
	}
};

vector<int> SortKIncreasingDecreasingArray(const vector<int>& A) {
	// O(N * logN)
	/*vector<int> heap = A;
	std::make_heap(heap.begin(), heap.end());
	std::sort_heap(heap.begin(), heap.end());
	return heap;*/

	// O(N * logK) : K는 부분 배열의 개수
	vector<vector<int>> sortedArray;
	size_t startIndex = 0;
	bool increasing = A[0] < A[1];

	for (int i = 1; i < std::size(A); ++i) {
		if (A[i - 1] < A[i] && !increasing) {
			sortedArray.push_back({ std::rbegin(A) + std::size(A) - i, std::rbegin(A) + std::size(A) - startIndex });
			increasing = true;
			startIndex = i;
		}
		else if (A[i - 1] >= A[i] && increasing) {
			sortedArray.push_back({ std::begin(A) + startIndex, std::begin(A) + i });
			increasing = false;
			startIndex = i;
		}
	}

	if (increasing) {
		sortedArray.push_back({ std::begin(A) + startIndex, std::end(A) });
	}
	else {
		sortedArray.push_back({ std::rbegin(A), std::rbegin(A) + std::size(A) - startIndex });
	}

	std::priority_queue<RangedIterator, vector<RangedIterator>, std::greater<RangedIterator>> minHeap;
	for (const vector<int>& sub : sortedArray) {
		minHeap.push({ std::cbegin(sub), std::cend(sub) });
	}

	vector<int> result;
	while (!std::empty(minHeap)) {
		RangedIterator it = minHeap.top();
		minHeap.pop();

		result.push_back(*it.current);
		it.current = std::next(it.current);

		if (it.current != it.end) {
			minHeap.push(it);
		}
	}

	return result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A" };
	return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
		"sort_increasing_decreasing_array.tsv",
		&SortKIncreasingDecreasingArray, DefaultComparator{},
		param_names);
}
