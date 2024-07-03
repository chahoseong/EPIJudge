#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

const int Safety = 2;
const int Field = 3;
const int Touchdown = 7;

int NumCombinationsForFinalScore(int final_score,
	const vector<int>& individual_play_scores)
{
	vector<vector<int>> table(std::size(individual_play_scores), vector<int>(final_score + 1, 0));

	// base case
	for (int i = 0; i <= final_score; ++i) {
		table[0][i] = (i % individual_play_scores[0] == 0);
	}

	for (int i = 1; i < std::size(individual_play_scores); ++i) {
		for (int j = 0; j <= final_score; ++j) {
			int without_this_play = table[i - 1][j];
			int with_this_play = (j >= individual_play_scores[i] ? table[i][j - individual_play_scores[i]] : 0);
			table[i][j] = without_this_play + with_this_play;
		}
	}

	return table.back().back();
}

void NumCombinationsForFinalScoreImpl(int final_score, const vector<int>& individual_play_score, int round, vector<int>& table)
{
}


int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "final_score", "individual_play_scores" };
	return GenericTestMain(args, "number_of_score_combinations.cc",
		"number_of_score_combinations.tsv",
		&NumCombinationsForFinalScore, DefaultComparator{},
		param_names);
}
