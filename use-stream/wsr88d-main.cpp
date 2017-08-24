#include "wsr88d-structs.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace nh {

	auto htons = [](unsigned short h)
	{
		return (unsigned short)
			(h << 8 & 0xFF00U |
				h >> 8 & 0x00FFU);
	};

	auto htonl = [](unsigned int h)
	{
		return (unsigned int)
			(h << 24 & 0xFF000000U |
				h << 8 & 0x00FF0000U |
				h >> 8 & 0x0000FF00U |
				h >> 24 & 0x000000FFU);
	};

	auto ntohs = htons;
	auto ntohl = htonl;

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

struct BlockHeader {
	BLOCKHEADMSG header;
	

	BlockHeader() = default;

	friend std::istream& operator>> (std::istream& in, BlockHeader& bh)
	{
		in.read((char *)&bh.header, sizeof(BLOCKHEADMSG));

		ntoh_struct((unsigned char*)&bh.header, bh.size_of_header_member);

		return in;
	}

	friend std::ostream& operator<< (std::ostream& out, BlockHeader& bh)
	{
		cout_struct((unsigned char*)&bh.header, bh.size_of_header_member);

		return out;
	}


private:
	const std::vector<unsigned char> size_of_header_member{2,2,4,4,2,2,2};
};	

struct BlockDescription {
	BLOCKDESCRIPTION description;


	BlockDescription() = default;

	friend std::istream& operator>> (std::istream& in, BlockDescription& bd)
	{
		in.read((char *)&bd.description, sizeof(BLOCKDESCRIPTION));

		ntoh_struct((unsigned char*)&bd.description, bd.size_of_description_member);

		return in;
	}

	friend std::ostream& operator<< (std::ostream& out, BlockDescription& bd)
	{
		cout_struct((unsigned char*)&bd.description, bd.size_of_description_member);

		return out;
	}


private:
	const std::vector<unsigned char> 
		size_of_description_member =  { 2, 4,4, 2,2,2,2,2,2, 2,4,2,4, 2,2,2,2,
			2,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,2,
			2,2,2,2,2,2,2, 2,4,4,4 };
};


struct BlockSymbol {
	BLOCKSYMBOL symbol;
	BLOCKLAYER layerHeader;
	BLOCKRADIAL radialPacket;

	BLOCKGRID gridPacket;

	bool isRadialData = false;
	bool isGridData = false;

	std::vector<std::vector<unsigned char> > radialColors, gridColors;


	BlockSymbol() = default;

	bool is_radial()const
	{
		return isRadialData;
	}

	bool is_grid()const
	{
		return isGridData;
	}

	void read_radial(std::istream& in)
	{
		in.read((char *)&radialPacket, sizeof(BLOCKRADIAL));

		ntoh_struct((unsigned char*)&radialPacket, size_of_radialPacket_member);

		radialColors.resize(360);

		for (auto i = 0; i != radialPacket.radialCount; i++)
		{
			BLOCKRADIALSTRIP oneRadial;


			in.read((char *)&oneRadial, sizeof(BLOCKRADIALSTRIP));

			ntoh_struct((unsigned char*)&oneRadial, size_of_oneRadial_member);

			//std::cout << "oneRadial: " << std::endl;

			//cout_struct((unsigned char*)&oneRadial, size_of_oneRadial_member);

			//std::cout << oneRadial.byteCount << std::endl;

			std::vector<unsigned char> p(oneRadial.byteCount * 2, 0);

			in.read((char *)p.data(), p.size());

			for (auto it = p.begin(); it < p.end(); it += 2)
			{
				std::swap(*it, *(it + 1) );
			}

			std::vector<unsigned char> colorAngle;
			for (auto v : p)
			{
				unsigned char color = v & 0x0F;
				unsigned char span = v>>4 & 0x0F;

				colorAngle.insert(colorAngle.end(), span, color);
			}
			unsigned angle = (oneRadial.angleStart / 10) % 360;
			radialColors[angle] = colorAngle;
		}
	}

