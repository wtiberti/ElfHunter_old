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
* Filename: ElfHunterRelTable.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfHunterRelTable.h"
#include <elf.h>

ElfHunterRelTable::ElfHunterRelTable() : ElfMultiHeader( 0, 5 )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "Relocations # " );
	
	table->horizontalHeader()->setResizeMode( QHeaderView::Interactive );
	
	table->horizontalHeaderItem(0)->setText( "[SECTION]" );
	table->horizontalHeaderItem(1)->setText( "[OFFSET]" );
	table->horizontalHeaderItem(2)->setText( "r_offset" );
	table->horizontalHeaderItem(3)->setText( "r_info" );
	table->horizontalHeaderItem(4)->setText( "r_addend" );
}

ElfHunterRelTable::~ElfHunterRelTable()
{
	ss.clear();
	isRela.clear();
}

void ElfHunterRelTable::SelectData( char *data )
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
		sectnum = header64->e_shnum;
	}
	else
	{
		sectoff = header->e_shoff;
		sectnum = header->e_shnum;
	}

	sect = (Elf32_Shdr *)(data+sectoff);
	sect64 = (Elf64_Shdr *)(data+sectoff);
	
	for( unsigned int i=0; i<sectnum; i++ )
	{
		if( is64bit )
		{
			if( sect64[i].sh_type==SHT_REL ||
				sect64[i].sh_type==SHT_RELA )
			{
				temp_s.sect_n = i;
				temp_s.index_name = sect64[i].sh_name;
				temp_s.offset = sect64[i].sh_offset;
				temp_s.addr = (char *)(base + temp_s.offset);
				temp_s.size = sect64[i].sh_size;
				ss.push_back( temp_s );
				
				if( sect64[i].sh_type==SHT_RELA )
					isRela.push_back( true );
				else
					isRela.push_back( false );
			}
		}
		else
		{
			if( sect[i].sh_type==SHT_REL ||
				sect[i].sh_type==SHT_RELA )
			{
				temp_s.sect_n = i;
				temp_s.index_name = sect[i].sh_name;
				temp_s.offset = sect[i].sh_offset;
				temp_s.addr = (char *)(base + temp_s.offset);
				temp_s.size = sect[i].sh_size;
				ss.push_back( temp_s );
				
				if( sect[i].sh_type==SHT_RELA )
					isRela.push_back( true );
				else
					isRela.push_back( false );
			}
		}
	}
	
	spin->setMaximum( (ss.size()==0)?0:ss.size() );
	spin->setSuffix( " of " + QString::number( spin->maximum() ) );
	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
	connect( table, SIGNAL(cellClicked(int, int)), this, SLOT(InvokeSelection(int,int)) );
	if( ss.size()>0 )
		SetValues( 0 );
}

void ElfHunterRelTable::SetValues( int index )
{
	qDebug() << "Index=" << index;
}

void ElfHunterRelTable::InvokeSelection( int row, int column )
{
	//TODO
	emit S_selection_changed( 0, column );
}
