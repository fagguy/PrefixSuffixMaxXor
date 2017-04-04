#pragma once

#include <iostream>
#include <memory>
#include <bitset>

#define WORD_SIZE 64 // all the binary strings added to the trie have the same length

using namespace std;
typedef unsigned long long ullong;

class BinaryTrie
{
private:
	struct _node
	{
		_node * parent = nullptr;
		unique_ptr<_node> child[2];
		unsigned int occurence = 0;
	};
	unique_ptr<_node> _root;

public:
	BinaryTrie();
	~BinaryTrie();

	// insert unsigned long long into trie
	void Insert(bitset<WORD_SIZE> binaryString);
	// check if unsigned long long exists in trie
	bool Find(bitset<WORD_SIZE> binaryString);
	// remove unsigned long long from trie
	bool Remove(bitset<WORD_SIZE> binaryString);
	// check the maximum XOR combination possible based on items in the trie and the input
	ullong QueryMaxXorCombination(bitset<WORD_SIZE> binaryString);

private:
	_node * __CreateNodeAtPointer(unique_ptr<_node>& pointer, _node * parent);
	_node * __Find(bitset<WORD_SIZE>& binaryString);

	static bool __HasChildren(_node * node);
	static bool __HasFork(_node * node);
};