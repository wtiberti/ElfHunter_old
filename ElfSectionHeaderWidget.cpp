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
* Filename: ElfSectionHeaderWidget.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfSectionHeaderWidget.h"
#include <elf.h>


ElfSectionHeaderWidget::ElfSectionHeaderWidget() : ElfMultiHeader( SECTHDRTABLEROWS, SECTHDRTABLECOLUMNS )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "Section Header # " );

	for( int i=0; i<SECTHDRTABLEROWS; i++ )
		table->verticalHeaderItem( i )->setText( secthdr_field_names[i] );
}

ElfSectionHeaderWidget::~ElfSectionHeaderWidget()
{}

void ElfSectionHeaderWidget::SetValues( int index )
{
	QString temp_string;
	Elf64_Shdr *sect64 = (Elf64_Shdr *)base;
	Elf32_Shdr *sect = (Elf32_Shdr *)base;
	__uint64_t temp_value = 0;

	sect += index;
	sect64 += index;

	stringlist.clear();
	valueslist.clear();

	temp_string.setNum( offset+index*entry_size, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// sh_name
	__uint64_t name_index;
	if( is64bit )
		name_index = sect64->sh_name;
	else
		name_index = sect->sh_name;
	temp_string.setNum( name_index, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	QString *temp_sect_name = new QString( (char*)(str_offset+name_index) );
	stringlist << *temp_sect_name;
	delete temp_sect_name;
	
	//sh_type
	__uint64_t secttype;
	if( is64bit )
		secttype = sect64->sh_type;
	else
		secttype = sect->sh_type;
	temp_string.setNum( secttype, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	
	switch( secttype )
	{
		case SHT_NULL:
			temp_string = "[Undefined]";
			break;
		case SHT_PROGBITS:
			temp_string = "Program-defined data";
			break;
		case SHT_SYMTAB:
			temp_string = "Symbol Table";
			break;
		case SHT_STRTAB:
			temp_string = "String Table";
			break;
		case SHT_RELA:
			temp_string = "Relocation entries (explicit)";
			break;
		case SHT_HASH:
			temp_string = "Symbol Hash Table";
			break;
		case SHT_DYNAMIC:
			temp_string = "Dynamic Linking Info";
			break;
		case SHT_NOTE:
			temp_string = "Auxiliary Info";
			break;
		case SHT_NOBITS:
			temp_string = "Program-defined data (no space occupied)";
			break;
		case SHT_REL:
			temp_string = "Relocation entries (implicit)";
			break;
		case SHT_SHLIB:
			temp_string = "Unspecified";
			break;
		case SHT_DYNSYM:
			temp_string = "Dynamic linking symbols";
			break;
		default:
			if( sect->sh_type>=SHT_LOPROC )
			{
				if( sect->sh_type>=SHT_LOUSER && sect->sh_type<=SHT_HIUSER )
					temp_string = "User-specific";
				else
					temp_string = "Processor-specific";
			}
			else
				temp_string = "[unknown]";
	}
	stringlist << temp_string;

	// sh_flags
	__uint64_t sectflags;
	if( is64bit )
		sectflags = sect64->sh_flags;
	else
		sectflags = sect->sh_flags;
	temp_string.setNum( sectflags, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	
	temp_string = "";
	if( sectflags & SHF_WRITE )
		temp_string.push_back( "Writeable " );
	if( sectflags & SHF_ALLOC )
		temp_string.push_back( "On-Memory " );
	if( sectflags & SHF_EXECINSTR )
		temp_string.push_back( "Executable ");
	stringlist << temp_string.trimmed();

	// sh_addr
	if( is64bit )
		temp_string.setNum( sect64->sh_addr, 16 );
	else
		temp_string.setNum( sect->sh_addr, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// sh_offset
	if( is64bit )
		temp_string.setNum( sect64->sh_offset, 16 );
	else
		temp_string.setNum( sect->sh_offset, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// sh_size
	if( is64bit )
		temp_string.setNum( sect64->sh_size, 16 );
	else
		temp_string.setNum( sect->sh_size, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// sh_link
	if( is64bit )
		temp_value = sect64->sh_link;
	else
		temp_value = sect->sh_link;
	temp_string.setNum( temp_value, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";
	// TODO : Per-section identification

	// sh_info
	if( is64bit )
		temp_string.setNum( sect64->sh_info, 16 );
	else
		temp_string.setNum( sect->sh_info, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";
	// TODO : Per-section identification

	// sh_addralign
	if( is64bit )
		temp_string.setNum( sect64->sh_addralign, 16 );
	else
		temp_string.setNum( sect->sh_addralign, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// sh_entsize
	if( is64bit )
		temp_string.setNum( sect64->sh_entsize, 16 );
	else
		temp_string.setNum( sect->sh_entsize, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	for( int i=0; i<SECTHDRTABLEROWS; i++ )
	{
		table->item( i, 0 )->setText( valueslist[i] );
		table->item( i, 1 )->setText( stringlist[i] );
	}
}

void ElfSectionHeaderWidget::SelectData( char *data )
{
	Elf32_Ehdr *header = (Elf32_Ehdr *)data;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)data;

	base = (unsigned char *) data;

	is64bit = header->e_ident[EI_CLASS]==ELFCLASS64?true:false;

	if( is64bit )
	{
		offset = header64->e_shoff;
		base += offset;
		entry_size = header64->e_shentsize;
		strsectnx = header64->e_shstrndx;

		if( header64->e_shnum==0 )
		{
			spin->setMaximum( 0 );
			return;
		}

		spin->setMaximum( header64->e_shnum-1 );
	}
	else
	{
		offset = header->e_shoff;
		base += offset;
		entry_size = header->e_shentsize;
		strsectnx = header->e_shstrndx;

		if( header->e_shnum==0 )
		{
			spin->setMaximum( 0 );
			return;
		}

		spin->setMaximum( header->e_shnum-1 );
	}

	GetShStrTable();

	spin->setSuffix( " of " + QString::number( spin->maximum() ) );
	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
	connect( table, SIGNAL(cellClicked(int, int)), this, SLOT(InvokeSelection(int,int)) );
	SetValues( 0 );
}


void ElfSectionHeaderWidget::GetShStrTable()
{
	Elf64_Shdr *sect64 = (Elf64_Shdr *)base;
	Elf32_Shdr *sect = (Elf32_Shdr *)base;
	sect += strsectnx;
	sect64 += strsectnx;

	if( is64bit )
		str_offset = sect64->sh_offset;
	else
		str_offset = sect->sh_offset;

	str_offset = (__uint64_t)base - offset + str_offset;
}

char *ElfSectionHeaderWidget::GetSectionName( char *elf, int index )
{
	int str_sect_index;
	__uint64_t name_offset;
	bool is64bitElf = false;
	char *stringsect = NULL;

	Elf32_Ehdr *header32 = (Elf32_Ehdr *)elf;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)elf;
	Elf32_Shdr *sects32;
	Elf64_Shdr *sects64;

	is64bitElf = (header32->e_ident[EI_CLASS])==ELFCLASS64?true:false;

	if( ! ElfGenericHeader::HasSections( elf ) )
		return NULL;

	if( is64bitElf )
	{
		if( index >= header64->e_shnum )
			return NULL;

		str_sect_index = header64->e_shstrndx;
		sects64 = (Elf64_Shdr *)( elf + header64->e_shoff );
		name_offset = sects64[index].sh_name;
		stringsect = (char *)( elf + sects64[str_sect_index].sh_offset + name_offset );
	}
	else
	{
		if( index >= header32->e_shnum )
			return NULL;

		str_sect_index = header32->e_shstrndx;
		sects32 = (Elf32_Shdr *)( elf + header32->e_shoff );
		name_offset = sects32[index].sh_name;
		stringsect = (char *)( elf + sects32[str_sect_index].sh_offset + name_offset );
	}
	return stringsect;
}

void ElfSectionHeaderWidget::InvokeSelection( int row, int column )
{
	__uint64_t start_offset = this->offset;
	__uint64_t size;
	
	
	start_offset += spin->value()*entry_size;
	
	if( row == 0 )
	{
		size = entry_size;
	}
	else
	{	
		if( is64bit )
		{
			start_offset += secthdr_selection_info64[ row ].start;
			size = secthdr_selection_info64[ row ].size;
		}
		else
		{
			start_offset += secthdr_selection_info[ row ].start;
			size = secthdr_selection_info[ row ].size;
		}
	}
	
	emit S_selection_changed( start_offset, size );
}