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
#include <elf.h>

ElfSymTable::ElfSymTable() : ElfMultiHeader( 8, 2 )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "Symbol # " );
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

		temp_string = new QString();
		temp_string->setNum( sym64.offsets[index], 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		//TODO index to string
		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_name, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_info, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_other, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_shndx, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_value, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym64.symv[index]->st_size, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
	}
	else
	{
		temp_string = new QString();
		temp_string->setNum( sym32.sects[index] );
		valueslist << *temp_string;

		temp_string = new QString();
		temp_string->setNum( sym32.offsets[index], 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_name, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_value, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_size, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_info, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_other, 16 );
		valueslist << temp_string->toUpper().prepend("0x");

		temp_string = new QString();
		temp_string->setNum( sym32.symv[index]->st_shndx, 16 );
		valueslist << temp_string->toUpper().prepend("0x");
	}

	for( int i=0; i<8; i++ )
	{
		table->item( i, 0 )->setText( valueslist[i] );

		//table->item( i, 1 )->setText( stringlist[i] );
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

	spin->setMaximum( ReadSymbols()-1 );
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

		//TEST
		/*
		qDebug() << "Grandezze sym64: " << sym64.symv.size() << " - "
			 << sym64.offsets.size() << " - " << sym64.sects.size() << "\n";

		qDebug() << "Terzo elemento: " << sym64.symv[2]->st_value << "\n"
			 << sym64.offsets[2] << "\n" << sym64.sects[2] << "\n";
		*/

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


