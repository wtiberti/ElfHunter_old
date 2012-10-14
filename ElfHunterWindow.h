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
	

	#define A_EXIT 0
	#define A_OPEN 1
	#define A_CLOSE 2
	#define A_ABOUT 3
	#define A_TOGGLEHEX 4
	#define A_TOGGLETREE 5
	// etc..
	
	#define M_FILE 0
	#define M_INFO 1
	// etc..
	
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
	};
#endif