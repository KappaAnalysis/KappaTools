#ifndef TBIOHELPER_H
#define TBIOHELPER_H

#include <iostream>
#include <iomanip>

class OStreamGuard
{
public:
	OStreamGuard(std::ostream &_os);
	~OStreamGuard();
private:
	std::ostream &os;
	std::streamsize p, w;
	std::ios_base::fmtflags flags;
	char f;
};

template<typename T>
void printMatrix(T **matrix, const size_t x, const size_t y, const size_t width = 10)
{
	OStreamGuard guard(std::cout);
	for (size_t i = 0; i < x; ++i)
	{
		for (size_t j = 0; j < y; ++j)
			std::cout << std::setw(width) << matrix[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

#endif
