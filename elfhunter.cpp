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
* Filename: elfhunter.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include <QtGui>
#include <vector>
#include "ElfHunterMainWidget.h"

// Prototypes
QToolBar *SetupToolBar(); // Set up the toolbar widget
QMenuBar *SetupMenu( QApplication *a ); // Set up the menu' widget
void Cleaner(); // Free allocated items

// ElfHunter main window
QMainWindow *w;

// ElfHunter wrapper widget
ElfHunterMainWidget *mw;

// Statusbar
QStatusBar *statusbar;

// Application menu'
QMenuBar *menu;
std::vector< QAction * > menuactions; // Vector grouping all the menu actions

// Toolbar
QToolBar *toolbar;
std::vector< QAction * > tbactions; // Vector grouping all the toolbar actions

int main( int argc, char *argv[] )
{
	// Initialization
	QApplication main_app( argc, argv );

	// Window creation
	w = new QMainWindow();

	//Setting starting size
	w->resize( 1000, 550 );

	// Creating wrapper widget, toolbar and statusbar
	mw = new ElfHunterMainWidget( w );
	statusbar = new QStatusBar( w );
	toolbar = new QToolBar( w );

	// Set up the toolbar and the menu'
	menu = SetupMenu( &main_app );
	toolbar = SetupToolBar();

	// Adding widget to the main window
	w->setMenuBar( menu );
	w->setStatusBar( statusbar );
	w->addToolBar( toolbar );

	// Showing the window
	w->setCentralWidget( mw );
	w->show();


	// MAIN LOOP
	main_app.exec();

	// Clean-up
	Cleaner();
	return 0;
}

QMenuBar *SetupMenu( QApplication *a )
{
	QMenuBar *m = new QMenuBar();
	QAction *temp;

	menuactions.clear();

	QMenu *im = m->addMenu( "&File" );
	temp = new QAction( "&Open", im );
	im->addAction( temp );
	menuactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(SetFile()) );

	temp = new QAction( "&Close", im );
	temp->setEnabled( false );
	im->addAction( temp );
	menuactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(CloseFile()) );

	temp = new QAction( "&Exit", im );
	im->addAction( temp );
	menuactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), a, SLOT(quit()) );

	im = m->addMenu( "&?" );
	temp = new QAction( "&About ElfHunter", im );
	im->addAction( temp );
	menuactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(DisplayAbout()) );

	return m;
}

QToolBar *SetupToolBar()
{
	QAction *temp;

	tbactions.clear();

	QToolBar *t = new QToolBar( "Main Toolbar", w );

	//TODO Add icons
	//TODO Better way to manage slots

	temp = new QAction( "Open", t );
	t->addAction( temp );
	tbactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(SetFile()) );

	temp = new QAction( "Close", t );
	temp->setEnabled( false );
	t->addAction( temp );
	tbactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(CloseFile()) );

	temp = new QAction( "Toggle Hex-dump", t );
	t->addAction( temp );
	tbactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(ToggleHexView()) );

	return t;
}

void Cleaner()
{
	menuactions.clear();
	delete menu;

	tbactions.clear();
	delete toolbar;

	delete statusbar;
	delete mw;
	delete w;
}
