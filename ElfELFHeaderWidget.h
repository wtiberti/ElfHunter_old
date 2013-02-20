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
* Filename: ElfELFHeaderWidget.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfELFHeaderWidget.h
 * @brief ElfELFHeaderWidget class definition
 */
#ifndef ElfELFHeaderWidget_H
	#define ElfELFHeaderWidget_H

	#include "ElfGenericHeader.h"

	/** ELF Header fields */
	const QString elfhdr_field_names[] =
	{
		"e_ident[MAG]",
		"e_ident[CLASS]",
		"e_ident[DATA]",
		"e_ident[ELF VERSION]",
		"e_ident[OS ABI]",
		"e_ident[ABI VERSION]",
		"e_ident[IDENT SIZE]",
		"e_type",
		"e_machine",
		"e_version",
		"e_entry",
		"e_phoff",
		"e_shoff",
		"e_flags",
		"e_ehsize",
		"e_phentsize",
		"e_phnum",
		"e_shentsize",
		"e_shnum",
		"e_shstrndx"
	};


	/** @class ElfELFHeaderWidget
	 * @brief ELF Header widget class
	 *
	 * This class care about extracting and display the values
	 * of the ELF header fields of the loaded file */
	class ElfELFHeaderWidget : public ElfGenericHeader
	{
	Q_OBJECT
	public:
		ElfELFHeaderWidget(); ///< Constructor
		~ElfELFHeaderWidget(); ///< Destructor

		/** @brief Insert ELF values in the table
		 * @param[in] elfheader Pointer to the ELF file data
		 * @param[in] updating "True" on data uploading */
		void SetElfValues( char *elfheader, bool updating=false );

	public slots:
		virtual void Update( char *data );

	private slots:
		/** @brief Invoke raw data highlighting in the hexdump widget */
		void InvokeSelection( int row, int column );
	};
#endif