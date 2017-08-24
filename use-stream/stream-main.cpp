#include <fstream>
#include <iostream>
#include <string>

void fstream_rw()
{
	auto filename = "fileio.txt";
	auto file = std::fstream(filename, std::ios::out | std::ios::binary | std::ios::in);

	if (!file.good())
	{
		std::cout << "file.good(): " << file.good() << "file.eof(): " << file.eof() << "file.bad(): " << file.bad() << "file.fail(): " << file.fail() << std::endl;
		std::cout << "file " << filename << " has error!" << std::endl;
		std::cerr << "error info: " << std::strerror(errno) << std::endl;
	}

	auto s = std::string("abcde 12345 hijkl");
	file.write(s.data(), s.size());
	file << 123 << "abc" << std::endl;

	file.seekp(5);

	std::cout << (!!(file >> s));

	std::cout << s << std::endl;

	file.seekg(5);

	std::cout << (!!(file >> s));

	std::cout << s << std::endl;

	file.seekg(7);
	std::cout << "file.tellp()" << file.tellp() << std::endl;

	file.read((char *)&s[0], 2);

	std::cout << "file.tellp()" << file.tellp() << std::endl;

}


int stream_main()//
{
	char a[] = { 1,2 };
	char *pc = a;
	short *p = (short *)pc;
	std::cout << *p <<0x0201<< std::endl;
	
	return 0;
}