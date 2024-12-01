#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <cassert>

std::tuple<std::vector<int32_t>, std::vector<int32_t>> getData()
{
	std::vector<int32_t> group1;
	std::vector<int32_t> group2;

	std::ifstream infile("input.txt");
	if (infile.is_open())
	{
		int32_t a, b;
		while (infile >> a >> b)
		{
			group1.push_back(a);
			group2.push_back(b);
		}

		infile.close();
	}
	else
	{
		throw std::runtime_error("File input.txt doesn't exist");
	}

	return { group1, group2 };
}

int32_t partOne()
{
	int32_t distance = 0;

	auto [ group1, group2 ] = getData();
	assert(group1.size() == group2.size());

	while (!group1.empty())
	{
		std::vector<int32_t>::iterator group1Min = std::ranges::min_element(group1);
		std::vector<int32_t>::iterator group2Min = std::ranges::min_element(group2);

		distance += std::abs(*group1Min - *group2Min);

		group1.erase(group1Min);
		group2.erase(group2Min);
	}

	return distance;
}

int32_t partTwo()
{
	int32_t similarityScore = 0;
	
	auto [group1, group2] = getData();

	for (auto& itemG1 : group1)
	{
		int32_t count = 0;

		for (auto& itemG2 : group2)
		{
			if (itemG1 == itemG2)
				count++;
		}

		similarityScore += itemG1 * count;
	}

	return similarityScore;
}

int main()
{
	std::printf("Final distance: %d\r\n", partOne());
	std::printf("Similarity score: %d\r\n", partTwo());

	return 0;
}