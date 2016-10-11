
// todo - move this file to wiz/bigInt.h

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <wiz/big_int.h>
//#include <wiz/big_fraction.h>

int main(void)
{
	wiz::big_int::BigInt x, y;
	x = wiz::big_int::BigInt(std::vector<long long>{ 1 }, true);
	y = wiz::big_int::BigInt(std::vector<long long>{ 1 }, true);
	wiz::big_int::BigInt Max(std::vector<long long>{ 1, 614511616 }, true);

	y = Max / wiz::big_int::BigInt(std::vector<long long>{ 95448 }, true);

	for (auto& val : y.val)
		std::cout << val << std::endl;

	x = wiz::big_int::BigInt(std::vector< long long >{ 999999999 }, true);
	y = x;
	y = y * y;
	std::cout << "-----" << std::endl;
	
	std::cout << y << std::endl;

	return 0;
}
