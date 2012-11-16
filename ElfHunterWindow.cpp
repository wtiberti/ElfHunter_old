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
* Filename: ElfHunterWindow.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/
#include "ElfHunterWindow.h"

ElfHunterWindow::ElfHunterWindow()
{
	resize( 800, 620 ); //TODO
	mw = new ElfHunterMainWidget( this );
	
	Init_Actions();
	
	Init_MenuBar();
	Init_ToolBar();
	Init_StatusBar();
	
	setCentralWidget( mw );
	
	connect( mw, SIGNAL(s_disable_action(unsigned int)), this, SLOT(DisableAction(unsigned int)) );
	connect( mw, SIGNAL(s_enable_action(unsigned int)), this, SLOT(EnableAction(unsigned int)) );
}

ElfHunterWindow::~ElfHunterWindow()
{
	menus.clear();
	actions.clear();
	delete mw;
}

void ElfHunterWindow::CleanUp()
{
	menus.clear();
	actions.clear();
	delete mw;
	
	qApp->quit();
}

void ElfHunterWindow::Init_Actions()
{
	QAction *temp;
	
	actions.clear();
	
	/*FIXME
	This workaround is used to enable the right action
	when the filename is passed via command line. */
	extern QString cmdline_file2open;
	bool fromcmdline = (cmdline_file2open=="")?false:true;
	//--
	
	temp = new QAction( QIcon( "icons/application-exit.png" ), "E&xit", this );
	temp->setShortcuts( QKeySequence::Quit );
	temp->setStatusTip( "Exit the application" );
	connect( temp, SIGNAL(triggered()), this, SLOT(CleanUp()) );
	actions.push_back( temp );
	
	temp = new QAction( QIcon( "icons/document-open.png" ), "&Open", this );
	temp->setStatusTip( "Open an ELF file" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(SetFile()) );
	actions.push_back( temp );
	//FIXME
	if( fromcmdline ) temp->setEnabled( false );
	//--
	
	temp = new QAction( QIcon( "icons/document-close.png" ), "&Close", this );
	temp->setStatusTip( "Close current file" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(CloseFile()) );
	temp->setEnabled( false );
	actions.push_back( temp );
	//FIXME
	if( fromcmdline ) temp->setEnabled( true );
	//--
	
	temp = new QAction( QIcon( "icons/help-about.png" ), "&About", this );
	temp->setStatusTip( "Show ElfHunter information" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(DisplayAbout()) );
	actions.push_back( temp );
	
	temp = new QAction( QIcon( "icons/view-expenses-categories.png" ), "Toggle Hex Dump", this );
	temp->setStatusTip( "Show/Hide hex dump panel" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(ToggleHexView()) );
	temp->setEnabled( false );
	actions.push_back( temp );
	//FIXME
	if( fromcmdline ) temp->setEnabled( true );
	//--
	
	temp = new QAction( QIcon( "icons/view-list-tree.png" ), "Toggle Table Selector", this );
	temp->setStatusTip( "Show/Hide table selector" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(ToggleWidgetTree()) );
	temp->setEnabled( false );
	actions.push_back( temp );
	//FIXME
	if( fromcmdline ) temp->setEnabled( true );
	//--
	
	temp = new QAction( QIcon( "icons/arrow-right-double.png" ), "&Go To Offset", this );
	temp->setStatusTip( "Go to a selected offset in the hexdump window" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(Hexdump_GoToOffset()) );
	temp->setEnabled( false );
	actions.push_back( temp );
	//FIXME
	if( fromcmdline ) temp->setEnabled( true );
	//--
	
}

void ElfHunterWindow::Init_MenuBar()
{
	QMenu *temp;
	
	menus.clear();
	
	temp = menuBar()->addMenu( "&File" );
	temp->addAction( actions[A_OPEN] );
	temp->addAction( actions[A_CLOSE] );
	temp->addSeparator();
	temp->addAction( actions[A_EXIT] );
	menus.push_back( temp );
	
	temp = menuBar()->addMenu( "&View" );
	temp->addAction( actions[A_TOGGLETREE] );
	temp->addAction( actions[A_TOGGLEHEX] );
	temp->addAction( actions[A_GOTOOFFSET] );
	
	temp = menuBar()->addMenu( "&?" );
	temp->addAction( actions[A_ABOUT] );
	menus.push_back( temp );
}

void ElfHunterWindow::Init_ToolBar()
{
	main_toolbar = addToolBar( "Main Toolbar" );
	main_toolbar->addAction( actions[A_OPEN] );
	main_toolbar->addAction( actions[A_CLOSE] );
	main_toolbar->addAction( actions[A_TOGGLETREE] );
	main_toolbar->addAction( actions[A_TOGGLEHEX] );
	main_toolbar->addAction( actions[A_GOTOOFFSET] );
}

void ElfHunterWindow::Init_StatusBar()
{
	//TODO
}

void ElfHunterWindow::EnableAction( unsigned int i )
{
	if( i<actions.size() )
	{
		actions[i]->setEnabled( true );
	}
}

void ElfHunterWindow::DisableAction( unsigned int i )
{
	if( i<actions.size() )
	{
		actions[i]->setEnabled( false );
	}
}