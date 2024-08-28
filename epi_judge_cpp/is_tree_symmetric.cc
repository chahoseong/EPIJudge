#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <vector>

using std::vector;

void SerializeTree(const unique_ptr<BinaryTreeNode<int>>& tree, bool leftFirst, vector<BinaryTreeNode<int>*>& serialized);

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
	if (tree == nullptr) {
		return true;
	}

	vector<BinaryTreeNode<int>*> leftTreeSerialized;
	SerializeTree(tree->left, true, leftTreeSerialized);

	vector<BinaryTreeNode<int>*> rightTreeSerialized;
	SerializeTree(tree->right, false, rightTreeSerialized);

	if (leftTreeSerialized.size() != rightTreeSerialized.size()) {
		return false;
	}

	int size = leftTreeSerialized.size();
	for (int i = 0; i < size; ++i) {
		bool leftIsNull = leftTreeSerialized[i] == nullptr;
		bool rightIsNull = rightTreeSerialized[i] == nullptr;

		if (leftIsNull != rightIsNull) {
			return false;
		}

		if (leftIsNull && rightIsNull) {
			continue;
		}

		if (leftTreeSerialized[i]->data != rightTreeSerialized[i]->data) {
			return false;
		}
	}

	return true;
}

void SerializeTree(const unique_ptr<BinaryTreeNode<int>>& tree, bool leftFirst, vector<BinaryTreeNode<int>*>& serialized)
{
	serialized.push_back(tree.get());

	if (tree != nullptr) {
		if (leftFirst) {
			SerializeTree(tree->left, leftFirst, serialized);
			SerializeTree(tree->right, leftFirst, serialized);
		}
		else {
			SerializeTree(tree->right, leftFirst, serialized);
			SerializeTree(tree->left, leftFirst, serialized);
		}
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
		&IsSymmetric, DefaultComparator{}, param_names);
}
