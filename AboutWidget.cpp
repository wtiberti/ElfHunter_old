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
* Filename: AboutWidget.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "AboutWidget.h"

AboutWidget::AboutWidget()
{
	QVBoxLayout l;

	// TODO: change to something else depending on content
	resize( 250, 140 );
	
	// TODO: Add logo and restyle
	
	abouttext = new QLabel(
		"ElfHunter v0.14\n"
		"An ELF file format analyzer\n\n"

		"Released under GNU GPL license.\n"
		"Copyright (C) 2012 Walter Tiberti\n\n"

		"Email: <wtuniv@gmail.com>\n\n"

		"website: http://wtprojects.site88.net", this );

	abouttext->setAlignment( Qt::AlignHCenter|Qt::AlignVCenter );
	l.addWidget( abouttext );
	setLayout( &l );
}

AboutWidget::~AboutWidget()
{
	delete abouttext;
}