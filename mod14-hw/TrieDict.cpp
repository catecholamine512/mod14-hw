#include "TrieDict.h"
#include <stdexcept>
#include <string>


TrieDict::TrieDict()
{
	_children = new TrieDict * [ALPHABET_SIZE] {nullptr};
}


TrieDict::~TrieDict()
{
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		delete _children[i];
	}
	delete[] _children;
}


bool TrieDict::_isValidSymbol(char c)
{
	return (c >= 'a' && c <= 'z');
}


void TrieDict::insert(const std::string& key)
{
	TrieDict* node = this;

	for (size_t i = 0; i < key.length(); i++)
	{
		if (!_isValidSymbol(key[i]))
			throw std::domain_error("bad symbols in dictionary");

		size_t index = key[i] - 'a';

		if (!node->_children[index])
			node->_children[index] = new TrieDict();

		node = node->_children[index];
	}

	node->_isEndOfWord = true;
}

TrieDict* TrieDict::search(const std::string& key)
{
	TrieDict* node = this;

	for (size_t i = 0; i < key.length(); i++)
	{
		if (!_isValidSymbol(key[i]))
			return nullptr;

		size_t index = key[i] - 'a';
		if (!node->_children[index])
			return nullptr;

		node = node->_children[index];
	}

	return node;
}

bool TrieDict::isEmpty() const
{
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		if (this->_children[i])
			return false;
	return true;
}


void TrieDict::learnWords()
{
	const std::string dict[10]{
		"asd",
		"qwe",
		"rty",
		"zxc",
		"fgh",
		"asdfgh",
		"vbn",
		"qwerty",
		"zxcvbn",
		"apple"
	};
	for (const auto& w : dict)
	{
		insert(w);
	}
	return;
}


std::string TrieDict::predict(const std::string& input)
{
	std::string result = input;
	TrieDict* node = search(input);
	if (node == nullptr) return result;
	while (node != nullptr && !node->_isEndOfWord)
	{
		bool childFound = false;
		for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		{
			if (node->_children[i] != nullptr)
			{
				node = node->_children[i];
				childFound = true;
				result += 'a' + i;
				break;
			}
		}
		if (!childFound) break;
	}
	return result;
}
