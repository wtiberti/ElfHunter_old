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
* Filename: ElfMultiHeader.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfMultiHeader.h"
#include <elf.h>

ElfMultiHeader::ElfMultiHeader( int r, int c, bool h ) : ElfGenericHeader( r, c, h )
{
	spin = new QSpinBox();
	le_search = new QLineEdit();
	le_search->setPlaceholderText( "< ...Regex Search... >" );
	layout->insertWidget( 0, spin );
	layout->addWidget( le_search );
	connect( le_search, SIGNAL(editingFinished()), this, SLOT(SearchStringChanged()) );
}

ElfMultiHeader::~ElfMultiHeader()
{
	delete le_search;
	delete spin;
}

void ElfMultiHeader::Changed()
{
	SetValues( spin->value() );
}

void ElfMultiHeader::SearchStringChanged()
{
	QPalette palette;
	QBrush brush_green( QColor( 0, 85, 0, 255) );
	QBrush brush_red( QColor(85, 0, 0, 255) );
	
	search_regex.setPattern( le_search->text() );

	if( search_regex.isValid() )
	{
		palette.setBrush( QPalette::Active, QPalette::Text, brush_green );
		le_search->setPalette( palette );
		emit S_SearchRegexReady();
	}
	else
	{
		search_regex.setPattern( "" );
		palette.setBrush( QPalette::Active, QPalette::Text, brush_red );
		le_search->setPalette( palette );
	}
	
}