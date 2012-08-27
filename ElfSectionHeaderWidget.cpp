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
	QString *temp_string;
	Elf64_Shdr *sect64 = (Elf64_Shdr *)base;
	Elf32_Shdr *sect = (Elf32_Shdr *)base;

	sect += index;
	sect64 += index;

	stringlist.clear();
	valueslist.clear();

	temp_string = new QString();
	temp_string->setNum( offset+index*entry_size, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	stringlist << "";

	// sh_name
	__uint64_t name_index;
	if( is64bit )
		name_index = sect64->sh_name;
	else
		name_index = sect->sh_name;
	temp_string = new QString();
	temp_string->setNum( name_index, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	stringlist << *(new QString( (char*)(str_offset+name_index) ) );

	//sh_type
	__uint64_t secttype;
	if( is64bit )
		secttype = sect64->sh_type;
	else
		secttype = sect->sh_type;
	temp_string = new QString();
	temp_string->setNum( secttype, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	switch( secttype )
	{
		case SHT_NULL:
			temp_string = new QString( "[Undefined]" );
			break;
		case SHT_PROGBITS:
			temp_string = new QString( "Program-defined data" );
			break;
		case SHT_SYMTAB:
			temp_string = new QString( "Symbol Table" );
			break;
		case SHT_STRTAB:
			temp_string = new QString( "String Table" );
			break;
		case SHT_RELA:
			temp_string = new QString( "Relocation entries (explicit)" );
			break;
		case SHT_HASH:
			temp_string = new QString( "Symbol Hash Table" );
			break;
		case SHT_DYNAMIC:
			temp_string = new QString( "Dynamic Linking Info" );
			break;
		case SHT_NOTE:
			temp_string = new QString( "Auxiliary Info" );
			break;
		case SHT_NOBITS:
			temp_string = new QString( "Program-defined data (no space occupied)" );
			break;
		case SHT_REL:
			temp_string = new QString( "Relocation entries (implicit)" );
			break;
		case SHT_SHLIB:
			temp_string = new QString( "Unspecified" );
			break;
		case SHT_DYNSYM:
			temp_string = new QString( "Dynamic linking symbols" );
			break;
		default:
			if( sect->sh_type>=SHT_LOPROC )
			{
				if( sect->sh_type>=SHT_LOUSER && sect->sh_type<=SHT_HIUSER )
					temp_string = new QString( "User-specific" );
				else
					temp_string = new QString( "Processor-specific" );
			}
			else
				temp_string = new QString( "[unknown]" );
	}
	stringlist << *temp_string;

	// sh_flags
	__uint64_t sectflags;
	if( is64bit )
		sectflags = sect64->sh_flags;
	else
		sectflags = sect->sh_flags;
	temp_string = new QString();
	temp_string->setNum( sectflags, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	temp_string = new QString("");
	if( sectflags & SHF_WRITE )
		temp_string->push_back( "Writeable " );
	if( sectflags & SHF_ALLOC )
		temp_string->push_back( "On-Memory " );
	if( sectflags & SHF_EXECINSTR )
		temp_string->push_back( "Executable ");
	stringlist << temp_string->trimmed();

	// sh_addr
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_addr, 16 );
	else
		temp_string->setNum( sect->sh_addr, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	stringlist << "";

	// sh_offset
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_offset, 16 );
	else
		temp_string->setNum( sect->sh_offset, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	stringlist << "";

	// sh_size
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_size, 10 );
	else
		temp_string->setNum( sect->sh_size, 10 );
	valueslist << *temp_string;
	stringlist << "";

	// sh_link
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_link, 16 );
	else
		temp_string->setNum( sect->sh_link, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	stringlist << "";

	// sh_info
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_info, 16 );
	else
		temp_string->setNum( sect->sh_info, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	stringlist << "";

	// sh_addralign
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_addralign, 16 );
	else
		temp_string->setNum( sect->sh_addralign, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
	stringlist << "";

	// sh_entsize
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_entsize, 16 );
	else
		temp_string->setNum( sect->sh_entsize, 16 );
	valueslist << temp_string->toUpper().prepend( "0x" );
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

	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
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