#include "ElfHeaderWidget.h"

#include <elf.h>
#include <cstdio>
#include <cstring>

extern QString *ToHexString( unsigned char *stream, unsigned int size );

ElfHeaderWidget::ElfHeaderWidget()
{
	QTableWidgetItem *tempitem;

	layout = new QVBoxLayout();
	table = new QTableWidget( ELFHDRTABLEROWS, ELFHDRTABLECOLUMNS, this );
	table->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );


	for( int i=0; i<ELFHDRTABLECOLUMNS; i++ )
	{
		// Horizontal table headers
		tempitem = new QTableWidgetItem( "Value" );
		tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setHorizontalHeaderItem( i, tempitem );
	}

	for( int i=0; i<ELFHDRTABLEROWS; i++ )
	{
		tempitem = new QTableWidgetItem( elfhdr_field_names[i] );
		//tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setVerticalHeaderItem( i, tempitem );
	}

	table->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
	table->horizontalHeader()->setResizeMode( QHeaderView::Stretch  );

	layout->addWidget( table );

	setLayout( layout );

	read = false;
	is64bit = false;
	ph_num = 0;
	sh_num = 0;
	ph_size = 0;
	sh_size = 0;
}

ElfHeaderWidget::~ElfHeaderWidget()
{
	for( int i=0; i<ELFHDRTABLECOLUMNS; i++ )
	{
		for( int j=0; j<ELFHDRTABLEROWS; j++ )
		{
			delete table->item( j, i );
		}
	}

	for( int i=0; i<ELFHDRTABLECOLUMNS; i++ )
		delete table->horizontalHeaderItem( i );

	for( int i=0; i<ELFHDRTABLEROWS; i++ )
		delete table->verticalHeaderItem( i );


	/*
	for( int i=0; i<stringlist.size(); i++ )
	{
		delete stringlist[i];
	}*/

	stringlist.clear();

	delete table;
	delete layout;
}

