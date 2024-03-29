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
* Filename: ElfProgHeaderWidget.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfProgHeaderWidget.h"
#include <elf.h>

ElfProgHeaderWidget::ElfProgHeaderWidget() : ElfMultiHeader( PROGHDRTABLEROWS, PROGHDRTABLECOLUMNS )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "Program Header # " );
	le_search->hide();
}

void ElfProgHeaderWidget::SetValues( int index )
{
	QString temp_string;
	QString temp_value;
	Elf64_Phdr *prog64 = (Elf64_Phdr *)base;
	Elf32_Phdr *prog = (Elf32_Phdr *)base;

	prog += index;
	prog64 += index;

	stringlist.clear();
	valueslist.clear();

	// p_type
	__uint64_t prgtype;
	if( is64bit )
		prgtype = prog64->p_type;
	else
		prgtype = prog->p_type;

	temp_value.setNum( prgtype, 16 );
	valueslist << temp_value.toUpper().prepend( "0x" );

	switch( prgtype )
	{
		case PT_NULL:
			temp_string = "PT_NULL";
			break;
		case PT_LOAD:
			temp_string = "PT_LOAD";
			break;
		case PT_DYNAMIC:
			temp_string = "PT_DYNAMIC";
			break;
		case PT_INTERP:
			temp_string = "PT_INTERP";
			break;
		case PT_NOTE:
			temp_string = "PT_NOTE";
			break;
		case PT_SHLIB:
			temp_string = "PT_SHLIB";
			break;
		case PT_PHDR:
			temp_string = "PT_PHDR";
			break;
		default:
			if( prgtype>=PT_LOOS && prgtype<=PT_HIOS )
				temp_string = "Environment-specific";
			else
				if( prgtype>=PT_LOPROC && prgtype<=PT_HIPROC )
					temp_string = "Processor-specific";
				else
					temp_string = "[unknown]";
	}
	stringlist << temp_string;

	// Data offset
	if( is64bit )
		temp_string.setNum( prog64->p_offset, 16 );
	else
		temp_string.setNum( prog->p_offset, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// Virtual Address
	if( is64bit )
		temp_string.setNum( prog64->p_vaddr, 16 );
	else
		temp_string.setNum( prog->p_vaddr, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// Physical Address
	if( is64bit )
		temp_string.setNum( prog64->p_paddr, 16 );
	else
		temp_string.setNum( prog->p_paddr, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// p_filesz
	if( is64bit )
		temp_string.setNum( prog64->p_filesz, 16 );
	else
		temp_string.setNum( prog->p_filesz, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// p_memsz
	if( is64bit )
		temp_string.setNum( prog64->p_memsz, 16 );
	else
		temp_string.setNum( prog->p_memsz, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	// flags
	__uint64_t prgflags;
	if( is64bit )
		prgflags = prog64->p_flags;
	else
		prgflags = prog->p_flags;

	temp_value.setNum( prgflags, 16 );
	valueslist << temp_value.toUpper().prepend( "0x" );

	temp_string = "";
	if( prgflags & PF_R )
		temp_string.push_back( "Readable " );
	if( prgflags & PF_W )
		temp_string.push_back( "Writeable " );
	if( prgflags & PF_X )
		temp_string.push_back( "Executable ");
	stringlist << temp_string.trimmed();

	// p_align
	if( is64bit )
		temp_string.setNum( prog64->p_align, 16 );
	else
		temp_string.setNum( prog->p_align, 16 );
	valueslist << temp_string.toUpper().prepend( "0x" );
	stringlist << "";

	if( is64bit )
	{
		valueslist.move( 6, 1 );
		stringlist.move( 6, 1 );
	}

	for( int i=0; i<PROGHDRTABLEROWS; i++ )
	{
		table->item( i, 0 )->setText( valueslist[i] );
		table->item( i, 1 )->setText( stringlist[i] );
	}
}

void ElfProgHeaderWidget::SelectData( char *data )
{
	Elf32_Ehdr *header = (Elf32_Ehdr *)data;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)data;

	base = (unsigned char *) data;

	is64bit = header->e_ident[EI_CLASS]==ELFCLASS64?true:false;

	if( is64bit )
	{
		offset = header64->e_phoff;
		base += offset;
		entry_size = header64->e_phentsize;

		if( header64->e_phnum==0 )
			return;

		spin->setMaximum( header64->e_phnum-1 );
	}
	else
	{
		offset = header->e_phoff;
		base += offset;
		entry_size = header->e_phentsize;

		if( header->e_phnum==0 )
		{
			spin->setMaximum( 0 );
			return;
		}

		spin->setMaximum( header->e_phnum-1 );
	}

	spin->setSuffix( " of " + QString::number( spin->maximum() ) );
	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
	connect( table, SIGNAL(cellClicked(int, int)), this, SLOT(InvokeSelection(int,int)) );

	table->verticalHeaderItem( 0 )->setText( "p_type" );
	if( is64bit )
	{
		table->verticalHeaderItem( 1 )->setText( "p_flags" );
		table->verticalHeaderItem( 2 )->setText( "p_offset" );
		table->verticalHeaderItem( 3 )->setText( "p_vaddr" );
		table->verticalHeaderItem( 4 )->setText( "p_paddr" );
		table->verticalHeaderItem( 5 )->setText( "p_filesz" );
		table->verticalHeaderItem( 6 )->setText( "p_memsz" );
	}
	else
	{
		table->verticalHeaderItem( 1 )->setText( "p_offset" );
		table->verticalHeaderItem( 2 )->setText( "p_vaddr" );
		table->verticalHeaderItem( 3 )->setText( "p_paddr" );
		table->verticalHeaderItem( 4 )->setText( "p_filesz" );
		table->verticalHeaderItem( 5 )->setText( "p_memsz" );
		table->verticalHeaderItem( 6 )->setText( "p_flags" );
	}
	table->verticalHeaderItem( 7 )->setText( "p_align" );
	SetValues( 0 );
}

void ElfProgHeaderWidget::InvokeSelection( int row, int column )
{
	__uint64_t start_offset = this->offset;
	__uint64_t size;


	start_offset += entry_size * spin->value();

	if( is64bit )
	{
		start_offset += proghdr_selection_info64[ row ].start;
		size = proghdr_selection_info64[ row ].size;
	}
	else
	{
		start_offset += proghdr_selection_info[ row ].start;
		size = proghdr_selection_info[ row ].size;
	}

	emit S_selection_changed( start_offset, size );
}

void ElfProgHeaderWidget::Update( char *data )
{
	SelectData( data );
}