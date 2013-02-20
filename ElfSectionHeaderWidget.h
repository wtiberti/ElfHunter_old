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
* Filename: ElfSectionHeaderWidget.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfSectionHeaderWidget.h
 * @brief ElfSectionHeaderWidget class definition */
#ifndef ElfSectionHeaderWidget_H
	#define ElfSectionHeaderWidget_H

	#include "ElfMultiHeader.h"
	#include <vector>

	/** Section Header fields */
	const QString secthdr_field_names[] =
	{
		"[offset]",
		"sh_name",
		"sh_type",
		"sh_flags",
		"sh_addr",
		"sh_offset",
		"sh_size",
		"sh_link",
		"sh_info",
		"sh_addralign",
		"sh_entsize"
	};

	#define SECTHDRTABLEROWS 11 ///<Number of rows needed for a section header
	#define SECTHDRTABLECOLUMNS 2 ///<Number of columns needed for a section header

	/** @class ElfSectionHeaderWidget
	 * @brief Class for Section Headers
	 *
	 * This class aims to read and show all the Section Headers and their fields */
	class ElfSectionHeaderWidget : public ElfMultiHeader
	{
	Q_OBJECT

	private:
		unsigned int strsectnx; ///< Index of the section headers' string table
		__uint64_t str_offset; ///<  Offset to the section headers' string table
		void GetShStrTable(); ///< Gets the offset to the section headers' string table
		unsigned int number_of_sections; ///< Holds the number of sections
		
		std::vector< int > sect_whitelist; ///< Holds the index of the sections that match the @ref search_regex
		
	protected:
		void SetValues( int index ); ///< @ref ElfMultiHeader::SetValues

	public:
		ElfSectionHeaderWidget(); ///< Constructor
		~ElfSectionHeaderWidget(); ///< Destructor
		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData

		/** @brief Retrieve the section name
		 * @param[in] elf Pointer to allocated ELF file
		 * @param[in] index Index of the section to be named */
		static char *GetSectionName( char *elf, int index );
		
	public slots:
		virtual void Update( char *data ); ///< @ref ElfGenericHeader::Update
		
	private slots:
		/** @brief Invoke raw data highlighting in the hexdump widget */
		void InvokeSelection( int row, int column );
		
		/** @brief Generate a sublist of sections which match the search_regex
		 * 
		 * @ref search_regex */
		void GenerateWhiteList();
	};
#endif