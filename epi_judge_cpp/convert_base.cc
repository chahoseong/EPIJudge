#include <string>

#include "test_framework/generic_test.h"
using std::string;

int ToDecimal(char ch)
{
	switch (ch)
	{
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	}

	return ch - '0';
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
	
	int x = 0;
	int sign = 1;

	for (int i = 0; i < num_as_string.size(); ++i)
	{
		if (num_as_string[i] == '-')
		{
			sign = -1;
			continue;
		}

		int n = ToDecimal(num_as_string[i]);
		x += n * pow(b1, num_as_string.size() - 1 - i);
	}

	string converted;

	if (x == 0)
	{
		converted.push_back('0');
	}
	else
	{
		while (x != 0)
		{
			int digit = x % b2;

			char ch;

			switch (digit)
			{
			case 10:
				ch = 'A';
				break;
			case 11:
				ch = 'B';
				break;
			case 12:
				ch = 'C';
				break;
			case 13:
				ch = 'D';
				break;
			case 14:
				ch = 'E';
				break;
			case 15:
				ch = 'F';
				break;
			default:
				ch = '0' + digit;
			}

			converted.push_back(ch);

			x /= b2;
		}

		if (sign == -1)
		{
			converted.push_back('-');
		}
	}

	return string(converted.rbegin(), converted.rend());
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "num_as_string", "b1", "b2" };
	return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
		&ConvertBase, DefaultComparator{}, param_names);
}
