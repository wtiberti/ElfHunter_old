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
* Filename: ElfHunterRelTable.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfHunterRelTable.h
 * @brief Definition of ElfHunterRelTable class
 */


#ifndef ElfHunterRelTable_H
	#define ElfHunterRelTable_H
	
	#include "ElfMultiHeader.h"
	#include "ElfAuxTypes.h"
	
	#include <vector>
	
	/** @class ElfHunterRelTable
	 * @brief Searches for all the ELF relocation sections and show their entries */
	class ElfHunterRelTable : public ElfMultiHeader
	{
	Q_OBJECT
	
	private:
		QStringList offsetlist; ///< Contains the relocation entries offsets as QStrings
		QStringList addendlist; ///< Contains the r_addend fields as QStrings (Only .Rela sections)
		std::vector< SectStruct > ss; ///< Vector containing all the .rel and .rela sections
		std::vector< bool > isRela; ///< Contains the type of the sections in @ref ss
		
		/** @brief Gets the r_info subfield
		 * @param[in] value The r_info value to be analyzed
		 * @return A QString in the form x-x-x or (is 32bit) x-x */
		QString Parse_Info_Field( __uint64_t value );
	
	protected:
		void SetValues( int index );///< @ref ElfMultiHeader::SetValues
		
	public:
		ElfHunterRelTable(); ///< Constructor
		~ElfHunterRelTable(); ///< Destructor
		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData
		
	private slots:
		/** @brief Invoke raw data highlighting in the hexdump widget */
		void InvokeSelection( int row, int column );
	};
#endif
