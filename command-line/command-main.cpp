#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	std::string input;

	std::cout << "argc: " << argc << std::endl;
	std::cout << "argv[0]: " << argv[0] << std::endl;

	if (argc > 1) input = argv[1];
	else std::cin >> input;

	std::cout << "hello" << input;

	if (input == "end") return 1;

	return 0;
}