#include <string>
#include <stack>
#include "test_framework/generic_test.h"

using std::string;
using std::stack;

bool IsOperator(char ch) {
	switch (ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
		return true;
	}

	return false;
}

int Evaluate(const string& expression) {
	stack<int> operand;

	int start = 0;
	int end = 0;
	bool done = false;
	
	while (!done) {
		string elem;
		end = expression.find(',', start);

		if (end == string::npos) {
			elem = expression.substr(start);
			done = true;
		}
		else {
			elem = expression.substr(start, end - start);
		}

		if (elem.size() > 1 || !IsOperator(elem[0])) {
			operand.push(std::stoi(elem));
		}
		else {
			int y = operand.top();
			operand.pop();

			int x = operand.top();
			operand.pop();

			switch (elem[0]) {
			case '+':
				operand.push(x + y);
				break;
			case '-':
				operand.push(x - y);
				break;
			case '*':
				operand.push(x * y);
				break;
			case '/':
				operand.push(x / y);
				break;
			}
		}

		start = end + 1;
	}

	return operand.top();
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "expression" };
	return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
		DefaultComparator{}, param_names);
}
