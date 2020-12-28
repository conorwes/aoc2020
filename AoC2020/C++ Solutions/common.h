#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

inline std::vector<std::string> split(std::string str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);

    std::string worker;
    while (std::getline(ss, worker, delimiter)) {
        tokens.push_back(worker);
    }

    return tokens;
}

std::vector<std::string> split(const std::string &original, const std::string &delimiter, int maxSplits = -1)
{
	std::vector<std::string> result;
	int splits = 0;
	size_t offset = 0;

	while (true)
	{
		if (splits == maxSplits)
		{
			break;
		}
		size_t pos = original.find(delimiter, offset);
		if (pos == std::string::npos)
		{
			break;
		}
		result.push_back(original.substr(offset, pos - offset));
		offset = pos + delimiter.length();
	}
	result.push_back(original.substr(offset));
	return result;
}

inline std::string trim(std::string str) {
    size_t beginPos = str.find_first_not_of(" \t");
    if (beginPos == std::string::npos) {
        return "";
    }

    size_t endPos = str.find_last_not_of(" \t");
    size_t len = endPos - beginPos + 1;

    return str.substr(beginPos, len);
}

std::vector<std::string> readLines(const std::string &basename)
{
	std::ifstream in(basename);
	std::string buffer;
	std::vector<std::string> lines;
	while (getline(in, buffer))
	{
		lines.push_back(buffer);
	}
	return lines;
}

std::vector<std::vector<std::string>> readSections(const std::string &basename) {
    auto lines = readLines(basename);
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> currentSection;
    for (const auto& line: lines) {
        if (line.empty()) {
            result.push_back(currentSection);
            currentSection = {};
        }
        else {
            currentSection.push_back(line);
        }
    }
    result.push_back(currentSection);
    return result;
}