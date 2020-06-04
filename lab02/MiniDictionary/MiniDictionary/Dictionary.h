#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>

typedef std::map<std::string, std::string> Dictionary;
using namespace std;

Dictionary DictionaryFilling(istream& dictionaryFile);
bool FindTranslation(string word, string& translation, const Dictionary& dictionary);
void AddTranslation(string word, const string& translation, Dictionary& dictionary);
void SaveDictionary(const Dictionary& dictionary, ostream& dictionaryFile);