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
* Filename: ElfSymTable.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfSymTable.h"
#include "ElfSectionHeaderWidget.h"
#include <elf.h>

ElfSymTable::ElfSymTable() : ElfMultiHeader( 8, 2 )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "Symbol # " );
	sym_strtable = NULL;
}

ElfSymTable::~ElfSymTable()
{}

void ElfSymTable::SetValues( int index )
{
	QString *temp_string;

	stringlist.clear();
	valueslist.clear();

	if( is64bit )
	{
		temp_string = new QString();
		temp_string->setNum( sym64.sects[index] );
		valueslist << *temp_string;
		stringlist << ElfSectionHeaderWidget::GetSectionName( (char *)base, sym64.sects[index] );

		temp_string = new QString();
		temp_string->setNum( sym64.offsets[index], 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << "";

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_name, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << (sym_strtable+sym64.symv[index]->st_name);

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_info, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		temp_string = new QString();
		switch( sym64.symv[index]->st_info >> 4 )
		{
			case STB_LOCAL:
				*temp_string += "Local ";
				break;
			case STB_GLOBAL:
				*temp_string += "Global ";
				break;
			case STB_WEAK:
				*temp_string += "Weak ";
				break;
			case 10: // ST_LOOS
			case 11: //
			case 12: // ST_HIOS
				*temp_string += "Environment-Specific ";
				break;
			case 13: // ST_LOPROC
			case 14: //
			case 15: // ST_HIPROC
				*temp_string += "Processor-Specific ";
		}
		switch( sym64.symv[index]->st_info & 0x0F )
		{
			case STT_NOTYPE:
				*temp_string += "Absolute";
				break;
			case STT_OBJECT:
				*temp_string += "DataObject";
				break;
			case STT_FUNC:
				*temp_string += "Function";
				break;
			case STT_SECTION:
				*temp_string += "Section";
				break;
			case STT_FILE:
				*temp_string += "SourceFile";
				break;
			case 10:
			case 11:
			case 12:
				*temp_string += "Environment-Specific";
				break;
			case 13:
			case 14:
			case 15:
				*temp_string += "Processor-Specific";
		}
		stringlist << *temp_string;

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_other, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << "";

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_shndx );
		valueslist << *temp_string;
		switch( sym64.symv[index]->st_shndx )
		{
			case SHN_UNDEF:
				stringlist << "[Undefined]";
				break;
			case SHN_ABS:
				stringlist << "[Absolute]";
				break;
			case SHN_COMMON:
				stringlist << "[Common]";
				break;
			default:
				stringlist << ElfSectionHeaderWidget::GetSectionName( (char *)base, sym64.symv[index]->st_shndx );
		}

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_value, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << "";

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_size, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << "";
	}
	else
	{
		temp_string = new QString();
		temp_string->setNum( sym32.sects[index] );
		valueslist << *temp_string;
		stringlist << ElfSectionHeaderWidget::GetSectionName( (char *)base, sym32.sects[index] );

		temp_string = new QString();
		temp_string->setNum( sym32.offsets[index], 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << "";

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_name, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << (sym_strtable+sym32.symv[index]->st_name);

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_value, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << "";

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_size, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << "";

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_info, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		temp_string = new QString();
		switch( sym32.symv[index]->st_info >> 4 )
		{
			case STB_LOCAL:
				*temp_string += "Local ";
				break;
			case STB_GLOBAL:
				*temp_string += "Global ";
				break;
			case STB_WEAK:
				*temp_string += "Weak ";
				break;
			case 10: // ST_LOOS
			case 11: //
			case 12: // ST_HIOS
				*temp_string += "Environment-Specific ";
				break;
			case 13: // ST_LOPROC
			case 14: //
			case 15: // ST_HIPROC
				*temp_string += "Processor-Specific ";
		}
		switch( sym32.symv[index]->st_info & 0x0F )
		{
			case STT_NOTYPE:
				*temp_string += "Absolute";
				break;
			case STT_OBJECT:
				*temp_string += "DataObject";
				break;
			case STT_FUNC:
				*temp_string += "Function";
				break;
			case STT_SECTION:
				*temp_string += "Section";
				break;
			case STT_FILE:
				*temp_string += "SourceFile";
				break;
			case 10:
			case 11:
			case 12:
				*temp_string += "Environment-Specific";
				break;
			case 13:
			case 14:
			case 15:
				*temp_string += "Processor-Specific";
		}
		stringlist << *temp_string;

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_other, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
		stringlist << "";

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_shndx );
		valueslist << *temp_string;
		switch( sym32.symv[index]->st_shndx )
		{
			case SHN_UNDEF:
				stringlist << "[Undefined]";
				break;
			case SHN_ABS:
				stringlist << "[Absolute]";
				break;
			case SHN_COMMON:
				stringlist << "[Common]";
				break;
			default:
				stringlist << ElfSectionHeaderWidget::GetSectionName( (char *)base, sym32.symv[index]->st_shndx );
		}
	}

	for( int i=0; i<8; i++ )
	{
		table->item( i, 0 )->setText( valueslist[i] );
		table->item( i, 1 )->setText( stringlist[i] );
	}
}

