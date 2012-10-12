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
* Filename: ElfHunterMainWidget.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfHunterMainWidget.h
 * @brief Definition of ElfHunterMainWidget class*/

#ifndef ElfHunterWidget_H
	#define ElfHunterMainWidget_H
	
	#include "ElfHunterSideWidget.h"
	#include "ElfHunterHexWidget.h"
	#include "AboutWidget.h"

	#include <vector>
	
	#define ELFSIGNATURE 0x464C457F
	
	#define ERR_OPEN_FILE_NOT_EXISTS 1
	#define ERR_OPEN_FILE_OPEN_ERROR 2
	
	#define ERR_READ_FILE_NOT_OPEN 1
	#define ERR_READ_INVALID_SIG 2

	/** @class ElfHunterMainWidget
	 * @brief Handles the internal widget set
	 *
	 * Defines a widget which is used both as a wrapper and a handler to
	 * the internal widget set. It handles all the read operation and all
	 * things related to the internal widgets (such as creation, deletion etc. )*/
	class ElfHunterMainWidget : public QWidget
	{
	Q_OBJECT
	private:
		QGridLayout *layout; ///< Main layout of the widget

		//TODO
		QWidget *parent_window;
		
		ElfHunterSideWidget *sidewidget; ///< Left side main widget
		ElfHunterHexWidget *hexdump; ///< Right side hex dump widget

		QFile *actual_file; ///< Pointer to actual file
		bool file_opened; ///< Flag. If a file is opened, it's true

		bool hexvisible; ///< Flag. If the hexdump widget is visible, it's true
		bool user_can_show_hex; ///< Flag. Indicates whenever user can show/hide the hex-dump

		/** A std::vector which groups all the widgets used in the tabs
		 * @see ElfHunterSideWidget.h*/
		std::vector< QWidget * > tabselem;

		/** @brief Open a file
		 *
		 * Shows the QT's "Open File" standard dialog, and try to open
		 * the selected file. Altough there's no restriction on the file choosen,
		 * all non-ELF file will be discared in the @ref ReadFile method
		 * @return The opened file size*/
		unsigned long OpenFile();

		/** @brief Read the opened file
		 *
		 * Try to read the previously opened file by @ref OpenFile and create all the information widgets
		 * according the file content.
		 * @return The pointer to the file content*/
		unsigned long ReadFile();

	public:
		/** @brief Constructor
		 *
		 * Initialize the layout, create a @ref ElfHunterSideWidget and a @ref ElfHunterHexWidget.
		 * @param[in] parent The parent widget. (Optional)*/
		ElfHunterMainWidget( QWidget *parent = 0);

		/** @brief Destructor
		 *
		 * Close the file (if open) and delete all the created widgets*/
		~ElfHunterMainWidget();

		/** @brief Detect if a file is opened*/
		bool IsFileActive();

	public slots:
		/** @brief Wrapper method. (QT slot)*/
		void SetFile();

		/** @brief Close the file. (QT slot) */
		void CloseFile();

		/** @brief Display a @ref AboutWidget (QT slot)*/
		void DisplayAbout();

		/** @brief Show/Hide the hex-dump widget */
		void ToggleHexView();
	};
#endif