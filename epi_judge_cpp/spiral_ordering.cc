#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

void Sub(const std::vector<vector<int>>& matrix, int x, int y, int length, vector<int>& result)
{
	if (length < 2) {
		if (length == 1) {
			result.push_back(matrix[y][x]);
		}
		return;
	}

	int shift[][2] = {
		{1, 0}, {0, 1}, {-1, 0}, {0, -1}
	};

	int cx = x;
	int cy = y;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < length - 1; ++j) {
			result.push_back(matrix[cy][cx]);
			cx += shift[i][0];
			cy += shift[i][1];
		}
	}

	Sub(matrix, x + 1, y + 1, length - 2, result);
}

vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
	vector<int> result;
	Sub(square_matrix, 0, 0, square_matrix.size(), result);
	return result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "square_matrix" };
	return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
		&MatrixInSpiralOrder, DefaultComparator{},
		param_names);
}
