#include "TextFileUtil.h"
#include <fstream>

std::string readTextFile(const char* location)
{
	std::ifstream file(location);
	std::string out;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			out = out + line + "\n";
		}
		file.close();
	}

	return out;
}
