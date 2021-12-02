#include <fstream>
#include <iostream>
#include <string>

void main()
{
	std::ifstream file("input.txt");

	int aim = 0;
	int horizontal = 0;
	int depth = 0;

	std::string line;
	while (std::getline(file, line))
	{
		auto pos = line.find(' ');
		auto command = line.substr(0, pos);
		auto arg = std::stoi(line.substr(pos));

		switch (command.c_str()[0])
		{
		case 'f':
			horizontal += arg;
			depth += aim * arg;

			break;
		case 'd':
			aim += arg;

			break;
		case 'u':
			aim -= arg;

			break;
		}
	}

	std::cout << horizontal * depth << std::endl;

	file.close();
}