#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>

std::regex mul_regex("mul\\((\\d+),(\\d+)\\)");
std::regex mul_and_statements_regex("(mul\\((\\d+),(\\d+)\\)|do\\(\\)|don\\'t\\(\\))");

std::string getData()
{
	std::string data;

	std::ifstream infile("input.txt");
	if (infile.is_open())
	{
		data = std::string(std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>());
		infile.close();
	}
	else
	{
		throw std::runtime_error("File input.txt doesn't exist");
	}

	return data;
}

int32_t sumMultiplyNotCorrupted(const std::string& data)
{
	auto words_begin = std::sregex_iterator(data.begin(), data.end(), mul_regex);
	auto words_end = std::sregex_iterator();

	int32_t sum = 0;

	for (std::sregex_iterator i = words_begin; i != words_end; ++i)
	{
		std::smatch match = *i;
		std::string match_str = match.str();

		std::smatch group_match;
		std::regex_match(match_str, group_match, mul_regex);

		int32_t val1, val2;
		std::istringstream ss1(group_match[1].str());
		std::istringstream ss2(group_match[2].str());

		ss1 >> val1;
		ss2 >> val2;

		sum += val1 * val2;
	}

	return sum;
}

int32_t sumMultiplyNotCorruptedWithStatements(const std::string& data)
{
	auto words_begin = std::sregex_iterator(data.begin(), data.end(), mul_and_statements_regex);
	auto words_end = std::sregex_iterator();

	bool enabled = true;
	int32_t sum = 0;

	for (std::sregex_iterator i = words_begin; i != words_end; ++i)
	{
		std::smatch match = *i;
		std::string match_str = match.str();

		std::smatch group_match;
		if (enabled && std::regex_match(match_str, group_match, mul_regex))
		{
			int32_t val1, val2;
			std::istringstream ss1(group_match[1].str());
			std::istringstream ss2(group_match[2].str());

			ss1 >> val1;
			ss2 >> val2;

			sum += val1 * val2;
		}
		else if (match_str == "do()")
			enabled = true;
		else if (match_str == "don't()")
			enabled = false;
	}

	return sum;
}

int main()
{
	std::string data = getData();

	std::printf("Sum of multiply not corrupted: %u\r\n", sumMultiplyNotCorrupted(data));
	std::printf("Sum of multiply not corrupted with statements: %u\r\n", sumMultiplyNotCorruptedWithStatements(data));

    return 0;
}