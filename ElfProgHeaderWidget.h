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
* Filename: ElfProgHeaderWidget.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfProgHeaderWidget.h
 * @brief ElfProgHeaderWidget class definition */
#ifndef ElfProgHeaderWidget_H
	#define ElfProgHeaderWidget_H

	#include "ElfMultiHeader.h"

	#define PROGHDRTABLEROWS 8 ///< Number of rows needed for a program header
	#define PROGHDRTABLECOLUMNS 2 ///< Number of columns needed for a program header

	/** @class ElfProgHeaderWidget
	 * @brief Class for Program Headers
	 *
	 * This class aims to read all the program headers and their fields. */
	class ElfProgHeaderWidget : public ElfMultiHeader
	{
	Q_OBJECT

	protected:
		void SetValues( int index ); ///< @ref ElfMultiHeader::SetValues

	public:
		ElfProgHeaderWidget(); ///< Constructor
		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData
		
	public slots:
		virtual void Update( char *data ); ///< @ref ElfGenericHeader::Update
	
	private slots:
		/** @brief Invoke raw data highlighting in the hexdump widget */
		void InvokeSelection( int row, int column );
	};

#endif