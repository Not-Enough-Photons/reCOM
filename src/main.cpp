#include <iostream>
#include "math/zmath_main.h"

int main()
{
	std::cout << "Identity matrix: " << std::endl;
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			std::cout << zdb::Identity().m[row][column] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Identity matrix multiplied with another identity: " << std::endl;
	zdb::Matrix4x4 mat = zdb::Identity() * zdb::Identity();
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			std::cout << zdb::Identity().m[row][column] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Identity matrix multiplied with a different matrix: " << std::endl;
	zdb::Matrix4x4 mat1 = zdb::Identity();
	zdb::Matrix4x4 mat2 = {
		66.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 115.2f, 0.0f, 0.0f,
		0.0f, 0.0f, 75.3f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	zdb::Matrix4x4 output = mat1 * mat2 * 2.0f;
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			std::cout << output.m[row][column] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return 0;
}