void ElfHeaderWidget::GetValues( char *elfheader )
{
	QTableWidgetItem *temp_item;
	QString *temp_string;
	Elf32_Ehdr *header = (Elf32_Ehdr *)elfheader;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)elfheader;


	// e_ident magic field
	temp_string = ToHexString( header->e_ident, 4 );
	stringlist << *temp_string;

	// e_ident class
	temp_string = new QString();
	switch( header->e_ident[EI_CLASS] )
	{
		case ELFCLASS32:
			temp_string = new QString( "32-Bit" );
			break;
		case ELFCLASS64:
			is64bit = true;
			temp_string = new QString( "64-Bit" );
			break;
		default:
			temp_string = new QString( "[unknown]" );
	}
	stringlist << *temp_string;

	//e_ident byte endian
	temp_string = new QString();
	switch( header->e_ident[EI_DATA] )
	{
		case ELFDATA2LSB:
			temp_string = new QString( "LIttle Endian" );
			break;
		case ELFDATA2MSB:
			temp_string = new QString( "Big Endian" );
			break;
		default:
			temp_string = new QString( "[unknown]" );
	}
	stringlist << *temp_string;

	// e_ident Version
	temp_string = new QString();
	if( header->e_ident[EI_VERSION]==EV_CURRENT )
		temp_string = new QString( "Current Version" );
	else
		temp_string = new QString( "Invalid Version" );
	stringlist << *temp_string;

	// e_ident ABI
	temp_string = new QString();
	switch( header->e_ident[EI_OSABI] )
	{
		case ELFOSABI_SYSV:
			temp_string = new QString( "None / Unix System V ABI" );
			break;
		case ELFOSABI_HPUX:
			temp_string = new QString( "HP-UX ABI" );
			break;
		case ELFOSABI_NETBSD:
			temp_string = new QString( "NetBSD ABI" );
			break;
		case ELFOSABI_LINUX:
			temp_string = new QString( "Linux ABI" );
			break;
		case ELFOSABI_SOLARIS:
			temp_string = new QString( "SOLARIS ABI" );
			break;
		case ELFOSABI_IRIX:
			temp_string = new QString( "IRIX ABI" );
			break;
		case ELFOSABI_FREEBSD:
			temp_string = new QString( "FreeBSD ABI" );
			break;
		case ELFOSABI_TRU64:
			temp_string = new QString( "Unix TRU64 ABI" );
			break;
		case ELFOSABI_ARM:
			temp_string = new QString( "ARM Architecture ABI" );
			break;
		case ELFOSABI_STANDALONE:
			temp_string = new QString( "Stand-alone / Embedded" );
			break;
		default:
			temp_string = new QString( "[unknown]" );
	}
	stringlist << *temp_string;

	// e_ident abiversion
	temp_string = new QString();
	temp_string->setNum( header->e_ident[EI_ABIVERSION] );
	stringlist << *temp_string;

	// e_ident size
	temp_string = new QString();
	temp_string->setNum( header->e_ident[EI_NIDENT] );
	stringlist << *temp_string;

	// e_type
	temp_string = new QString();
	switch( header->e_type )
	{
		case ET_REL:
			temp_string = new QString( "Relocable File" );
			break;
		case ET_EXEC:
			temp_string = new QString( "Executable File" );
			break;
		case ET_DYN:
			temp_string = new QString( "Shared Object" );
			break;
		case ET_CORE:
			temp_string = new QString( "Core File" );
			break;
		default:
			temp_string = new QString( "[unknown]" );
	}
	stringlist << *temp_string;

	// e_machine
	temp_string = new QString();
	switch( header->e_machine )
	{
		case EM_NONE:
			temp_string = new QString( "No machine" );
			break;
		case EM_M32:
			temp_string = new QString( "AT&T WE 32100" );
			break;
		case EM_SPARC:
			temp_string = new QString( "Sun Microsistems SPARC" );
			break;
		case EM_386:
			temp_string = new QString( "Intel 386" );
			break;
		case EM_68K:
			temp_string = new QString( "Motorola 68K" );
			break;
		case EM_88K:
			temp_string = new QString( "Motorola 88K" );
			break;
		case EM_860:
			temp_string = new QString( "Intel 80860" );
			break;
		case EM_MIPS:
			temp_string = new QString( "MIPS RS3000 Big-Endian" );
			break;
		case EM_PARISC:
			temp_string = new QString( "HP / PA" );
			break;
		case EM_SPARC32PLUS:
			temp_string = new QString( "SPARC (Enhaced Instruction Set)" );
			break;
		case EM_PPC:
			temp_string = new QString( "PowerPC" );
			break;
		case EM_PPC64:
			temp_string = new QString( "PowerPC (64-Bit)" );
			break;
		case EM_S390:
			temp_string = new QString( "IBM S/390" );
			break;
		case EM_X86_64:
			temp_string = new QString( "AMD x86-64" );
			break;
		default:
			temp_string = new QString( "[Not Yet Inserted]" );
	}
	stringlist << *temp_string;

	// e_version
	temp_string = new QString();
	if( header->e_version==EV_CURRENT )
		temp_string = new QString( "Current Version" );
	else
		temp_string = new QString( "Invalid Version" );
	stringlist << *temp_string;

	// e_entry
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( header64->e_entry, 16 );
	else
		temp_string->setNum( header->e_entry, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// e_phoff
	temp_string = new QString();
	if( is64bit )
	{
		ph_off = header64->e_phoff;
		temp_string->setNum( header64->e_phoff, 16 );
	}
	else
	{
		ph_off = (uint64_t) header->e_phoff;
		temp_string->setNum( header->e_phoff, 16 );
	}
	stringlist << temp_string->toUpper().prepend( "0x" );

	// e_shoff
	temp_string = new QString();
	if( is64bit )
	{
		sh_off = header64->e_shoff;
		temp_string->setNum( header64->e_shoff, 16 );
	}
	else
	{
		sh_off = (uint64_t) header->e_shoff;
		temp_string->setNum( header->e_shoff, 16 );
	}
	stringlist << temp_string->toUpper().prepend( "0x" );

	// e_flags
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( header64->e_flags, 16 );
	else
		temp_string->setNum( header->e_flags, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// e_ehsize
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( header64->e_ehsize );
	else
		temp_string->setNum( header->e_ehsize );
	stringlist << *temp_string;

	// e_phentsize
	temp_string = new QString();
	if( is64bit )
	{
		ph_size = header64->e_phentsize;
		temp_string->setNum( header64->e_phentsize );
	}
	else
	{
		ph_size = header->e_phentsize;
		temp_string->setNum( header->e_phentsize );
	}
	stringlist << *temp_string;

	// e_phnum
	//TODO see man elf
	temp_string = new QString();
	if( is64bit )
	{
		ph_num = header64->e_phnum;
		temp_string->setNum( header64->e_phnum );
	}
	else
	{
		ph_num = header->e_phnum;
		temp_string->setNum( header->e_phnum );
	}
	stringlist << *temp_string;

	// e_shentsize
	temp_string = new QString();
	if( is64bit )
	{
		sh_size = header64->e_shentsize;
		temp_string->setNum( header64->e_shentsize );
	}
	else
	{
		sh_size = header->e_shentsize;
		temp_string->setNum( header->e_shentsize );
	}
	stringlist << *temp_string;

	// e_phnum
	//TODO see man elf
	temp_string = new QString();
	if( is64bit )
	{
		sh_num = header64->e_shnum;
		temp_string->setNum( header64->e_shnum );
	}
	else
	{
		sh_num = header->e_shnum;
		temp_string->setNum( header->e_shnum );
	}
	stringlist << *temp_string;

	// e_shstrndx
	//TODO see man elf
	temp_string = new QString();
	if( is64bit )
	{
		if( header64->e_shstrndx == SHN_UNDEF )
			*temp_string = "[No name string table]";
		else
			temp_string->setNum( header64->e_shstrndx );
	}
	else
	{
		if( header->e_shstrndx == SHN_UNDEF )
			*temp_string = "[No name string table]";
		else
			temp_string->setNum( header->e_shstrndx );
	}
	stringlist << *temp_string;

// ------  Inserting
	read = true;

	for( int i=0; i<stringlist.size(); i++ )
	{
		temp_item = new QTableWidgetItem( stringlist[i] );
		temp_item->setFlags( EHW_ITEMFLAGS );
		table->setItem( i, 0, temp_item );
	}
}

int ElfHeaderWidget::GetNumOfSections()
{
	return read?sh_num:-1;
}

int ElfHeaderWidget::GetNumOfProgHeaders()
{
	return read?ph_num:-1;
}

bool ElfHeaderWidget::IsELF64()
{
	// TODO check exeptions
	return is64bit;
}

uint64_t ElfHeaderWidget::GetProgHeaderOff( uint16_t i )
{
	if( !read || i>=ph_num )
		return -1;

	return ( ph_off + i*ph_size );
}

uint64_t ElfHeaderWidget::GetSectHeaderOff( uint16_t i )
{
	if( !read || i>=sh_num )
		return -1;

	return ( sh_off + i*sh_size );
}
