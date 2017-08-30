#include "wsr88d.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace nh {

	unsigned short htons(unsigned short h)
	{
		return (unsigned short)
			(h << 8 & 0xFF00U |
				h >> 8 & 0x00FFU);
	};

	unsigned int htonl(unsigned int h)
	{
		return (unsigned int)
			(h << 24 & 0xFF000000U |
				h << 8 & 0x00FF0000U |
				h >> 8 & 0x0000FF00U |
				h >> 24 & 0x000000FFU);
	};


	unsigned short ntohs(unsigned short h) 
	{
		return htons(h);
	}
	
	unsigned int ntohl(unsigned int h)
	{
		return htonl(h);
	}

}

void ntoh_struct( unsigned char* pc, const std::vector<unsigned char>& size_of_member)
{

	for (auto v : size_of_member)
	{
		if (v == 2)
		{
			unsigned short *p = (unsigned short *)pc;
			*p = nh::ntohs(*p);
		}
		else if (v == 4)
		{
			unsigned int *p = (unsigned int *)pc;
			*p = nh::ntohl(*p);
		}
		pc += v;
	}

}

void cout_struct(unsigned char* pc, const std::vector<unsigned char>& size_of_member)
{
	for (auto v : size_of_member)
	{
		if (v == 2)
		{
			short *p = (short *)pc;
			std::cout << *p << std::endl;
		}
		else if (v == 4)
		{
			int *p = (int *)pc;
			std::cout << *p << std::endl;
		}
		pc += v;
	}
}




int wsr88d_main()//
{
	std::cout << "sizeof(BLOCKHEADMSG): " << sizeof(BLOCKHEADMSG) << std::endl;
	std::cout << "sizeof(BLOCKDESCRIPTION) " << sizeof(BLOCKDESCRIPTION) << std::endl;

	static_assert(sizeof(BLOCKHEADMSG) == 18,"error struct BLOCKHEADMSG size");
	static_assert(sizeof(BLOCKDESCRIPTION) == 102, "error struct BLOCKDESCRIPTION size");

	BlockHeader bh;
	BlockDescription bd;
	BlockSymbol bs;

	std::string filename;
	std::ifstream fin;

	while (std::cout<<"filename: " &&std::cin >> filename)
	{
		fin.open(filename, fin.in|fin.binary);

		if ( !fin )
		{
			std::cout << "file " << filename << " open fail!" << std::endl;
			continue;
		}

		fin >> bh;
		std::cout << "BlockHeader:\n" << bh;

		fin >> bd;//<< std::hex << std::showbase
		std::cout  << "BlockDescription:\n" << bd;

		fin >> bs;
		std::cout << "BlockSymbol:\n" << bs;


		fin.close();
	}

	return 0;
}