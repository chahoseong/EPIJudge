#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistanceInternal(const string& AString, int AIdx, const string& BString, int BIdx, vector<vector<int>>& distances);

int LevenshteinDistance(const string& A, const string& B) {
	// A[A.length() - 1]�� B[B.length() - 1]�� ���ڰ� ���ٸ�,
	// �� ���ڿ��� �ּ� ���� ���̴� A[A.length() - 2]�� B[B.length() - 2]�� �ּ� ���� ���̿� �����ϴ�.
	// 
	// ������ A[A.length() - 1]�� B[B.length() - 1]�� ���ڰ� �ٸ� ���, �� ���ڿ��� �ּ� ���� ���̴�
	// 1. A[A.length() - 2]���� B[B.length() - 2]�� ��ȯ�� �ڿ� A�� ������ ���ڸ� B�� ������ ���ڷ� ġȯ.
	// 2. A[A.length() - 1]���� B[B.length() - 2]�� ��ȯ�� �ڿ� A�� ���ڿ��� B�� ������ ���ڸ� �߰�.
	// 3. A[A.length() - 2]���� B[B.length() - 1]�� ��ȯ�� �ڿ� A�� ������ ���ڸ� ����.
	// �� ������ ��� �߿� �ּҰ��� ã�Ƽ� ���⿡ ���� ������ ������ +1 �����ָ� �ȴ�.
	vector<vector<int>> distances(A.length(), vector<int>(B.length(), -1));
	return LevenshteinDistanceInternal(A, A.length() - 1, B, B.length() - 1, distances);
}

int LevenshteinDistanceInternal(const string& AString, int AIdx, const string& BString, int BIdx, vector<vector<int>>& distances)
{
	if (AIdx < 0) {
		return BIdx + 1;
	}
	else if (BIdx < 0) {
		return AIdx + 1;
	}
	else if (distances[AIdx][BIdx] == -1) {
		if (AString[AIdx] == BString[BIdx]) {
			distances[AIdx][BIdx] = LevenshteinDistanceInternal(AString, AIdx - 1, BString, BIdx - 1, distances);
		}
		else {
			int inserted = LevenshteinDistanceInternal(AString, AIdx, BString, BIdx - 1, distances);
			int removed = LevenshteinDistanceInternal(AString, AIdx - 1, BString, BIdx, distances);
			int replaced = LevenshteinDistanceInternal(AString, AIdx - 1, BString, BIdx - 1, distances);
			distances[AIdx][BIdx] = 1 + std::min({ inserted, removed, replaced });
		}
	}
	return distances[AIdx][BIdx];
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A", "B" };
	return GenericTestMain(args, "levenshtein_distance.cc",
		"levenshtein_distance.tsv", &LevenshteinDistance,
		DefaultComparator{}, param_names);
}
