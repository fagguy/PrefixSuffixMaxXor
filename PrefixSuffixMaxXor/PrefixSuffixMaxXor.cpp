#include "PrefixSuffixMaxXor.h"

int main()
{
	GetInput();

	GeneratePrefixArray();
	maxXor = *max_element(PrefixArray, PrefixArray + N);

	GenerateSuffixArray();
	maxXor = max(maxXor, *max_element(SuffixArray + 1, SuffixArray + N));

	AddSuffixArrayToTrie();
	GetPrefixSuffixMaxXor();

	cout << "Max XOR is: " << maxXor << endl;

	system("Pause");
	delete[] inputArray;
	delete[] PrefixArray;
	delete[] SuffixArray;

	return 0;
}

void GetInput()
{
	cin >> N;

	inputArray = new ullong[N];

	for (unsigned int idx = 0; idx < N; ++idx)
	{
		cin >> inputArray[idx];
	}
}

void GeneratePrefixArray()
{
	PrefixArray = new ullong[N];
	PrefixArray[0] = inputArray[0];

	for (unsigned int idx = 1; idx < N; ++idx)
	{
		PrefixArray[idx] = PrefixArray[idx - 1] ^ inputArray[idx];
	}
}

void GenerateSuffixArray()
{
	SuffixArray = new ullong[N];
	SuffixArray[N - 1] = inputArray[N - 1];

	for (unsigned int idx = N - 2; idx > 0; --idx)
	{
		SuffixArray[idx] = SuffixArray[idx + 1] ^ inputArray[idx];
	}
}

void AddSuffixArrayToTrie()
{
	for (unsigned int idx = N - 1; idx > 0; --idx)
	{
		trie.Insert(SuffixArray[idx]);
	}
}

void GetPrefixSuffixMaxXor()
{
	for (unsigned int idx = 0; idx < N - 2; ++idx)
	{
		maxXor = max(maxXor, trie.QueryMaxXorCombination(PrefixArray[idx]));
		trie.Remove(SuffixArray[idx + 1]);
	}
}
