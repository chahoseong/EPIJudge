#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

int GetListLength(shared_ptr<ListNode<int>> l)
{
	int length = 0;
	while (l) {
		l = l->next;
		++length;
	}
	return length;
}

shared_ptr<ListNode<int>> Advance(shared_ptr<ListNode<int>> l, int step)
{
	for (int i = 0; i < step; ++i) {
		l = l->next;
	}
	return l;
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
	shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
	int l0_len = GetListLength(l0);
	int l1_len = GetListLength(l1);

	int delta = abs(l0_len - l1_len);
	
	if (l0_len > l1_len) {
		l0 = Advance(l0, delta);
	}
	else if (l1_len > l0_len) {
		l1 = Advance(l1, delta);
	}

	while ((l0 && l1) && l0 != l1) {
		l0 = l0->next;
		l1 = l1->next;
	}

	return l0;
}

void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
	shared_ptr<ListNode<int>> l0,
	shared_ptr<ListNode<int>> l1,
	shared_ptr<ListNode<int>> common) {
	if (common) {
		if (l0) {
			auto i = l0;
			while (i->next) {
				i = i->next;
			}
			i->next = common;
		}
		else {
			l0 = common;
		}

		if (l1) {
			auto i = l1;
			while (i->next) {
				i = i->next;
			}
			i->next = common;
		}
		else {
			l1 = common;
		}
	}

	auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

	if (result != common) {
		throw TestFailure("Invalid result");
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "l0", "l1", "common" };
	return GenericTestMain(
		args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
		&OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
