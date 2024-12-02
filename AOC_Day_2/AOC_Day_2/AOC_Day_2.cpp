#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template<typename T>
bool isSorted(const std::vector<T>& arr)
{
    if (arr.size() < 2) return false;

    bool ascending = true;
    bool descending = true;

    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < arr[i - 1])
            ascending = false;
        else if (arr[i] > arr[i - 1])
            descending = false;
    }

    return (ascending || descending);
}

std::vector<std::vector<int32_t>> getData()
{
    std::vector<std::vector<int32_t>> data;

	std::ifstream infile("input.txt");
	if (infile.is_open())
	{
        int32_t tmp;

		std::string line;
		while (std::getline(infile, line))
		{
            std::vector<int32_t> lineData;

			std::istringstream lineStream(line);
            while (!lineStream.eof())
            {
                lineStream >> tmp;
                lineData.push_back(tmp);
            }

            data.push_back(lineData);
		}

		infile.close();
	}
	else
	{
		throw std::runtime_error("File input.txt doesn't exist");
	}

    return data;
}

std::vector<std::vector<int32_t>> createDampenedVariations(const std::vector<int32_t>& data)
{
	std::vector<std::vector<int32_t>> variations;

	for (size_t i = 0; i < data.size(); i++)
	{
		std::vector<int32_t> tmp;
		std::copy(data.begin(), data.end(), std::back_inserter(tmp));

		tmp.erase(tmp.begin() + i);

		variations.push_back(tmp);
	}

	return variations;
}

bool isSafe(const std::vector<int32_t>& data)
{
    if (!isSorted(data)) return false;

	for (size_t i = 1; i < data.size(); i++)
	{
		int32_t diff = abs(data[i] - data[i - 1]);

		if (diff == 0 || diff > 3)
			return false;
	}

	return true;
}

size_t safeCount(const std::vector<std::vector<int32_t>>& data)
{
    size_t count = 0;

    for (auto& row : data)
    {
		if (isSafe(row))
			count++;
    }

    return count;
}

size_t safeCountWithDampener(const std::vector<std::vector<int32_t>>& data)
{
	size_t count = 0;

	for (auto& row : data)
	{
		if (isSafe(row))
			count++;
		else
		{
			std::vector<std::vector<int32_t>> variations = createDampenedVariations(row);

			for (auto& drow : variations)
			{
				if (isSafe(drow))
				{
					count++;
					break;
				}
			}
		}
	}

	return count;
}

int main()
{
    std::vector<std::vector<int32_t>> data = getData();

    std::printf("Safe reports: %zu\r\n", safeCount(data));
	std::printf("Safe reports with dampener: %zu\r\n", safeCountWithDampener(data));

    return 0;
}
