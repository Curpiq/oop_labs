#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MiniDictionary/Dictionary.h"


Dictionary dictionary = {
	{"cat", "кот, кошка"},
	{"ball", "мяч"}
};

Dictionary newDictionary =
{
	{"cat", "кот, кошка"},
	{"ball", "мяч"},
	{"moon", "луна"}
};

string translation;


TEST_CASE("Translate the word that is in the dictionary")
{
	string word;
	translation = "";
	word = "ball";
	bool find = FindTranslation(word, translation, dictionary);
	CHECK(translation == "мяч");

	word = "CAt";
    find = FindTranslation(word, translation, dictionary);
	CHECK(translation == "кот, кошка");
}

TEST_CASE("Fill dictionary from stream")
{
	Dictionary streamDictionary;
	istringstream input("cat\nкот, кошка\nball\nмяч\n");
	DictionaryFilling(input);
	CHECK(dictionary == streamDictionary);
}

TEST_CASE("Adding a translation of an unknown word to the dictionary")
{
	string newWord = "moon";
	translation = "луна";
	AddTranslation(newWord, translation, dictionary);
	CHECK(dictionary == newDictionary);
}

TEST_CASE("Save changed dictionary to file")
{
	ostringstream output;
	SaveDictionary(dictionary, output);
	ostringstream expectedOutput("ball\nмяч\ncat\nкот, кошка\nmoon\nлуна\n");
	CHECK(output.str() == expectedOutput.str());
}