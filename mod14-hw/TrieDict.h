#pragma once
#include <string>


const int ALPHABET_SIZE = 26;


class TrieNode
{
	TrieNode** _children = nullptr;
	bool _isEndOfWord = false;

	static bool _isValidSymbol(char c);

public:
	TrieNode();
	~TrieNode();
	void insert(const std::string& key);
	TrieNode* search(const std::string& key);
	bool isEmpty() const;
	std::string predict(const std::string& input);
};


class TrieDict
{
	TrieNode* _root = nullptr;

public:
	TrieDict();
	~TrieDict();
	void learnWords();
	std::string predict(const std::string& input);
};

