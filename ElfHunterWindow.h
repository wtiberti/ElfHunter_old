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

#ifndef ElfHunterWindow_H
	#define ElfHunterWindow_H
	
	#include <vector>
	#include "ElfHunterMainWidget.h"
	

	#define A_EXIT 0
	#define A_OPEN 1
	#define A_CLOSE 2
	#define A_ABOUT 3
	#define A_TOGGLEHEX 4
	// etc..
	
	#define M_FILE 0
	#define M_INFO 1
	// etc..
	
	class ElfHunterWindow : public QMainWindow
	{
	Q_OBJECT
	
	private:
		ElfHunterMainWidget *mw;
		QToolBar *main_toolbar;
		std::vector< QAction * > actions;
		std::vector< QMenu * > menus;
		
		void Init_Actions();
		void Init_MenuBar();
		void Init_ToolBar();
		void Init_StatusBar();
		
	public:
		ElfHunterWindow();
		~ElfHunterWindow();
		
	public slots:
		void EnableAction( unsigned int i, bool value=true );
	};
#endif