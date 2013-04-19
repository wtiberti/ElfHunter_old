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
	l = new QHBoxLayout();

	banner = new QPixmap( ":/banner.png" );
	banner_container = new QLabel();
	banner_container->setScaledContents( true );
	banner_container->setPixmap( *banner );

	infos = new QLabel( "Version 0.17\n\n"
						"Author: Walter Tiberti\n"
						"email: wtuniv@gmail.com\n"
						"website: wtprojects.site88.net" );

	l->addWidget( banner_container );
	l->addWidget( infos );

	setLayout( l );
	resize( sizeHint() );
}

AboutWidget::~AboutWidget()
{
	delete l;
	delete banner_container;
	delete banner;
	delete infos;
}