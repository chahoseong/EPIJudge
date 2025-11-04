#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start, int finish) {
	auto dummy_head = make_shared<ListNode<int>>(0, L);
	auto sublist_head = dummy_head;

	int k = 1;
	while (k++ < start) {
		sublist_head = sublist_head->next;
	}

	auto sublist_iter = sublist_head->next;
	while (start++ < finish) {
		auto temp = sublist_iter->next;
		sublist_iter->next = temp->next;
		temp->next = sublist_head->next;
		sublist_head->next = temp;
	}

	return dummy_head->next;
}
//shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
//	int finish) {
//
//	if (!L) {
//		return L;
//	}
//
//	if (finish - start <= 0) {
//		return L;
//	}
//
//	auto cursor = L;
//	shared_ptr<ListNode<int>> prev = nullptr;
//
//	for (int i = 1; i < start; ++i) {
//		prev = cursor;
//		cursor = cursor->next;
//	}
//
//	shared_ptr<ListNode<int>> sublistHead = nullptr;
//	shared_ptr<ListNode<int>> sublistTail = nullptr;
//
//	for (int i = start; i <= finish; ++i) {
//		if (!sublistHead) {
//			sublistHead = cursor;
//			cursor = cursor->next;
//			sublistTail = sublistHead;
//			sublistTail->next = nullptr;
//		}
//		else {
//			auto temp = sublistHead;
//			sublistHead = cursor;
//			cursor = cursor->next;
//			sublistHead->next = temp;
//		}
//	}
//
//	if (prev) {
//		prev->next = sublistHead;
//	}
//	else {
//		L = sublistHead;
//	}
//
//	sublistTail->next = cursor;
//
//	return L;
//}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "L", "start", "finish" };
	return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
		&ReverseSublist, DefaultComparator{}, param_names);
}
