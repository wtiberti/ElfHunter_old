/*
* This file is part of ElfHunter software.
*
* ElfHunter is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ElfHunter is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ElfHunter.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright (C) 2012 Walter Tiberti
*/

/*
* Filename: ElfAuxTypes.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfAuxTypes.h
 * @brief Auxiliary primitives definition */
#ifndef ElfAuxTypes_H
	#define ElfAuxTypes_H

	#include <vector>

	/** @brief SectStruct definition
	 *
	 * This struct is used to store all the meaningful
	 * values for each string section */
	typedef struct
	{
		int sect_n; ///< Index of the section
		__uint64_t index_name; ///< Index of the name (inside the section header string table)
		__uint64_t offset; ///< Offset to section
		char *addr; ///< Address to section
		__uint64_t size; ///< Size of the section
	} SectStruct;

	
	/** @brief SymData64 definition
	 *
	 * This structure is used to keep track of all
	 * the symbols in a ELF file (64-bit) */
	typedef struct
	{
		std::vector< Elf64_Sym * > symv; ///< Vector of pointer to symbol
		std::vector< __uint64_t > offsets; ///< Vector of symbol offsets
		std::vector< int > sects; ///< Vector of symbols sections
	} SymData64;

	
	/** @brief SymData32 definition
	 *
	 * This structure is used to keep track of all
	 * the symbols in a ELF file (32-bit) */
	typedef struct
	{
		std::vector< Elf32_Sym * > symv; ///< Vector of pointer to symbol
		std::vector< __uint64_t > offsets; ///< Vector of symbol offsets
		std::vector< int > sects; ///< Vector of symbols sections
	} SymData32;

#endif