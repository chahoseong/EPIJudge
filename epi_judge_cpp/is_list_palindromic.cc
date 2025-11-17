#include "list_node.h"
#include "test_framework/generic_test.h"

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
	auto fast = L;
	auto slow = L;

	while (fast && fast->next) {
		fast = fast->next->next;
		slow = slow->next;
	}

	shared_ptr<ListNode<int>> R;
	while (slow) {
		auto T = slow;
		slow = slow->next;
		T->next = R;
		R = T;
	}

	auto x = L;
	auto y = R;

	while (x && y) {
		if (x->data != y->data) {
			return false;
		}
		x = x->next;
		y = y->next;
	}

	return true;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "L" };
	return GenericTestMain(args, "is_list_palindromic.cc",
		"is_list_palindromic.tsv", &IsLinkedListAPalindrome,
		DefaultComparator{}, param_names);
}
