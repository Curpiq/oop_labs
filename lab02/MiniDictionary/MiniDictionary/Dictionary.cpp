#include "Dictionary.h"

Dictionary DictionaryFilling(istream& dictionaryFile)
{
	Dictionary dictionary;
	string word;
	string translation;
	while (getline(dictionaryFile, word) && getline(dictionaryFile, translation))
	{
		transform(word.begin(), word.end(), word.begin(), tolower);
		dictionary.insert(pair<string, string>(word, translation));
	}
	return dictionary;
}

bool FindTranslation(string word, string& translation, const Dictionary& dictionary)
{
	transform(word.begin(), word.end(), word.begin(), tolower);
	if (dictionary.find(word) == dictionary.end())
	{
		return false;
	}
	else
	{
		translation = dictionary.find(word)->second;
		return true;
	}
}

void AddTranslation(string word, const string& translation, Dictionary& dictionary)
{
	transform(word.begin(), word.end(), word.begin(), tolower);
	dictionary.insert(pair<string, string>(word, translation));
}

void SaveDictionary(const Dictionary& dictionary, ostream& dictionaryFile)
{
	for (const auto& line : dictionary)
	{
		dictionaryFile << line.first << "\n" << line.second << "\n";
	}
}