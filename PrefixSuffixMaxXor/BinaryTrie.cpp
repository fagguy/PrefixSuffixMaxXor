#include "BinaryTrie.h"

BinaryTrie::BinaryTrie()
{
	_root = unique_ptr<_node>(new _node);
}

BinaryTrie::~BinaryTrie()
{
}

void BinaryTrie::Insert(bitset<WORD_SIZE>& binaryString)
{
	_node * current = &(*_root);

	for (int idx = WORD_SIZE - 1; idx >= 0; --idx)
	{
		if (!current->child[binaryString[idx]]) // append a new node if it does not exist
		{
			this->__CreateNodeAtPointer(current->child[binaryString[idx]], current);
		}

		current = &(*current->child[binaryString[idx]]); // set current pointer to next node
	}

	++current->occurence;
}

bool BinaryTrie::Find(bitset<WORD_SIZE>& binaryString)
{
	return this->__Find(binaryString);
}

bool BinaryTrie::Remove(bitset<WORD_SIZE>& binaryString)
{
	// tries to get the last node of the path that represents the binary string
	_node * node = this->__Find(binaryString);
	// you can't remove what does not exist
	if (!node) return false;

	// decrement counter and return as a success
	// don't remove since it still has occurences
	if (--node->occurence > 0) return true;

	while (!this->__HasFork(node->parent)) // find the first fork from the end
	{
		node = node->parent;
	}

	// find the child pointer that leads down the path
	for (unsigned int idx = 0; idx < 2; ++idx)
	{
		if (node->parent->child[idx].get() == node)
		{
			node->parent->child[idx].reset(); // remove the useless dangly bits
			break;
		}
	}

	return true;
}

ullong BinaryTrie::QueryMaxXorCombination(bitset<WORD_SIZE>& binaryString)
{
	bitset<WORD_SIZE> xorResult;
	_node * current = &(*_root);

	// if the trie is empty, then return the input itself
	if (!this->__HasChildren(current)) return binaryString.to_ullong();

	for (int idx = WORD_SIZE - 1; idx >= 0; --idx)
	{
		if (current->child[!(binaryString[idx])]) // path representing an inverse bit is found
		{
			xorResult[idx] = 1; // XOR of two different bits results in '1'
			current = &(*current->child[!(binaryString[idx])]);
		}
		else // cannot find path representing an inverse bit
		{
			xorResult[idx] = 0; // XOR of two same bits results in '0'
			current = &(*current->child[(binaryString[idx])]);
		}
	}

	return xorResult.to_ullong();
}

BinaryTrie::_node * BinaryTrie::__CreateNodeAtPointer(unique_ptr<_node>& pointer, _node * parent)
{
	pointer = unique_ptr<_node>(new _node);
	pointer->parent = parent;

	return &(*pointer);
}

BinaryTrie::_node * BinaryTrie::__Find(bitset<WORD_SIZE>& binaryString)
{
	_node * current = &(*_root);

	for (int idx = WORD_SIZE - 1; idx >= 0; --idx)
	{
		// return null if it does not exist
		if (!current->child[binaryString[idx]]) return nullptr;

		current = &(*current->child[binaryString[idx]]); // set current pointer to next node
	}

	return current;
}

bool BinaryTrie::__HasChildren(_node * node)
{
	return (node->child[0] || node->child[1]);
}

bool BinaryTrie::__HasFork(_node * node)
{
	return (node->child[0] && node->child[1]);
}



int main()
{
	BinaryTrie trie;

	trie.Insert(bitset<WORD_SIZE>("1011"));
	trie.Insert(bitset<WORD_SIZE>("1111"));
	trie.Insert(bitset<WORD_SIZE>("1111"));

	trie.Remove(bitset<WORD_SIZE>("1111"));
	trie.Remove(bitset<WORD_SIZE>("1111"));

	trie.Insert(bitset<WORD_SIZE>("1111"));

	if (trie.Find(bitset<WORD_SIZE>("1111"))) cout << "Found!" << endl;
	else cout << "Not found..." << endl;

	system("Pause");
	return 0;
}
