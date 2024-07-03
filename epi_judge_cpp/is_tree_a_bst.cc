#include <memory>
#include <queue>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

struct Entry {
	const unique_ptr<BinaryTreeNode<int>>& node;
	int lower, upper;
};

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
	std::queue<Entry> queue;

	queue.emplace(Entry{ tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max() });
	while (!queue.empty()) {
		Entry entry = queue.front();
		queue.pop();

		if (entry.node == nullptr) {
			continue;
		}

		if (entry.node->data < entry.lower || entry.node->data > entry.upper) {
			return false;
		}

		if (entry.node->left != nullptr) {
			queue.emplace(Entry{ entry.node->left, entry.lower, entry.node->data });
		}
		if (entry.node->right != nullptr) {
			queue.emplace(Entry{ entry.node->right, entry.node->data, entry.upper });
		}
	}

	return true;
}



int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
		&IsBinaryTreeBST, DefaultComparator{}, param_names);
}
