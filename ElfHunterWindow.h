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
* Filename: ElfHunterWindow.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfHunterWindow.h
 * @brief Definition of ElfHunterWindow class
 */

#ifndef ElfHunterWindow_H
	#define ElfHunterWindow_H
	
	#include <vector>
	#include "ElfHunterMainWidget.h"
	

	#define A_EXIT 0 ///< Exit Action id
	#define A_OPEN 1 ///< Open Action id
	#define A_CLOSE 2 ///< Close Action id
	#define A_ABOUT 3 ///< About Action id
	#define A_TOGGLEHEX 4 ///< ToggleHex Action id
	#define A_TOGGLETREE 5 ///< ToggleTree Action id
	#define A_GOTOOFFSET 6 ///< GotoOffset Action id
	#define A_RELOADFILE 7 ///< ReloadFile Action id
	// etc..
	
	#define M_FILE 0 ///< "File" Menu id
	#define M_EDIT 1 ///< "Edit" Menu id
	#define M_VIEW 2 ///< "View" Menu id
	#define M_FIND 3 ///< "Find" Menu id
	// etc..
	
	// Note: even number are for label widget!
	#define STBAR_FILENAME 1 ///< "Filename" status widget
	#define STBAR_FILESIZE 3 ///< "Filename" status widget
	#define STBAR_OFFSET 5 ///< "Filename" status widget
	
	/** @class ElfHunterWindow
	 * @brief ElfHunter Main Window class
	 *
	 * This class represent the main window of ElfHunter. It shows the menu, tool and status bars
	 * along the three main widget (wrapped together in the @ref ElfHunterMainWidget class) */
	class ElfHunterWindow : public QMainWindow
	{
	Q_OBJECT
	
	private:
		ElfHunterMainWidget *mw; ///< Main Widget
		QToolBar *main_toolbar; ///< Toolbar
		std::vector< QAction * > actions; ///< Actions vector. All actions are stored here
		std::vector< QMenu * > menus; ///< Menu vector. All the top level menus are stored here
		std::vector< QWidget * > status_widgets; ///< Status bar widget vector

		/** @brief  Creates all the needed actions */
		void Init_Actions();
		
		/** @brief Create all the menus */
		void Init_MenuBar();
		
		/** @brief Creates the toolbar */
		void Init_ToolBar();
		
		/** @brief Creates the statusbar */
		void Init_StatusBar();
		
	public:
		ElfHunterWindow(); ///< Constructor
		~ElfHunterWindow(); ///< Destructor
		
	public slots:
		/** @brief Enable the choosen action
		 * @param[in] i The action to be enabled (as index in @ref actions vector) */
		void EnableAction( unsigned int i );
		
		/** @brief Disable the choosen action
		 * @param[in] i The action to be disabled (as index in @ref actions vector) */
		void DisableAction( unsigned int i );
		
		/** @brief Ensure a clean exit */
		void CleanUp();
		
		/** @brief Shows opened file parameters in status bar
		 * @param[in] filename Name of the file
		 * @param[in] size Size of the file in bytes */
		void SetFileDesc( QString filename, __uint64_t size );
		
		/** @brief Shows opened file parameters in status bar
		 * @param[in] offset Current offset in the hexdump window */
		void SetCurrentOffset( __uint64_t offset );
	};
#endif