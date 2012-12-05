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
* Filename: ElfELFHeaderWidget.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfELFHeaderWidget.h"

ElfELFHeaderWidget::ElfELFHeaderWidget() : ElfGenericHeader( 20, 1 )
{
	for( int i=0; i<20; i++ )
		table->verticalHeaderItem( i )->setText( elfhdr_field_names[i] );
}

ElfELFHeaderWidget::~ElfELFHeaderWidget()
{}

void ElfELFHeaderWidget::SetElfValues( char *elfheader )
{
	QTableWidgetItem *temp_item;
	QString temp_string;
	Elf32_Ehdr *header = (Elf32_Ehdr *)elfheader;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)elfheader;

	// e_ident magic field
	QString *temp_magic = ToHexString( header->e_ident, 4 );
	stringlist << *temp_magic;
	delete temp_magic;

	// e_ident class
	switch( header->e_ident[EI_CLASS] )
	{
		case ELFCLASS32:
			temp_string = "32-Bit" ;
			break;
		case ELFCLASS64:
			is64bit = true;
			temp_string = "64-Bit";
			break;
		default:
			temp_string = "[unknown]";
	}
	stringlist << temp_string;

	//e_ident byte endian
	switch( header->e_ident[EI_DATA] )
	{
		case ELFDATA2LSB:
			temp_string = "LIttle Endian";
			break;
		case ELFDATA2MSB:
			temp_string = "Big Endian";
			break;
		default:
			temp_string = "[unknown]";
	}
	stringlist << temp_string;

	// e_ident Version
	if( header->e_ident[EI_VERSION]==EV_CURRENT )
		temp_string = "Current Version";
	else
		temp_string = "Invalid Version";
	stringlist << temp_string;

	// e_ident ABI
	switch( header->e_ident[EI_OSABI] )
	{
		case ELFOSABI_SYSV:
			temp_string = "None / Unix System V ABI";
			break;
		case ELFOSABI_HPUX:
			temp_string = "HP-UX ABI";
			break;
		case ELFOSABI_NETBSD:
			temp_string = "NetBSD ABI";
			break;
		case ELFOSABI_LINUX:
			temp_string = "Linux ABI";
			break;
		case ELFOSABI_SOLARIS:
			temp_string = "SOLARIS ABI";
			break;
		case ELFOSABI_IRIX:
			temp_string = "IRIX ABI";
			break;
		case ELFOSABI_FREEBSD:
			temp_string = "FreeBSD ABI";
			break;
		case ELFOSABI_TRU64:
			temp_string = "Unix TRU64 ABI";
			break;
		case ELFOSABI_ARM:
			temp_string = "ARM Architecture ABI";
			break;
		case ELFOSABI_STANDALONE:
			temp_string = "Stand-alone / Embedded";
			break;
		default:
			temp_string = "[unknown]";
	}
	stringlist << temp_string;

	// e_ident abiversion
	temp_string.setNum( header->e_ident[EI_ABIVERSION] );
	stringlist << temp_string;

	// e_ident size
	temp_string.setNum( EI_NIDENT );
	stringlist << temp_string;

	// e_type
	switch( header->e_type )
	{
		case ET_REL:
			temp_string = "Relocable File";
			break;
		case ET_EXEC:
			temp_string = "Executable File";
			break;
		case ET_DYN:
			temp_string = "Shared Object";
			break;
		case ET_CORE:
			temp_string = "Core File";
			break;
		default:
			temp_string = "[unknown]";
	}
	stringlist << temp_string;

	// e_machine
	switch( header->e_machine )
	{
		case EM_NONE:
			temp_string = "No machine";
			break;
		case EM_M32:
			temp_string = "AT&T WE 32100";
			break;
		case EM_SPARC:
			temp_string = "Sun Microsistems SPARC";
			break;
		case EM_386:
			temp_string = "Intel 386";
			break;
		case EM_68K:
			temp_string = "Motorola 68K";
			break;
		case EM_88K:
			temp_string = "Motorola 88K";
			break;
		case EM_860:
			temp_string = "Intel 80860";
			break;
		case EM_MIPS:
			temp_string = "MIPS RS3000 Big-Endian";
			break;
		case EM_PARISC:
			temp_string = "HP / PA";
			break;
		case EM_SPARC32PLUS:
			temp_string = "SPARC (Enhaced Instruction Set)";
			break;
		case EM_PPC:
			temp_string = "PowerPC";
			break;
		case EM_PPC64:
			temp_string = "PowerPC (64-Bit)";
			break;
		case EM_S390:
			temp_string = "IBM S/390";
			break;
		case EM_X86_64:
			temp_string = "AMD x86-64";
			break;
		default:
			temp_string = "[Not Yet Inserted]";
	}
	stringlist << temp_string;
	// e_version
	if( header->e_version==EV_CURRENT )
		temp_string = "Current Version";
	else
		temp_string = "Invalid Version";
	stringlist << temp_string;

	// e_entry
	if( is64bit )
		temp_string.setNum( header64->e_entry, 16 );
	else
		temp_string.setNum( header->e_entry, 16 );
	stringlist << temp_string.toUpper().prepend( "0x" );

	// e_phoff
	if( is64bit )
		temp_string.setNum( header64->e_phoff, 16 );
	else
		temp_string.setNum( header->e_phoff, 16 );
	stringlist << temp_string.toUpper().prepend( "0x" );

	// e_shoff
	if( is64bit )
		temp_string.setNum( header64->e_shoff, 16 );
	else
		temp_string.setNum( header->e_shoff, 16 );
	stringlist << temp_string.toUpper().prepend( "0x" );

	// e_flags
	if( is64bit )
		temp_string.setNum( header64->e_flags, 16 );
	else
		temp_string.setNum( header->e_flags, 16 );
	stringlist << temp_string.toUpper().prepend( "0x" );

	// e_ehsize
	if( is64bit )
		temp_string.setNum( header64->e_ehsize );
	else
		temp_string.setNum( header->e_ehsize );
	stringlist << temp_string;

	// e_phentsize
	if( is64bit )
		temp_string.setNum( header64->e_phentsize );
	else
		temp_string.setNum( header->e_phentsize );
	stringlist << temp_string;

	// e_phnum
	if( is64bit )
		temp_string.setNum( header64->e_phnum );
	else
		temp_string.setNum( header->e_phnum );
	stringlist << temp_string;

	// e_shentsize
	if( is64bit )
		temp_string.setNum( header64->e_shentsize );
	else
		temp_string.setNum( header->e_shentsize );
	stringlist << temp_string;

	// e_shnum
	if( is64bit )
		temp_string.setNum( header64->e_shnum );
	else
		temp_string.setNum( header->e_shnum );
	stringlist << temp_string;

	// e_shstrndx
	if( is64bit )
	{
		if( header64->e_shstrndx == SHN_UNDEF )
			temp_string = "[No section name string table]";
		else
			temp_string.setNum( header64->e_shstrndx );
	}
	else
	{
		if( header->e_shstrndx == SHN_UNDEF )
			temp_string = "[No section name string table]";
		else
			temp_string.setNum( header->e_shstrndx );
	}
	stringlist << temp_string;


	for( int i=0; i<stringlist.size(); i++ )
	{
		temp_item = new QTableWidgetItem( stringlist[i] );
		temp_item->setFlags( EHW_ITEMFLAGS );
		table->setItem( i, 0, temp_item );
	}
	
	connect( table, SIGNAL(cellClicked(int, int)), this, SLOT(InvokeSelection(int,int)) );
}

void ElfELFHeaderWidget::InvokeSelection( int row, int column )
{
	__uint64_t offset = 0;
	__uint64_t size = 0;
	
	if( row < table->rowCount() )
	{
		if( is64bit )
		{
			offset = elfhdr_selection_info64[row].start;
			size = elfhdr_selection_info64[row].size;
		}
		else
		{
			offset = elfhdr_selection_info[row].start;
			size = elfhdr_selection_info[row].size;
		}
		emit S_selection_changed( offset, size );
	}
}