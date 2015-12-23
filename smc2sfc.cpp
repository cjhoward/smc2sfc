/*
 * Copyright (C) 2015  Christopher J. Howard
 *
 * This file is part of SMC2SFC.
 *
 * SMC2SFC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SMC2SFC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SMC2SFC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

#define HEADER_SIZE 512
#define MAGIC_OFFSET 8
#define MAGIC_A 0xAA
#define MAGIC_B 0xBB

int main(int argc, const char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "usage: smc2sfc <input> <output>" << std::endl;
		return EXIT_FAILURE;
	}

	std::ifstream input(argv[1], std::ios::binary);
	if (!input.is_open())
	{
		std::cerr << "Failed to open input file \"" << argv[1] << "\"" << std::endl;
		return EXIT_FAILURE;
	}

	std::ofstream output(argv[2], std::ios::binary);
	if (!output.is_open())
	{
		std::cerr << "Failed to open output file \"" << argv[2] << "\"" << std::endl;
		return EXIT_FAILURE;
	}

	// Check for SMC/SWC header
	unsigned char magicA;
	unsigned char magicB;
	input.seekg(MAGIC_OFFSET);
	input >> magicA;
	input >> magicB;
	input.seekg(0);

	if (magicA == MAGIC_A && magicB == MAGIC_B)
	{
		// Skip past header
		input.rdbuf()->pubseekpos(HEADER_SIZE);
	}
	else
	{
		std::cerr << "No SMC/SWC header detected. Copying file..." << std::endl;
	}

	output << input.rdbuf();

	input.close();
	output.close();

	return EXIT_SUCCESS;
}
