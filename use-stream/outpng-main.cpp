#include <iostream>
#include <vector>

#include "CImg/CImg.h"
#include "wsr88d.h"
#include "max_sum.h"

//获取雷达发射率对应的RGBA值
std::vector<unsigned> getReflectivityColor(int level)
{

	unsigned r = 0, g = 0, b = 0, alpha = 255;

	switch (level)
	{

	case 0:
	{
		r = 0, g = 172, b = 164; break;
	}
	case 1:
	{
		r = 192, g = 192, b = 254; break;
	}
	case 2:
	{
		r = 112, g = 114, b = 238; break;
	}
	case 3:
	{
		r = 30, g = 38, b = 208; break;
	}
	case 4:
	{
		r = 166, g = 252, b = 168; break;
	}
	case 5:
	{
		r = 0, g = 234, b = 0; break;
	}
	case 6:
	{
		r = 16, g = 146, b = 26; break;
	}
	case 7:
	{
		r = 252, g = 244, b = 100; break;
	}
	case 8:
	{
		r = 200, g = 200, b = 2; break;
	}
	case 9:
	{
		r = 140, g = 140, b = 0; break;
	}
	case 10:
	{
		r = 254, g = 172, b = 172; break;
	}
	case 11:
	{
		r = 254, g = 100, b = 92; break;
	}
	case 12:
	{
		r = 238, g = 2, b = 48; break;
	}
	case 13:
	{
		r = 212, g = 142, b = 254; break;
	}
	case 14:
	{
		r = 170, g = 36, b = 250; break;
	}
	default:
	{
		alpha = 0;
	}
	}


	return { r, g, b, alpha };
}

int main()
{
	namespace CI = cimg_library;

	std::cout << "sizeof(BLOCKHEADMSG): " << sizeof(BLOCKHEADMSG) << std::endl;
	std::cout << "sizeof(BLOCKDESCRIPTION) " << sizeof(BLOCKDESCRIPTION) << std::endl;

	static_assert(sizeof(BLOCKHEADMSG) == 18, "error struct BLOCKHEADMSG size");
	static_assert(sizeof(BLOCKDESCRIPTION) == 102, "error struct BLOCKDESCRIPTION size");

	BlockHeader bh;
	BlockDescription bd;
	BlockSymbol bs;

	std::string filename;
	std::ifstream fin;

	while (std::cout << "filename: " &&std::cin >> filename)
	{
		fin.open(filename, fin.in | fin.binary);

		if (!fin)
		{
			std::cout << "file " << filename << " open fail!" << std::endl;
			continue;
		}

		fin >> bh;
		//std::cout << "BlockHeader:\n" << bh;

		fin >> bd;//<< std::hex << std::showbase
		//std::cout << "BlockDescription:\n" << bd;

		fin >> bs;
		//std::cout << "BlockSymbol:\n" << bs;


		fin.close();


		if (bs.is_radial())
		{

		}
		else if (bs.is_grid())
		{
			auto& gridLevel = bs.gridColors;
			unsigned scale = 4, 
				row = gridLevel.size(), col = gridLevel[0].size(),
				height = row*scale, width = col*scale;

			CI::CImg<unsigned char> gridPng(width, height, 1, 3);
			gridPng.fill(0);

			for (auto y = 0; y < row; y++)
			{
				for(auto x = 0; x < col; x++)
				{
					if (x < gridLevel[y].size())
					{
						auto level = gridLevel[y][x];
					
						if (level > 0)
						{
							auto color = getReflectivityColor(level);
							gridPng.draw_rectangle(x*scale, y*scale, (x+1)*scale, (y+1)*scale, color.data());
						}
					
					}
				}
			}

			for(auto& array : gridLevel) //it will modify bs.gridColors
			{
				for(auto& v: array) {v -= 10; };
			};
			
			auto range = max_sum_submatrix(gridLevel);
			std::cout << "max_add: " << range.value << " left: " << range.left << " right: " << range.right
				<< " top: " << range.top << " bottom: " << range.bottom << std::endl;

			std::vector<unsigned char> blue = { 0, 0, 255 };
			gridPng.draw_rectangle(range.left*scale, range.top*scale, range.right*scale, range.bottom*scale, blue.data(), 1, ~0U);
			gridPng.display();
			gridPng.save((filename + ".png").c_str());
		}
	}

	return 0;
}

