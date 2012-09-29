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

QMainWindow *w;
ElfHunterMainWidget *mw;

QStatusBar *statusbar;

QMenuBar *menu;
std::vector< QAction * > menuactions;

QToolBar *toolbar;
std::vector< QAction * > tbactions;

QToolBar *SetupToolBar();
QMenuBar *SetupMenu( QApplication *a );
void Cleaner();

int main( int argc, char *argv[] )
{
	QApplication main_app( argc, argv );

	w = new QMainWindow();
	//Setting starting size
	w->resize( 1000, 550 );

	mw = new ElfHunterMainWidget( w );
	statusbar = new QStatusBar( w );
	toolbar = new QToolBar( w );

	menu = SetupMenu( &main_app );
	toolbar = SetupToolBar();

	w->setMenuBar( menu );
	w->setStatusBar( statusbar );
	w->addToolBar( toolbar );
	w->setCentralWidget( mw );
	w->show();

	main_app.exec();

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
