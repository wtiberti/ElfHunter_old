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
* Filename: ElfStringTable.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfStringTable.h
 * @brief ElfStringTable class definition */
#ifndef ElfStringTable_H
	#define ElfStringTable_H

	#include "ElfMultiHeader.h"
	#include "ElfAuxTypes.h"

	#include <vector>

	/** Field used to display strings */
	const QString str_table_h_hdr[] =
	{
		"Offset",
		"String"
	};

	/** @class ElfStringTable
	 * @brief Select the string sections and extract all the strings
	 *
	 * This class analyze the section headers and filter all the section marked as
	 * string table. Then, for each section, search for all the strings and display them
	 * on the table.
	 * *NOTE* This class handles *only* strings in sections. Since sections are optional in
	 * pure ELF executable file, you should refer to ElfProgStrings class for strings found in ".DYN" program headers */
	class ElfStringTable : public ElfMultiHeader
	{
	Q_OBJECT

	private:
		char *hdrstrings;///< Pointer to headers string table
		std::vector< SectStruct > ss; ///< One SectStruct for string section
		
		/** @brief Add a string to the table
		 * @param[in] v Offset of the string
		 * @param[in] s Pointer to the string */
		void AddString( QString v, QString s );
		
		/** @brief Searxhes for strings and fills data structures
		 * @param[in] index Index int the @ref ss vector */
		void ParseStrings( int index );

	protected:
		void SetValues( int index );///< @ref ElfMultiHeader::SetValues

	public:
		ElfStringTable(); ///< Constructor
		~ElfStringTable(); ///< Destructor
		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData

	private slots:
		/** @brief Invoke raw data highlighting in the hexdump widget */
		void InvokeSelection( int row, int column );
		
	public slots:
		virtual void Update( char *data ); ///< @ref ElfGenericHeader::Update
		
	};
#endif