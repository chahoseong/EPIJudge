#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
	if (!L) {
		return nullptr;
	}

	shared_ptr<ListNode<int>> even_head = make_shared<ListNode<int>>(0, nullptr);
	shared_ptr<ListNode<int>> odd_head = make_shared<ListNode<int>>(0, nullptr);
	shared_ptr<ListNode<int>> tails[2] = { even_head, odd_head };

	auto cursor = L;
	int i = 0;

	while (cursor) {
		tails[i]->next = cursor;
		tails[i] = cursor;
		cursor = cursor->next;
		tails[i]->next = nullptr;
		i = (i + 1) % 2;
	}

	tails[0]->next = odd_head->next;

	return even_head->next;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "L" };
	return GenericTestMain(args, "even_odd_list_merge.cc",
		"even_odd_list_merge.tsv", &EvenOddMerge,
		DefaultComparator{}, param_names);
}
