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
* Filename: ElfStringTable.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfStringTable.h"
#include <elf.h>

ElfStringTable::ElfStringTable() : ElfMultiHeader( 0, 2 )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "String table # " );

	table->horizontalHeaderItem( 0 )->setText( str_table_h_hdr[0] );
	table->horizontalHeaderItem( 1 )->setText( str_table_h_hdr[1] );

	table->horizontalHeader()->setResizeMode( QHeaderView::Interactive );
	table->horizontalHeaderItem( 1 )->setTextAlignment( Qt::AlignLeft );
	table->horizontalHeader()->setStretchLastSection( true );
	
	connect( this, SIGNAL(S_SearchRegexReady()), this, SLOT(Changed()) );
}

ElfStringTable::~ElfStringTable()
{
	ss.clear();
}

void ElfStringTable::ParseStrings( int index )
{
	QString temp_string;
	QString str_off;
	
	stringlist.clear();
	valueslist.clear();
	
	if( ss.size()>0 )
	{
		temp_string = (char *)(hdrstrings+ss[index].index_name);
		str_off.setNum( ss[index].sect_n );
		AddString( str_off.prepend( "[SECT n°] " ), temp_string );

		unsigned int i=0;
		while( i<ss[index].size )
		{
			str_off.setNum( (ss[index].offset)+i, 16 );
			temp_string = (char *)(ss[index].addr+i);
			
			if( search_regex.isValid() && search_regex.indexIn( temp_string )!=-1 )
				AddString( str_off.toUpper().prepend("0x"), temp_string );

			i += temp_string.length() + 1;
		}
	}
}

void ElfStringTable::SetValues( int index )
{
	QTableWidgetItem *table_item;
	
	if( ss.size()>0 )
	{
		ParseStrings( index );
		ClearRows();
		for( int i=0; i<valueslist.size(); i++ )
		{
			AddRow();
			table_item = new QTableWidgetItem( valueslist[i] );
			table_item->setFlags( (Qt::ItemFlag)37 );
			table->setItem( i, 0, table_item );

			table_item = new QTableWidgetItem( stringlist[i] );
			table_item->setFlags( (Qt::ItemFlag)37 );
			table->setItem( i, 1, table_item );
		}
		
		table->horizontalHeader()->resizeSections( QHeaderView::ResizeToContents );
	}
}

void ElfStringTable::SelectData( char *data )
{
	SectStruct temp_s;
	__uint64_t sectoff;
	unsigned int sectnum;

	Elf32_Ehdr *header = (Elf32_Ehdr *)data;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)data;
	Elf64_Shdr *sect64;
	Elf32_Shdr *sect;

	base = (unsigned char *) data;
	is64bit = header->e_ident[EI_CLASS]==ELFCLASS64?true:false;

	if( is64bit )
	{
		sectoff = header64->e_shoff;
		hdrstrings = (char *) (base + sectoff + (int)(header64->e_shstrndx)*(int)(header64->e_shentsize));
		hdrstrings = (char *)(base + ((Elf64_Shdr *)hdrstrings)->sh_offset);
		sectnum = header64->e_shnum;
	}
	else
	{
		sectoff = header->e_shoff;
		hdrstrings = (char *) (base + sectoff + (int)(header->e_shstrndx)*(int)(header->e_shentsize));
		hdrstrings = (char *)(base + ((Elf32_Shdr *)hdrstrings)->sh_offset);
		sectnum = header->e_shnum;
	}

	sect = (Elf32_Shdr *)(data+sectoff);
	sect64 = (Elf64_Shdr *)(data+sectoff);

	ss.clear();
	
	for( unsigned int i=0; i<sectnum; i++ )
	{
		if( is64bit )
		{
			if( sect64[i].sh_type==SHT_STRTAB )
			{
				temp_s.sect_n = i;
				temp_s.index_name = sect64[i].sh_name;
				temp_s.offset = sect64[i].sh_offset;
				temp_s.addr = (char *)(base + temp_s.offset);
				temp_s.size = sect64[i].sh_size;
				ss.push_back( temp_s );
			}
		}
		else
		{
			if( sect[i].sh_type==SHT_STRTAB )
			{
				temp_s.index_name = sect[i].sh_name;
				temp_s.offset = sect[i].sh_offset;
				temp_s.addr = (char *)(base + temp_s.offset);
				temp_s.size = sect[i].sh_size;
				ss.push_back( temp_s );
			}
		}
	}

	spin->setMaximum( (ss.size()==0)?0:ss.size()-1 );
	spin->setSuffix( " of " + QString::number( spin->maximum() ) );
	
	if( ss.size()>0 )
	{
		connect( table, SIGNAL(cellClicked(int, int)), this, SLOT(InvokeSelection(int,int)) );
		connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
		SetValues( 0 );
	}
}

void ElfStringTable::AddString( QString v, QString s )
{
	valueslist << v;
	stringlist << s;
}

void ElfStringTable::InvokeSelection( int row, int column )
{
	__uint64_t str_offset;
	__uint64_t len;
	bool conversion_result;
	
	if( row==0 ) // Section indication
	{
		str_offset = ss[ spin->value() ].offset;
		len = ss[ spin->value() ].size;
	}
	else
	{
		// also selecting the ending NULL byte
		len = stringlist[row].length() + 1;
		
		str_offset = valueslist[row].toULongLong( &conversion_result, 16 );
		
		if( !conversion_result )
			len = str_offset = 0;
	}
	
	emit S_selection_changed( str_offset, len );
}

void ElfStringTable::Update( char *data )
{
	SelectData( data );
}