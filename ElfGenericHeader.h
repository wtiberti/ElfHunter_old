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
* Filename: ElfGenericHeader.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfGenericHeader.h
 * @brief ElfGenericHeader class definition */

#ifndef ElfGenericHeader_H
	#define ElfGenericHeader_H

	#include <QtGui>
	#include <elf.h>
	#include <vector>
	
	#include "SelectionInfo.h"

	//Makes item being enabled, selectable and drag-able
	#define EHW_ITEMFLAGS (Qt::ItemFlag)37

	/** Array of QString used as horizontal labels in the table  */
	const QString generic_horizontal_labels[] =
	{
		"Value",
		"Meaning",
		"Info"
	};

	/** @class ElfGenericHeader
	 * @brief Generic ELF header widget
	 *
	 * It provides basic attributes and mathods common to each header
	 * in the ELF files. */
	class ElfGenericHeader : public QWidget
	{
	Q_OBJECT
	private:
		unsigned int columns; ///< Contains the actual number of rows
		unsigned int rows; ///< Contains the actual number of columns
		bool tableheaders; ///< Flag that indicates whenever table headers are present or not

	protected:
		QVBoxLayout *layout; ///< Layput of the widget
		QTableWidget *table; ///< Table widget used to display data
		QStringList stringlist; ///< Array of informations string (one for each field)
		QStringList valueslist; ///< Array of value string (one for each field)
		bool is64bit; ///< 64-bit flag

	public:
		/** @brief Constructor
		 * @param[in] r Number of rows requested
		 * @param[in] c Number of columns requested
		 * @param[in] h Table header flag. (default true) */
		ElfGenericHeader( int r, int c, bool h=true );
		~ElfGenericHeader(); ///< Destructor

		bool IsELF64(); ///< Returns true if the data resambles a 64-bit ELF file
		void AddHeader_H(); ///< Adds horizontal table headers
		void AddHeader_V(); ///< Adds vertical table headers
		int AddRow(); ///< Adds a row to the table
		int AddCol(); ///< Adds a column to the table
		void ClearRows(); ///< Delete all the rows int the table

		/** @brief Verify the presence of Section Headers in the selected data
		 * @param[in] data Data to be verified */
		static bool HasSections( char *data );

		/** @brief Verify the presence of Program Headers in the selected data
		 * @param[in] data Data to be verified */
		static bool HasSegments( char *data );

		/** @brief Convert a sequence of bytes in a hex-string
		 * @param[in] stream Pointer to data to be converted
		 * @param[in] size Size in bytes of data */
		static QString *ToHexString( unsigned char *stream, unsigned int size );
	};
#endif