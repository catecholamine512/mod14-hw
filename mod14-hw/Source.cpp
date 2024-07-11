#include <iostream>
#include <string>
#include "TrieDict.h"


int main(void)
{
	std::cout << "begin to type your word, press [enter] to autocomplete" << std::endl;
	std::cout << "EOF ([Ctrl+Z]) to exit" << std::endl;

	TrieDict dict;
	dict.learnWords();

	std::string input;
	while (std::getline(std::cin, input))
	{
		std::string output = dict.predict(input);
		std::cout << output << std::endl;
	}

	return 0;
}