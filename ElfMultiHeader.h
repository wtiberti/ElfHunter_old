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
* Filename: ElfHunterMultiHeader.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfMultiHeader.h
 * @brief ElfMultiHeader class definition
 */

#ifndef ElfMultiHeader_H
	#define ElfMultiHeader_H

	#include "ElfGenericHeader.h"

	/** @class ElfMultiHeader
	 * @brief Generic class for various ELF header
	 *
	 * It handles those situation with multiple headers of
	 * the same type (for example, Section header, Program headers etc.)
	 * It adds a QSpinBox to switch from one header to another and offers
	 * some methods to handle other aspects */
	class ElfMultiHeader : public ElfGenericHeader
	{
	Q_OBJECT

	protected:
		QSpinBox *spin; ///< QSpinBox widget to switch between headers
		QLineEdit *le_search; ///< QLineEdit containing the searching regex
		
		QRegExp search_regex; ///< QRegExp object used to filter tables elements
		
		unsigned char *base; ///< base address of header table
		int entry_size; ///< Size of a single header
		__uint64_t offset; ///< offset inside the file of the header table

		/** @brief Insert values inside the table
		 * @param[in] index The header number (relative to its position in the file)
		 *
		 * This method is called automatically by @ref Changed */
		virtual void SetValues( int index ) = 0;

	public:
		/** @brief Constructor
		 * @param[in] r Number of rows requested
		 * @param[in] c Number of columns requested
		 * @param[in] h Table header flag. (default true) */
		ElfMultiHeader( int r, int c, bool h=true );

		/** @brief Destructor */
		~ElfMultiHeader();

		/** @brief Choose the headers to show
		 * @param[in] data The ELF file data
		 *
		 * This method takes the pointer to the ELF file and fills
		 * class attributes such @ref base, @ref entry_size and @ref offset.
		 * In this way, @ref SetValues can navigate through headers. */
		virtual void SelectData( char *data ) = 0;

	public slots:
		/** @brief React to QSpinBox value-change (QT slot)
		 *
		 * After user change the value inside the QSpinBox widget, it calls
		 * @ref SetValues with the index specified by user */
		void Changed();
		
		/** @brief Update the QRegExp search object
		 * 
		 * Update the QRegExp @ref search_regex object */
		void SearchStringChanged();

		virtual void Update( char *data ) = 0; ///< @ref ElfGenericHeader::Update
		
	signals:
		/** @brief Signal. Thrown when used stop writing in the search text box */
		void S_SearchRegexReady();
	};
#endif