#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
	int finish) {
	shared_ptr<ListNode<int>> head = L;

	if (ListSize(L) > 1) {
		shared_ptr<ListNode<int>> cursor = L;
		shared_ptr<ListNode<int>> prev = nullptr;

		int index = 1;

		while (index < start) {
			prev = cursor;
			cursor = cursor->next;
			++index;
		}

		shared_ptr<ListNode<int>> begin = cursor;
		shared_ptr<ListNode<int>> next = cursor->next;
		
		while (index < finish) {
			shared_ptr<ListNode<int>> target = next;
			next = next->next;

			target->next = cursor;
			cursor = target;

			++index;
		}

		if (prev) {
			prev->next = cursor;
		}
		else {
			head = cursor;
		}

		begin->next = next;
	}

	return head;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "L", "start", "finish" };
	return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
		&ReverseSublist, DefaultComparator{}, param_names);
}
