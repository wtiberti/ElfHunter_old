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
* Filename: SelectionInfo.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#ifndef SelectionInfo_H
	#define SelectionInfo_H
	
	#include <unistd.h>
	
	/** @brief SelectionInfo struct
	 * 
	 * This structure is used to store the relative starting offset
	 * and the size of members of the various ELF structure */
	typedef struct
	{
		__uint64_t start; /// Start of range
		__uint64_t size; /// Size
	} SelectionInfo;
	
	/** @brief ELF file header SelectionInfo structs */
	const SelectionInfo elfhdr_selection_info[] =
	{
		{ 0, 4 },
		{ 4, 1 },
		{ 5, 1 },
		{ 6, 1 },
		{ 7, 1 },
		{ 8, 1 },
		{ 0, 16 }, /* NOTE select all IDENT fields */
		{ 0x10, 2 },
		{ 0x12, 2 },
		{ 0x14, 4 },
		{ 0x18, 4 },
		{ 0x1C, 4 },
		{ 0x20, 4 },
		{ 0x24, 4 },
		{ 0x28, 2 },
		{ 0x2A, 2 },
		{ 0x2C, 2 },
		{ 0x2E, 2 },
		{ 0x30, 2 },
		{ 0x32, 2 }
	};
	
	/** @brief ELF file header SelectionInfo structs (64bit) */
	const SelectionInfo elfhdr_selection_info64[] =
	{
		{ 0, 4 },
		{ 4, 1 },
		{ 5, 1 },
		{ 6, 1 },
		{ 7, 1 },
		{ 8, 1 },
		{ 0, 16 }, /* NOTE select all IDENT fields */
		{ 0x10, 2 },
		{ 0x12, 2 },
		{ 0x14, 4 },
		{ 0x18, 8 },
		{ 0x20, 8 },
		{ 0x28, 8 },
		{ 0x30, 4 },
		{ 0x34, 2 },
		{ 0x36, 2 },
		{ 0x38, 2 },
		{ 0x3A, 2 },
		{ 0x3C, 2 },
		{ 0x3E, 2 }
	};
	
	/** @brief Program header SelectionInfo structs */
	const SelectionInfo proghdr_selection_info[] =
	{
		{ 0, 4 },
		{ 4, 4 },
		{ 8, 4 },
		{ 0xC, 4 },
		{ 0x10, 4 },
		{ 0x14, 4 },
		{ 0x18, 4 },
		{ 0x1C, 4 }
	};
	
	/** @brief Program header SelectionInfo structs (64bit) */
	const SelectionInfo proghdr_selection_info64[] =
	{
		{ 0, 4 },
		{ 4, 4 },
		{ 8, 8 },
		{ 0x10, 8 },
		{ 0x18, 8 },
		{ 0x20, 8 },
		{ 0x28, 8 },
		{ 0x30, 8 }
	};
	
	/** @brief Section header SelectionInfo structs */
	const SelectionInfo secthdr_selection_info[] =
	{
		{ 0, 0 }, // Dummy
		{ 0, 4 },
		{ 4, 4 },
		{ 8, 4 },
		{ 0xC, 4 },
		{ 0x10, 4 },
		{ 0x14, 4 },
		{ 0x18, 4 },
		{ 0x1C, 4 },
		{ 0x20, 4 },
		{ 0x24, 4 }
	};
	
	/** @brief Section header SelectionInfo structs (64bit)*/
	const SelectionInfo secthdr_selection_info64[] =
	{
		{ 0, 0 }, // Dummy
		{ 0, 4 },
		{ 4, 4 },
		{ 0x8, 8 },
		{ 0x10, 8 },
		{ 0x18, 8 },
		{ 0x20, 8 },
		{ 0x28, 4 },
		{ 0x2C, 4 },
		{ 0x30, 8 },
		{ 0x38, 8 }
	};
	
	/** @brief Symbol Table SelectionInfo structs */
	const SelectionInfo symtbl_selection_info[] =
	{
		{ 0, 0 }, //DUMMY
		{ 0, 0 }, //DUMMY
		{ 0, 4 },
		{ 4, 4 },
		{ 8, 4 },
		{ 0xC, 1 },
		{ 0xD, 1 },
		{ 0xE, 2 }
	};
	
	/** @brief Symbol Table SelectionInfo structs (64bit) */
	const SelectionInfo symtbl_selection_info64[] =
	{
		{ 0, 0 }, //DUMMY
		{ 0, 0 }, //DUMMY
		{ 0, 4 },
		{ 4, 1 },
		{ 5, 1 },
		{ 6, 2 },
		{ 8, 8 },
		{ 0x10, 8 }
	};
	
	/** @brief Rel and Rela Tables SelectionInfo structs (64bit) */
	const SelectionInfo reltbl_selection_info64[] =
	{
		{ 0, 0 }, // DUMMY
		{ 0, 0 }, // DUMMY
		{ 0, 8 },
		{ 8, 8 },
		{ 0x10, 8 }
	};
	
	/** @brief Rel and Rela Tables SelectionInfo structs */
	const SelectionInfo reltbl_selection_info[] =
	{
		{ 0, 0 }, // DUMMY
		{ 0, 0 }, // DUMMY
		{ 0, 4 },
		{ 4, 4 },
		{ 0, 0 } // DUMMY
	};
	
#endif