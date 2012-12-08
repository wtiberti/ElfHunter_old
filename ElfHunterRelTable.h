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

#ifndef ElfHunterRelTable_H
	#define ElfHunterRelTable_H
	
	#include "ElfMultiHeader.h"
	#include "ElfAuxTypes.h"
	
	#include <vector>
	
	class ElfHunterRelTable : public ElfMultiHeader
	{
	Q_OBJECT
	
	private:
		QStringList offsetlist;
		QStringList addendlist;
		std::vector< SectStruct > ss;
		std::vector< bool > isRela;
		
		QString Parse_Info_Field( __uint64_t value );
	
	protected:
		void SetValues( int index );///< @ref ElfMultiHeader::SetValues
		
	public:
		ElfHunterRelTable();
		~ElfHunterRelTable();
		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData
		
	private slots:
		/** @brief Invoke raw data highlighting in the hexdump widget */
		void InvokeSelection( int row, int column );
	};
#endif
