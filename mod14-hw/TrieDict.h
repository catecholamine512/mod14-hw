#pragma once
#include <string>


const int ALPHABET_SIZE = 26;


class TrieDict {
	TrieDict** _children = nullptr;
	bool _isEndOfWord = false;

	bool _isValidSymbol(char c);

public:
	TrieDict();
	~TrieDict();
	void insert(const std::string& key);
	TrieDict* search(const std::string& key);
	bool isEmpty() const;
	void learnWords();
	std::string predict(const std::string& input);
};

