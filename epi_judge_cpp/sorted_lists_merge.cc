#include "list_node.h"
#include "test_framework/generic_test.h"

// node를 리스트 끝에 추가하고, node는 다음 노드로 이동한다.
void AppendNode(shared_ptr<ListNode<int>>* node, shared_ptr<ListNode<int>>* tail)
{
	(*tail)->next = *node;
	*tail = *node;
	*node = (*node)->next;
}

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1, 
	shared_ptr<ListNode<int>> L2) {

	shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>();
	auto tail = dummy_head;

	while (L1 && L2) {
		AppendNode(L1->data <= L2->data ? &L1 : &L2, &tail);
	}

	tail->next = L1 ? L1 : L2;

	return dummy_head->next;
}
//shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
//	shared_ptr<ListNode<int>> L2) {
//	shared_ptr<ListNode<int>> head = nullptr;
//	shared_ptr<ListNode<int>> cursor = nullptr;
//
//	while (L1 != nullptr && L2 != nullptr) {
//		shared_ptr<ListNode<int>> node;
//
//		if (L1->data < L2->data) {
//			node = std::make_shared<ListNode<int>>(L1->data);
//			L1 = L1->next;
//		}
//		else {
//			node = std::make_shared<ListNode<int>>(L2->data);
//			L2 = L2->next;
//		}
//
//		if (head == nullptr) {
//			head = node;
//			cursor = node;
//		}
//		else {
//			cursor->next = node;
//			cursor = cursor->next;
//		}
//	}
//
//	while (L1 != nullptr) {
//		if (head == nullptr) {
//			head = std::make_shared<ListNode<int>>(L1->data);
//			cursor = head;
//		}
//		else {
//			cursor->next = std::make_shared<ListNode<int>>(L1->data);
//			cursor = cursor->next;
//		}
//		L1 = L1->next;
//	}
//
//	while (L2 != nullptr) {
//		if (head == nullptr) {
//			head = std::make_shared<ListNode<int>>(L2->data);
//			cursor = head;
//		}
//		else {
//			cursor->next = std::make_shared<ListNode<int>>(L2->data);
//			cursor = cursor->next;
//		}
//		L2 = L2->next;
//	}
//
//	return head;
//}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "L1", "L2" };
	return GenericTestMain(args, "sorted_lists_merge.cc",
		"sorted_lists_merge.tsv", &MergeTwoSortedLists,
		DefaultComparator{}, param_names);
}
