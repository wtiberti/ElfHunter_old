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
* Filename: ElfHunterGenericHeader.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfGenericHeader.h"
#include <elf.h>
#include <cstdio>
#include <cstring>

ElfGenericHeader::ElfGenericHeader( int r, int c, bool h )
{
	QTableWidgetItem *tempitem;

	rows = r;
	columns = c;

	layout = new QVBoxLayout();
	table = new QTableWidget( r, c, this );
	table->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

	tableheaders = h;

	if( h )
	{
		AddHeader_H();
		AddHeader_V();
	}

	for( unsigned int j=0; j<columns; j++ )
		for( unsigned int i=0; i<rows; i++ )
		{
			tempitem = new QTableWidgetItem();
			tempitem->setFlags( (Qt::ItemFlag)37 );
			table->setItem( i, j, tempitem );
		}

	layout->addWidget( table );
	setLayout( layout );
	is64bit = false;
}

void ElfGenericHeader::AddHeader_H()
{
	QTableWidgetItem *tempitem;

	for( unsigned int i=0; i<columns; i++ )
	{
		tempitem = new QTableWidgetItem( generic_horizontal_labels[i] );
		tempitem->setTextAlignment( Qt::AlignHCenter );
		table->setHorizontalHeaderItem( i, tempitem );
	}
	table->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
}

void ElfGenericHeader::AddHeader_V()
{
	QTableWidgetItem *tempitem;

	for( unsigned int i=0; i<rows; i++ )
	{
		tempitem = new QTableWidgetItem( QString::number( i ) );
		table->setVerticalHeaderItem( i, tempitem );
	}
	table->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
}

ElfGenericHeader::~ElfGenericHeader()
{
	for( unsigned int i=0; i<columns; i++ )
		for( unsigned int j=0; j<rows; j++ )
			delete table->item( j, i );

	if( tableheaders )
	{
	for( unsigned int i=0; i<rows; i++ )
			delete table->horizontalHeaderItem( i );

		for( unsigned int i=0; i<rows; i++ )
			delete table->verticalHeaderItem( i );
	}
	
	stringlist.clear();
	valueslist.clear();

	delete table;
	delete layout;
}

int ElfGenericHeader::AddRow()
{
	table->setRowCount( table->rowCount()+1 );
	rows = table->rowCount();
	return rows;
}

int ElfGenericHeader::AddCol()
{
	table->setColumnCount( table->columnCount()+1 );
	columns = table->columnCount();
	return columns;
}

void ElfGenericHeader::ClearRows()
{
	for( unsigned int i=0; i<columns; i++ )
		for( unsigned int j=0; j<rows; j++ )
			delete table->item( j, i );

	table->setRowCount( 0 );
	rows = 0;
}

bool ElfGenericHeader::IsELF64()
{
	return is64bit;
}

bool ElfGenericHeader::HasSections( char *data )
{
	Elf32_Ehdr *header = (Elf32_Ehdr *)data;

	if( header->e_ident[EI_CLASS]==ELFCLASS64 )
		return ((Elf64_Ehdr *)header)->e_shnum==0?false:true;
	else
		return header->e_shnum==0?false:true;
}

bool ElfGenericHeader::HasSegments( char *data )
{
	Elf32_Ehdr *header = (Elf32_Ehdr *)data;

	if( header->e_ident[EI_CLASS]==ELFCLASS64 )
		return ((Elf64_Ehdr *)header)->e_phnum==0?false:true;
	else
		return header->e_phnum==0?false:true;
}

QString *ElfGenericHeader::ToHexString( unsigned char *stream, unsigned int size )
{
	char *buffer = new char[5*size+1];
	char temp_buffer[10];
	QString *result;

	memset( buffer, 0, sizeof(char)*(5*size+1) );

	for( unsigned int i=0; i<size; i++ )
	{
		memset( temp_buffer, 0, sizeof(char)*10 );
		snprintf( temp_buffer, 6, "0x%.2X ", stream[i] );
		strncat( buffer, temp_buffer, 6 );
	}

	result = new QString( buffer );
	*result = result->trimmed();

	delete buffer;

	return result;
}