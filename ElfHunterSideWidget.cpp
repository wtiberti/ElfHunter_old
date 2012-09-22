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
* Filename: ElfHunterSideWidget.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfHunterSideWidget.h"

//#include "ElfHWidget.h"

ElfHunterSideWidget::ElfHunterSideWidget( QWidget *parent ) : QWidget(parent)
{
	layout = new QVBoxLayout();

	tabs = new QTabWidget();
	layout->addWidget( tabs );
	setLayout( layout );
}

ElfHunterSideWidget::~ElfHunterSideWidget()
{
	delete tabs;
	delete layout;
}

void ElfHunterSideWidget::addTab( QWidget *w, QString title )
{
	tabs->addTab( w, title );
}