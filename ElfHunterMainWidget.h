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
	
	#include "ElfELFHeaderWidget.h"
	#include "ElfProgHeaderWidget.h"
	#include "ElfSectionHeaderWidget.h"
	#include "ElfStringTable.h"
	#include "ElfSymTable.h"
	#include "ElfHunterRelTable.h"
	#include "ElfHunterExec.h"
	#include "ElfHunterDyn.h"

	#include <vector>
	
	#define MAX_PATH 256 ///< Maximum size of the filename buffer
	
	#define ELFSIGNATURE 0x464C457F ///< ELF signature
	
	#define ERR_OPEN_FILE_NOT_EXISTS 1 ///< Error code 1
	#define ERR_OPEN_FILE_OPEN_ERROR 2 ///< Error code 2
	
	#define ERR_READ_FILE_NOT_OPEN 1 ///< Read Error code 1
	#define ERR_READ_INVALID_SIG 2 ///< Read Error code 2

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
		QSplitter *spl; ///< Nested splitter. Used to make @ref sidewidget and @ref widget_selector to be resizeable
		QSplitter *v_spl; ///< Main splitter. Used to make @ref spl and @ref hexdump to be resizeable
		
		QTreeWidget *widget_selector; ///< A widget to select different tables
		ElfHunterSideWidget *sidewidget; ///< Left side main widget
		ElfHunterHexWidget *hexdump; ///< Right side hex dump widget

		QFile *actual_file; ///< Pointer to actual file
		bool file_opened; ///< Flag. If a file is opened, it's true
		char long_file_name[MAX_PATH]; ///< Holds the expanded filename

		bool hexvisible; ///< Flag. If the hexdump widget is visible, it's true
		bool user_can_show_hex; ///< Flag. Indicates whenever user can show/hide the hex-dump
		bool treewidgetvisible; ///< Flag. Indicates if the QTreeWidget is visible or not
		
		/** Contains all the QTreeWidget item added */
		std::vector< QTreeWidgetItem * > tree_elem;

		/** @brief Open a file
		 *
		 * Try to open the selected file. Altough there's no restriction on the file choosen,
		 * all non-ELF file will be discared in the @ref ReadFile method
		 * @param[in] filename The file to open
		 * @return The opened file size*/
		unsigned long OpenFile( QString &filename );
		
		/** @brief Shows the 'Open File' dialog
		 * @return The name of the choosen file*/
		QString OpenFile_Dialog();

		/** @brief Read the opened file
		 *
		 * Try to read the previously opened file by @ref OpenFile
		 * @return The pointer to the file content*/
		unsigned long ReadFile();
		
		/** @brief Check the open file and adds all the data widget
		 * @param[in] filedata The pointer to the buffer containing the file data
		 * @param[in] size Size of the file */
		void Populate( char *filedata, unsigned long size );

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
		void SetFile( bool fromcmdline = false );

		/** @brief Closes the file. (QT slot) */
		void CloseFile();

		/** @brief Displays a @ref AboutWidget (QT slot)*/
		void DisplayAbout();

		/** @brief Shows/Hides the hex-dump widget */
		void ToggleHexView();
		
		/** @brief Shows/Hides the Tree widget */
		void ToggleWidgetTree();
		
		/** @brief Shows the "Go To Offset" dialog box */
		void Hexdump_GoToOffset();
		
	signals:
		/** @brief QT Signal. It is sent when an action has to be disabled */
		void s_disable_action( unsigned int action_n );
		/** @brief QT Signal. It is sent when an action has to be enabled */
		void s_enable_action( unsigned int action_n );
		
		/** @brief QT Signal. It is sent when user opens/closes a file */
		void s_filechanged( QString filename, __uint64_t filesize );
	};
#endif