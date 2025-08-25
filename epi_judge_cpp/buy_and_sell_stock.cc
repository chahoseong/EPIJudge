#include <vector>
#include "test_framework/generic_test.h"

using std::vector;

double BuyAndSellStockOnce(const vector<double>& prices) {
	size_t lowestIndex = 0;
	double bestProfit = 0.0;

	for (size_t day = 1; day < prices.size(); ++day) {
		double profit = prices[day] - prices[lowestIndex];
		if (profit > bestProfit) {
			bestProfit = profit;
		}
		if (prices[day] < prices[lowestIndex]) {
			lowestIndex = day;
		}
	}

	return bestProfit;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "prices" };
	return GenericTestMain(args, "buy_and_sell_stock.cc",
		"buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
		DefaultComparator{}, param_names);
}
