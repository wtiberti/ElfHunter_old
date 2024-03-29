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
	resize( 750, 600 );

	// QIcon window_icon( ":/icons/elf.svg" );
	// setWindowIcon( window_icon );

	Init_StatusBar(); // Must be called before creating the main widget

	mw = new ElfHunterMainWidget( this );

	Init_Actions();
	Init_MenuBar();
	Init_ToolBar();

	setCentralWidget( mw );

	connect( mw, SIGNAL(s_disable_action(unsigned int)), this, SLOT(DisableAction(unsigned int)) );
	connect( mw, SIGNAL(s_enable_action(unsigned int)), this, SLOT(EnableAction(unsigned int)) );
}

ElfHunterWindow::~ElfHunterWindow()
{
	menus.clear();

	for( unsigned int i=0; i<actions.size(); i++ )
		delete actions[i];
	actions.clear();

	for( unsigned int i=0; i<status_widgets.size(); i++ )
		delete status_widgets[i];
	status_widgets.clear();

	if( mw != NULL )
	{
		delete mw;
		mw = NULL;
	}

}

void ElfHunterWindow::CleanUp()
{
	menus.clear();

	for( unsigned int i=0; i<actions.size(); i++ )
		delete actions[i];
	actions.clear();

	for( unsigned int i=0; i<status_widgets.size(); i++ )
		delete status_widgets[i];
	status_widgets.clear();

	if( mw!=NULL )
	{
		delete mw;
		mw = NULL;
	}

	qApp->quit();
}

void ElfHunterWindow::Init_Actions()
{
	QAction *temp;
	actions.clear();

	/* FIXME maybe!
	This workaround is used to enable the right action
	when the filename is passed via command line. */
	extern QString cmdline_file2open;
	bool fromcmdline = (cmdline_file2open=="")?false:true;
	//--

	temp = new QAction( QIcon( ":/icons/application-exit.png" ), "E&xit", this );
	temp->setShortcuts( QKeySequence::Quit );
	temp->setStatusTip( "Exit the application" );
	connect( temp, SIGNAL(triggered()), this, SLOT(CleanUp()) );
	actions.push_back( temp );

	temp = new QAction( QIcon( ":/icons/document-open.png" ), "&Open", this );
	temp->setStatusTip( "Open an ELF file" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(SetFile()) );
	temp->setEnabled( !fromcmdline );
	actions.push_back( temp );

	temp = new QAction( QIcon( ":/icons/document-close.png" ), "&Close", this );
	temp->setStatusTip( "Close current file" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(CloseFile()) );
	temp->setEnabled( fromcmdline );
	actions.push_back( temp );

	temp = new QAction( QIcon( ":/icons/help-about.png" ), "&About", this );
	temp->setStatusTip( "Show ElfHunter information" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(DisplayAbout()) );
	actions.push_back( temp );

	temp = new QAction( QIcon( ":/icons/view-expenses-categories.png" ), "Toggle Hex Dump", this );
	temp->setStatusTip( "Show/Hide hex dump panel" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(ToggleHexView()) );
	temp->setEnabled( fromcmdline );
	actions.push_back( temp );

	temp = new QAction( QIcon( ":/icons/view-list-tree.png" ), "Toggle Table Selector", this );
	temp->setStatusTip( "Show/Hide table selector" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(ToggleWidgetTree()) );
	temp->setEnabled( fromcmdline );
	actions.push_back( temp );

	temp = new QAction( QIcon( ":/icons/arrow-right-double.png" ), "&Go To Offset", this );
	temp->setStatusTip( "Go to a selected offset in the hexdump window" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(Hexdump_GoToOffset()) );
	temp->setEnabled( fromcmdline );
	actions.push_back( temp );

	temp = new QAction( QIcon( ":/icons/view-refresh.png" ), "Reload File data", this );
	temp->setStatusTip( "Re-read the opened file" );
	connect( temp, SIGNAL(triggered()), mw, SLOT(Reload_Active_File()) );
	temp->setEnabled( fromcmdline );
	actions.push_back( temp );
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

	temp = menuBar()->addMenu( "&Edit" );
	temp->addAction( actions[A_RELOADFILE] );
	menus.push_back( temp );

	temp = menuBar()->addMenu( "&View" );
	temp->addAction( actions[A_TOGGLETREE] );
	temp->addAction( actions[A_TOGGLEHEX] );
	temp->addAction( actions[A_GOTOOFFSET] );
	menus.push_back( temp );

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
	main_toolbar->addAction( actions[A_RELOADFILE] );
}

void ElfHunterWindow::Init_StatusBar()
{
	QLabel *temp;

	temp = new QLabel( "File:" );
	statusBar()->addWidget( temp );
	status_widgets.push_back( temp );

	temp = new QLabel( " --- " ); // File name
	statusBar()->addWidget( temp );
	status_widgets.push_back( temp );

	temp = new QLabel( "\tSize:" );
	statusBar()->addWidget( temp );
	status_widgets.push_back( temp );

	temp = new QLabel( " --- " ); // File size
	statusBar()->addWidget( temp );
	status_widgets.push_back( temp );

	temp = new QLabel( "\tCurrent Offset:" ); // Used for filename
	statusBar()->addWidget( temp );
	status_widgets.push_back( temp );

	temp = new QLabel( " --- " ); // Cursor offset
	statusBar()->addWidget( temp );
	status_widgets.push_back( temp );
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

void ElfHunterWindow::SetFileDesc( QString filename, __uint64_t size )
{
	QString size_string = " --- ";

	((QLabel *)status_widgets.at(STBAR_FILENAME))->setText( filename );

	if( size && status_widgets.size() > STBAR_FILESIZE )
	{
		size_string.setNum( size, 16 );
		size_string = size_string.prepend( "0x" );
		size_string = size_string.append( " bytes" );
	}

	((QLabel *)status_widgets[STBAR_FILESIZE])->setText( size_string );
}

void ElfHunterWindow::SetCurrentOffset( __uint64_t offset )
{
	QString o;

	if( status_widgets.size() > STBAR_OFFSET && mw->IsFileActive() )
	{
		o.setNum( offset, 16 );
		o = o.toUpper().prepend( "0x" );
	}
	else
		o = " --- ";

	((QLabel *)status_widgets.at(STBAR_OFFSET))->setText( o );
}