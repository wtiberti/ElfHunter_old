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

#include "ElfSectionHeaderWidget.h"
#include "ElfHunterRelTable.h"
#include <elf.h>

ElfHunterRelTable::ElfHunterRelTable() : ElfMultiHeader( 0, 5 )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "Relocations # " );
	
	table->horizontalHeader()->setResizeMode( QHeaderView::Interactive );
	
	table->horizontalHeaderItem(0)->setText( "[SECT#]" );
	table->horizontalHeaderItem(1)->setText( "[OFFSET]" );
	table->horizontalHeaderItem(2)->setText( "r_offset" );

	table->horizontalHeaderItem(4)->setText( "r_addend" );
	
	table->horizontalHeader()->setStretchLastSection( true );
	
	le_search->hide();
}

ElfHunterRelTable::~ElfHunterRelTable()
{
	offsetlist.clear();
	addendlist.clear();
	
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
	
	table->horizontalHeaderItem(3)->setText( "r_info(sym:type)" );
	
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
	
	ss.clear();
	
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
	
	spin->setMaximum( (ss.size()==0)?0:ss.size()-1 );
	spin->setSuffix( " of " + QString::number( spin->maximum() ) );
	if( ss.size()>0 )
	{
		connect( table, SIGNAL(cellClicked(int, int)), this, SLOT(InvokeSelection(int,int)) );
		connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
		SetValues( 0 );
	}
}

void ElfHunterRelTable::SetValues( int index )
{
	QString section;
	QString temp_string;
	__uint64_t reloc_start = (__uint64_t)ss[index].addr;
	__uint64_t cursor = ss[index].offset;
	
	/* Here how data is collected:
	offsetlist <- generic file offset
	stringlist <- r_offset
	valuelist <- r_info
	addendlist <- r_addend */
	
	section = QString( ElfSectionHeaderWidget::GetSectionName( (char*)base, ss[index].sect_n ) );
	section += " ( " + QString::number( ss[index].sect_n ) + " )";
	
	stringlist.clear();
	valueslist.clear();
	
	offsetlist.clear();
	addendlist.clear();
	
	if( isRela[index] )
	{
		if( is64bit )
		{
			Elf64_Rela *rela64 = (Elf64_Rela *) reloc_start;
			
			while( (__uint64_t)rela64 < (__uint64_t)(reloc_start+ss[index].size) )
			{
				temp_string.setNum( cursor, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				offsetlist << temp_string;
				
				temp_string.setNum( rela64->r_offset, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				stringlist << temp_string;
				
				temp_string = Parse_Info_Field( rela64->r_info );
				valueslist << temp_string;
				
				temp_string.setNum( rela64->r_addend, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				addendlist << temp_string;
				
				rela64++;
				cursor += sizeof( Elf64_Rela );
			}
		}
		else
		{
			Elf32_Rela *rela = (Elf32_Rela *) reloc_start;
			
			while( (__uint64_t)rela < (__uint64_t)(reloc_start+ss[index].size) )
			{
				temp_string.setNum( cursor, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				offsetlist << temp_string;

				temp_string.setNum( rela->r_offset, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				stringlist << temp_string;
				
				temp_string = Parse_Info_Field( rela->r_info );
				valueslist << temp_string;
				
				temp_string.setNum( rela->r_addend, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				addendlist << temp_string;

				rela++;
				cursor += sizeof( Elf32_Rela );
			}
		}
	}
	else
	{
		if( is64bit )
		{
			Elf64_Rel *rel64 = (Elf64_Rel *) reloc_start;
			
			while( (__uint64_t)rel64 < (__uint64_t)(reloc_start+ss[index].size) )
			{
				temp_string.setNum( cursor, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				offsetlist << temp_string;

				temp_string.setNum( rel64->r_offset, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				stringlist << temp_string;

				temp_string.setNum( rel64->r_info, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				valueslist << temp_string;
				
				rel64++;
				cursor += sizeof( Elf64_Rel );
			}
		}
		else
		{
			Elf32_Rel *rel = (Elf32_Rel *) reloc_start;
			
			while( (__uint64_t)rel < (__uint64_t)(reloc_start+ss[index].size) )
			{
				temp_string.setNum( cursor, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				offsetlist << temp_string;
				
				temp_string.setNum( rel->r_offset, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				stringlist << temp_string;

				temp_string.setNum( rel->r_info, 16 );
				temp_string = temp_string.toUpper().prepend( "0x" );
				valueslist << temp_string;
				
				rel++;
				cursor += sizeof( Elf32_Rel );
			}
		}
	}
	
	ClearRows();
	
	QTableWidgetItem *table_item;
	
	for( int i=0; i<offsetlist.size(); i++ )
	{
		AddRow();
		
		table_item = new QTableWidgetItem( section );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 0, table_item );
		
		table_item = new QTableWidgetItem( offsetlist[i] );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 1, table_item );
		
		table_item = new QTableWidgetItem( stringlist[i] );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 2, table_item );
		
		table_item = new QTableWidgetItem( valueslist[i] );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 3, table_item );
		
		if( isRela[index] )
		{
			table_item = new QTableWidgetItem( addendlist[i] );
			table_item->setFlags( (Qt::ItemFlag)37 );
			table->setItem( i, 4, table_item );
		}
	}
	table->horizontalHeader()->resizeSections( QHeaderView::ResizeToContents );
}

void ElfHunterRelTable::InvokeSelection( int row, int column )
{
	unsigned int spin_value = spin->value();
	
	__uint64_t offset = ss[spin_value].offset;
	__uint64_t size = 0;
	

	if( column == 0 )
	{
		// Selects the whole section

		size = ss[spin_value].size;
	}
	else
	{
		// NOTE: A Rel Section does not have r_addend!
		if( column == 1 || (column==4 && !isRela[spin_value]) )
		{
			// Selects the whole entry in the table
			
			if( is64bit )
				size = (isRela[spin_value]==true)?sizeof(Elf64_Rela):sizeof(Elf64_Rel);
			else
				size = (isRela[spin_value]==true)?sizeof(Elf32_Rela):sizeof(Elf32_Rel);
			
			offset += row*size;
		}
		else
		{
			if( is64bit )
				size = (isRela[spin_value]==true)?sizeof(Elf64_Rela):sizeof(Elf64_Rel);
			else
				size = (isRela[spin_value]==true)?sizeof(Elf32_Rela):sizeof(Elf32_Rel);
			
			if( is64bit )
			{
				offset += (row*size) + reltbl_selection_info64[column].start;
				size = reltbl_selection_info64[column].size;
			}
			else
			{
				offset += (row*size) + reltbl_selection_info[column].start;
				size = reltbl_selection_info[column].size;
			}
		}
	}
	emit S_selection_changed( offset, size );
}

QString ElfHunterRelTable::Parse_Info_Field( __uint64_t value )
{
	QString result;
	
	if( is64bit )
	{
		result = "0x%1 - 0x%2";
		result = result.arg( QString::number(value>>32, 16).toUpper(), 8, '0' ) // Symbol Index
						.arg( QString::number((value&0xFFFFFFFF), 16).toUpper(), 8, '0' ); // Type
	}
	else
	{
		result = "0x%1 - 0x%2";
		result = result.arg(QString::number(value&0xFF, 16).toUpper(), 2, '0' )
							.arg(QString::number((value>>8)&0xFF, 16).toUpper(), 2, '0' );
	}
	
	return result;
}

void ElfHunterRelTable::Update( char *data )
{
	SelectData( data );
}