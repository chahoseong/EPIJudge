#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistanceInternal(const string& AString, int AIdx, const string& BString, int BIdx, vector<vector<int>>& distances);

int LevenshteinDistance(const string& A, const string& B) {
	// A[A.length() - 1]와 B[B.length() - 1]의 문자가 같다면,
	// 두 문자열의 최소 편집 길이는 A[A.length() - 2]와 B[B.length() - 2]의 최소 편집 길이와 같습니다.
	// 
	// 하지만 A[A.length() - 1]와 B[B.length() - 1]의 문자가 다를 경우, 두 문자열의 최소 편집 길이는
	// 1. A[A.length() - 2]에서 B[B.length() - 2]로 변환한 뒤에 A의 마지막 문자를 B의 마지막 문자로 치환.
	// 2. A[A.length() - 1]에서 B[B.length() - 2]로 변환한 뒤에 A의 문자열에 B의 마지막 문자를 추가.
	// 3. A[A.length() - 2]에서 B[B.length() - 1]로 변환한 뒤에 A의 마지막 문자를 삭제.
	// 이 세가지 경우 중에 최소값을 찾아서 여기에 현재 진행한 연산을 +1 더해주면 된다.
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