void ElfSymTable::SelectData( char *data )
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
			if( sect64[i].sh_type==SHT_SYMTAB )
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
			if( sect[i].sh_type==SHT_SYMTAB )
			{
				temp_s.sect_n = i;
				temp_s.index_name = sect[i].sh_name;
				temp_s.offset = sect[i].sh_offset;
				temp_s.addr = (char *)(base + temp_s.offset);
				temp_s.size = sect[i].sh_size;
				ss.push_back( temp_s );
			}
		}
	}


	table->verticalHeaderItem( 0 )->setText( "[Section]" );
	table->verticalHeaderItem( 1 )->setText( "[Offset]" );
	table->verticalHeaderItem( 2 )->setText( "st_name" );
	if( is64bit )
	{
		table->verticalHeaderItem( 3 )->setText( "st_info" );
		table->verticalHeaderItem( 4 )->setText( "st_other" );
		table->verticalHeaderItem( 5 )->setText( "st_shndx" );
		table->verticalHeaderItem( 6 )->setText( "st_value" );
		table->verticalHeaderItem( 7 )->setText( "st_size" );
	}
	else
	{
		table->verticalHeaderItem( 3 )->setText( "st_value" );
		table->verticalHeaderItem( 4 )->setText( "st_size" );
		table->verticalHeaderItem( 5 )->setText( "st_info" );
		table->verticalHeaderItem( 6 )->setText( "st_other" );
		table->verticalHeaderItem( 7 )->setText( "st_shndx" );
	}

	sym_strtable = GetSymNameStrTable( data );

	spin->setMaximum( ReadSymbols()-1 );
	spin->setSuffix( " of " + QString::number( spin->maximum() ) );
	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
	SetValues( 0 );
}

unsigned int ElfSymTable::ReadSymbols()
{
	unsigned int sym_off; // relative to section

	sym32.symv.clear();
	sym32.offsets.clear();
	sym32.sects.clear();
	sym64.symv.clear();
	sym64.offsets.clear();
	sym64.sects.clear();

	if( is64bit )
	{
		//for each SectStruct...
		for( unsigned int i=0; i<ss.size(); i++ )
		{
			sym_off = 0;

			while( sym_off < ss[i].size )
			{
				sym64.sects.push_back( ss[i].sect_n );
				sym64.symv.push_back( (Elf64_Sym *)(ss[i].addr+sym_off) );
				sym64.offsets.push_back( ss[i].offset+sym_off );

				sym_off+=sizeof( Elf64_Sym );
			}
		}
		return sym64.symv.size();
	}
	else
	{
		for( unsigned int i=0; i<ss.size(); i++ )
		{
			sym_off = 0;

			while( sym_off < ss[i].size )
			{
				sym32.sects.push_back( ss[i].sect_n );
				sym32.symv.push_back( (Elf32_Sym *)(ss[i].addr+sym_off) );
				sym32.offsets.push_back( ss[i].offset+sym_off );

				sym_off+=sizeof( Elf32_Sym );
			}
		}
		return sym32.symv.size();
	}
}

char *ElfSymTable::GetSymNameStrTable( char *elf )
{
	/* The situation is this: we have got a lot
	 * of symbols. Each symbol has a st_name field
	 * which specify the offset in "the string table"
	 * where the symbol name is located.
	 *
	 * The question is: Which one ?
	 *
	 * ...so here we try to search for the ".strtable"
	 * section, expecting it to be the "one" - WT
	 */

	bool is64bitElf = false;
	char *temp_name = NULL;

	Elf32_Ehdr *header = (Elf32_Ehdr *)elf;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)elf;

	Elf64_Shdr *sect64;
	Elf32_Shdr *sect;

	is64bitElf = header->e_ident[EI_CLASS]==ELFCLASS64?true:false;

	if( is64bitElf )
	{
		sect64 = (Elf64_Shdr *)(elf + header64->e_shoff);

		for( int i=0; i<header64->e_shnum; i++ )
		{
			temp_name = ElfSectionHeaderWidget::GetSectionName( elf, i );

			if( strncmp( temp_name, ".strtab", 7 )==0 )
			{
				temp_name = elf + (sect64[i].sh_offset);
				return temp_name;
			}
		}
		return NULL;
	}
	else
	{
		sect = (Elf32_Shdr *)(elf + header->e_shoff);

		for( int i=0; i<header->e_shnum; i++ )
		{
			temp_name = ElfSectionHeaderWidget::GetSectionName( elf, i );

			if( strncmp( temp_name, ".strtab", 7 )==0 )
			{
				temp_name = elf + (sect[i].sh_offset);
				return temp_name;
			}
		}
		return NULL;
	}
}