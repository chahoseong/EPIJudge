#include <tuple>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
struct Rect {
	int x, y, width, height;
};

// 내가 푼 방법
//Rect IntersectRectangle(const Rect& r1, const Rect& r2) {
//	Rect left, right;
//	if (r1.x <= r2.x) {
//		left = r1;
//		right = r2;
//	}
//	else {
//		left = r2;
//		right = r1;
//	}
//
//	int w = left.x + left.width - right.x;
//	int x = right.x;
//	if (w < 0) {
//		return Rect{ 0, 0, -1, -1 };
//	}
//	else if (w > right.width) {
//		w = right.width;
//	}
//
//	Rect top, bottom;
//	if (r1.y >= r2.y) {
//		top = r1;
//		bottom = r2;
//	}
//	else {
//		top = r2;
//		bottom = r1;
//	}
//
//	int h = bottom.y + bottom.height - top.y;
//	int y = top.y;
//	if (h < 0) {
//		return Rect{ 0, 0, -1, -1 };
//	}
//	else if (h > top.height) {
//		h = top.height;
//	}
//
//	return Rect{ x, y, w, h };
//}

// 책에 나온 해답
bool IsIntersect(const Rect& r1, const Rect& r2)
{
	return r1.x <= r2.x + r2.width && r1.x + r1.width >= r2.x &&
		r1.y <= r2.y + r2.height && r1.y + r1.height >= r2.y;
}

Rect IntersectRectangle(const Rect& r1, const Rect& r2)
{
	// *정답이 아닌 부분을 먼저 제외한다.
	if (!IsIntersect(r1, r2)) {
		return { 0, 0, -1, -1 };
	}
	return {
		std::max(r1.x, r2.x), std::max(r1.y, r2.y),
		std::min(r1.x + r1.width, r2.x + r2.width) - std::max(r1.x, r2.x),
		std::min(r1.y + r1.height, r2.y + r2.height) - std::max(r1.y, r2.y)
	};
}

bool operator==(const Rect& r1, const Rect& r2) {
	return std::tie(r1.x, r1.y, r1.width, r1.height) ==
		std::tie(r2.x, r2.y, r2.width, r2.height);
}

namespace test_framework {
	template <>
	struct SerializationTrait<Rect> : UserSerTrait<Rect, int, int, int, int> {
		static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
			return { FmtStr("height({})", arg_name), FmtStr("width({})", arg_name) };
		}

		static std::vector<int> GetMetrics(const Rect& x) {
			return { x.height, x.width };
		}
	};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const Rect& r) {
	return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "r1", "r2" };
	return GenericTestMain(args, "rectangle_intersection.cc",
		"rectangle_intersection.tsv", &IntersectRectangle,
		DefaultComparator{}, param_names);
}
