#include "TrieDict.h"
#include <stdexcept>
#include <string>


TrieNode::TrieNode()
{
	_children = new TrieNode * [ALPHABET_SIZE] {nullptr};
}


TrieNode::~TrieNode()
{
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		delete _children[i];
	}
	delete[] _children;
}


bool TrieNode::_isValidSymbol(char c)
{
	return (c >= 'a' && c <= 'z');
}


void TrieNode::insert(const std::string& key)
{
	TrieNode* node = this;

	for (size_t i = 0; i < key.length(); i++)
	{
		if (!_isValidSymbol(key[i]))
			throw std::domain_error("bad symbols in dictionary");

		size_t index = key[i] - 'a';

		if (!node->_children[index])
			node->_children[index] = new TrieNode();

		node = node->_children[index];
	}

	node->_isEndOfWord = true;
}

TrieNode* TrieNode::search(const std::string& key)
{
	TrieNode* node = this;

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

bool TrieNode::isEmpty() const
{
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		if (this->_children[i])
			return false;
	return true;
}


std::string TrieNode::predict(const std::string& input)
{
	std::string result = input;
	TrieNode* node = search(input);
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


TrieDict::TrieDict()
{
	_root = new TrieNode();
}


TrieDict::~TrieDict()
{
	delete _root;
}


void TrieDict::learnWords()
{
	const std::string dict[10] {
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
		_root->insert(w);
	}
	return;
}


std::string TrieDict::predict(const std::string& input)
{
	return _root->predict(input);
}

