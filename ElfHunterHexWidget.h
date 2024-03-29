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
* Filename: ElfHunterHexWidget.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfHunterHexWidget.h
 * @brief ElfHunterHexWidget class definition
 */

#ifndef ElfHunterHexWidget_H
	#define ElfHunterHexWidget_H

	#include <okteta1/bytearraycolumnview.h>
	#include <okteta1/piecetablebytearraymodel.h>
	#include <okteta1/addressrange.h>

	#include <QtGui>
	

	/** @class ElfHunterHexWidget
	 * @brief Implementation of KHexEditor interface
	 *
	 * It provide the standard hex-dump widget
	 * and sets up some methods to insert and clean data inside it. */
	class ElfHunterHexWidget : public QWidget
	{
	Q_OBJECT

	private:
		Okteta::ByteArrayColumnView *okteta_widget; ///< Hex Dump View widget
		Okteta::PieceTableByteArrayModel* model; ///< Data model used ( as in Model-View pattern )

		QGridLayout *l; ///< Main layout

		char *hexdata; ///< Pointer to data displayed on the widget

	public:
		/** @brief Contructor
		 * @param[in] parent The parent widget */
		ElfHunterHexWidget( QWidget *parent = 0 );
		~ElfHunterHexWidget(); ///< Destructor

		/** @brief Insert data into the widget
		 * @param[in] data Pointer to data to be inserted
		 * @param[in] datasize Size in bytes of data */
		void SetData( char *data, unsigned long datasize );
		void ClearData(); ///< Empty the widget and clear data
		
	public slots:
		/** @brief Select/Mark the selected data range
		 * @param[in] offset Start of data to be marked/selected
		 * @param[in] size Size of data to be marked/selected */
		void Select( __uint64_t offset, __uint64_t size );
		
		/** @brief "Center" the hexdump to the selected offset
		 * @param[in] offset Offset */
		void GoToOffset( __uint64_t offset );
		
		/** @brief Convert a Okteta::Address to a __uint64_t and redirect
		 * the cursorPositionChanged signal from Okteta::ByteArrayColumnView */
		void andress2uint( Okteta::Address address );
		
	signals:
		/** @brief QT Signal. It is sent when moving the hexdump cursor */
		void s_hexcursorchanged( __uint64_t offset );
	};
#endif