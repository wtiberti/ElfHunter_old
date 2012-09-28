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
* Filename: ElfSymTable.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfSymTable.h
 * @brief ElfSymTable class definition */

#ifndef ElfSymTable_H
	#define ElfSymTable_h

	#include "ElfMultiHeader.h"
	#include "ElfAuxTypes.h"
	#include <vector>

	#include <elf.h>

	class ElfSymTable : public ElfMultiHeader
	{
	Q_OBJECT

	private:
		std::vector< SectStruct > ss;

		//don't like it too much...
		SymData32 sym32;
		SymData64 sym64;
		unsigned int ReadSymbols();

	protected:
		void SetValues( int index );

	public:
		ElfSymTable();
		~ElfSymTable();
		void SelectData( char *data );

	};
#endif