	void read_grid(std::istream& in)
	{
		in.read((char *)&gridPacket, sizeof(BLOCKGRID));

		ntoh_struct((unsigned char*)&gridPacket, size_of_gridPacket_member);

		auto row = gridPacket.rowCount;
		gridColors.resize(row);

		for (auto i = 0; i != row; i++)
		{
			unsigned short byteCount = 0;

			in.read((char *)&byteCount, sizeof(unsigned short));
			byteCount = nh::ntohs(byteCount);

			//std::cout <<i<<": "<< byteCount << std::endl;

			std::vector<unsigned char> p(byteCount, 0);

			in.read((char *)p.data(), p.size());

			for (auto it = p.begin(); it < p.end(); it += 2)
			{
				std::swap(*it, *(it + 1));
			}

			std::vector<unsigned char> colorLine;
			for (auto v : p)
			{
				unsigned char color = v & 0x0F;
				unsigned char span = v >> 4 & 0x0F;

				colorLine.insert(colorLine.end(), span, color);
			}
			
			gridColors[i] = colorLine;
		}
	}

	friend std::istream& operator>> (std::istream& in, BlockSymbol& bs)
	{
		in.read((char *)&bs.symbol, sizeof(BLOCKSYMBOL));

		ntoh_struct((unsigned char*)&bs.symbol, bs.size_of_symbol_member);

		in.read((char *)&bs.layerHeader, sizeof(BLOCKLAYER));

		ntoh_struct((unsigned char*)&bs.layerHeader, bs.size_of_layerHeader_member);

		unsigned short packetCode = 0;
		in.read((char *)&packetCode, sizeof(unsigned short));
		packetCode = nh::ntohs(packetCode);

		in.seekg(-2, in.cur);

		switch (packetCode)
		{
		case 0xAF1F:
			bs.isRadialData = true;
			bs.isGridData = false;
			bs.read_radial(in); 
			break;
		case 0xBA0F:
		case 0xBA07:
			bs.isRadialData = false;
			bs.isGridData = true;
			bs.read_grid(in);
			break;

		default:break;
		}
		//
		

		return in;
	}

	friend std::ostream& operator<< (std::ostream& out, BlockSymbol& bs)
	{
		cout_struct((unsigned char*)&bs.symbol, bs.size_of_symbol_member);

		std::cout << "layerHeader: " << std::endl;

		cout_struct((unsigned char*)&bs.layerHeader, bs.size_of_layerHeader_member);

		if (bs.is_radial())
		{
			std::cout << "radialPacket: " << std::endl;

			cout_struct((unsigned char*)&bs.radialPacket, bs.size_of_radialPacket_member);

			unsigned count = 0;
			for (auto line : bs.radialColors)
			{
				std::cout << ++count << ' ';
				for (auto v : line)
				{
					std::cout << ' ' << +v;
				}
				std::cout << std::endl;
			}
		}



		if (bs.is_grid())
		{
			std::cout << "gridPacket: " << std::endl;

			cout_struct((unsigned char*)&bs.gridPacket, bs.size_of_gridPacket_member);

			unsigned count = 0;
			for (auto line : bs.gridColors)
			{
				std::cout << ++count << ' ' ;
				for (auto v : line)
				{
					std::cout << ' ' << +v;
				}
				std::cout << std::endl;
			}

		}
		

		return out;
	}


private:
	const std::vector<unsigned char> size_of_symbol_member{ 2,2,4,2 };
	const std::vector<unsigned char> size_of_layerHeader_member{ 2,4 };
	const std::vector<unsigned char> size_of_radialPacket_member{ 2,2,2,2, 2,2,2 };
	const std::vector<unsigned char> size_of_oneRadial_member{ 2,2,2 };
	const std::vector<unsigned char> size_of_gridPacket_member{ 2,2,2,2, 2,2,2,2, 2,2,2 };
};


int main()//wsr88d_
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