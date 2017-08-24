#include <bitset>
#include <vector>
#include <iostream>

int main() 
{
	int x = 5;
	std::cout << std::bitset<32>(x) << std::endl;



	std::vector<bool> v = { 1, 0 };
	for (auto& b : v) 
	{
		std::cout << (b = !b) << ' ';
	} // error

	for (auto &b : v)
	{
		std::cout << b  << ' ';
	} // error


}