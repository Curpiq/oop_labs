#include "StringDecoder.h"
#include <iostream>
#include <vector>

using namespace std;

const int NUMBER_OF_ENTITY_SYMBOL_PAIRS = 5;
const int MAX_LENGTH_OF_HTML_ENTITY = 6;
const int MIN_LENGTH_OF_HTML_ENTITY = 4;

struct EntitySymbolPair
{
	string htmlEntity;
	string symbol;
};

const vector<EntitySymbolPair> pairOfEntitiyAndSymbol =
{
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

unsigned int FindEntityNumberToDecode(int marker, const string& inputString, int entityNumber)
{
	string str;
	for (int i = marker; ((i < inputString.length()) && (i < marker + MAX_LENGTH_OF_HTML_ENTITY)); i++)
	{
		str += inputString[i];
		if (str.length() >= MIN_LENGTH_OF_HTML_ENTITY)
		{
			for (int j = 0; j < NUMBER_OF_ENTITY_SYMBOL_PAIRS; j++)
			{
				if (pairOfEntitiyAndSymbol[j].htmlEntity == str)
				{
					entityNumber = j;
				}
			}
		}
	}
	return entityNumber;
}

void DecodeEntity(int& entityNumber, int& marker, string& decodedString)
{
	decodedString += pairOfEntitiyAndSymbol[entityNumber].symbol;
	marker += pairOfEntitiyAndSymbol[entityNumber].htmlEntity.length();
	entityNumber = -1;

}

string StringDecoder(const string& inputString)
{
	string decodedString;
	int marker = 0;
	int entityNumber = -1;
	while (marker < inputString.length())
	{
		if (inputString[marker] == '&')
		{
			entityNumber = FindEntityNumberToDecode(marker, inputString, entityNumber);
		}
		if (entityNumber >= 0)
		{
			DecodeEntity(entityNumber, marker, decodedString);
		}
		else
		{
			decodedString += inputString[marker];
			marker++;
		}
	}
	return decodedString;
}