// HTMLDecode_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTMLDecode/StringDecoder.h"

TEST_CASE("Decoding of string with HTML entities gives decoded string")
{
	std::string str = "cat &amp; dog";
	std::string expected = "cat & dog";
	CHECK(StringDecoder(str) == expected);

	str = "&lt;cat&gt;";
	expected = "<cat>";
	CHECK(StringDecoder(str) == expected);

	str = "cat&apos;s paw";
	expected = "cat's paw";
	CHECK(StringDecoder(str) == expected);

	str = "&quot;meow&quot;";
	expected = "\"meow\"";
	CHECK(StringDecoder(str) == expected);

	str = "&amp;gt;";
	expected = "&gt;";
	CHECK(StringDecoder(str) == expected);

	str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	expected = "Cat <says> \"Meow\". M&M's";
	CHECK(StringDecoder(str) == expected);
}

TEST_CASE("Decoding of empty string gives empty string")
{
	CHECK(StringDecoder("") == "");
}

TEST_CASE("Decoding of string without HTML entities gives unchanged string")
{
	std::string str = "cat";
	CHECK(StringDecoder(str) == str);
}


