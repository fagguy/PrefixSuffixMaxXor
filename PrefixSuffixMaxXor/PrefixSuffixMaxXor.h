#pragma once

#include "BinaryTrie.h"
#include <vector>
#include <algorithm>

unsigned int N;
ullong *inputArray, *PrefixArray, *SuffixArray;
BinaryTrie trie;
ullong maxXor = 0;

void GetInput();
void GeneratePrefixArray();
void GenerateSuffixArray();
void AddSuffixArrayToTrie();
void GetPrefixSuffixMaxXor();
