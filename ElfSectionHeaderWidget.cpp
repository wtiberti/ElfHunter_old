#include "ElfSectionHeaderWidget.h"
#include <elf.h>


ElfSectionHeaderWidget::ElfSectionHeaderWidget()
{
	QTableWidgetItem *tempitem;

	layout = new QVBoxLayout();

	spin = new QSpinBox();
	spin->setMinimum( 0 );
	spin->setPrefix( "Section Header # " );

	table = new QTableWidget( SECTHDRTABLEROWS, SECTHDRTABLECOLUMNS, this );
	table->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

	for( int i=0; i<SECTHDRTABLECOLUMNS; i++ )
	{
		// Horizontal table headers
		tempitem = new QTableWidgetItem( "Value" );
		tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setHorizontalHeaderItem( i, tempitem );
	}

	for( int i=0; i<SECTHDRTABLEROWS; i++ )
	{
		tempitem = new QTableWidgetItem( secthdr_field_names[i] );
		//tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setVerticalHeaderItem( i, tempitem );
	}

	table->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
	table->horizontalHeader()->setResizeMode( QHeaderView::Stretch  );

	for( int i=0; i<SECTHDRTABLEROWS; i++ )
	{
		tempitem = new QTableWidgetItem();
		tempitem->setFlags( EHW_ITEMFLAGS );
		table->setItem( i, 0, tempitem );
	}

	layout->addWidget( spin );
	layout->addWidget( table );

	setLayout( layout );
}

ElfSectionHeaderWidget::~ElfSectionHeaderWidget()
{
	for( int i=0; i<SECTHDRTABLECOLUMNS; i++ )
	{
		for( int j=0; j<SECTHDRTABLEROWS; j++ )
		{
			delete table->item( j, i );
		}
	}

	for( int i=0; i<SECTHDRTABLECOLUMNS; i++ )
		delete table->horizontalHeaderItem( i );

	for( int i=0; i<SECTHDRTABLEROWS; i++ )
		delete table->verticalHeaderItem( i );

	stringlist.clear();

	delete spin;
	delete table;
	delete layout;
}

void ElfSectionHeaderWidget::SetValues( int index )
{
	QString *temp_string;
	Elf64_Shdr *sect64 = (Elf64_Shdr *)base;
	Elf32_Shdr *sect = (Elf32_Shdr *)base;

	sect += index;
	sect64 += index;

	stringlist.clear();

	temp_string = new QString();
	temp_string->setNum( shoff+index*entry_size, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// sh_name
	//TODO stringa
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_name, 16 );
	else
		temp_string->setNum( sect->sh_name, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );


	//sh_type
	__uint64_t secttype;
	if( is64bit )
		secttype = sect64->sh_type;
	else
		secttype = sect->sh_type;
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
			if( sect->sh_type>=SHT_LOPROC && sect->sh_type<=SHT_HIPROC )
				temp_string = new QString( "Processor-specific" );
			else
				temp_string = new QString( "[Invalid]" );
	}
	stringlist << *temp_string;

	// sh_flags
	temp_string = new QString("");
	__uint64_t sectflags;
	if( is64bit )
		sectflags = sect64->sh_flags;
	else
		sectflags = sect->sh_flags;
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
	stringlist << temp_string->toUpper().prepend( "0x" );

	// sh_offset
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_offset, 16 );
	else
		temp_string->setNum( sect->sh_offset, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// sh_size
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_size, 10 );
	else
		temp_string->setNum( sect->sh_size, 10 );
	stringlist << *temp_string;

	// sh_link
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_link, 16 );
	else
		temp_string->setNum( sect->sh_link, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// sh_info
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_info, 16 );
	else
		temp_string->setNum( sect->sh_info, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// sh_addralign
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_addralign, 16 );
	else
		temp_string->setNum( sect->sh_addralign, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// sh_entsize
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( sect64->sh_entsize, 16 );
	else
		temp_string->setNum( sect->sh_entsize, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	for( int i=0; i<SECTHDRTABLEROWS; i++ )
	{
		table->item( i, 0 )->setText( stringlist[i] );
	}
}

void ElfSectionHeaderWidget::Changed()
{
	SetValues( spin->value() );
}

void ElfSectionHeaderWidget::SelectData( char *elffile )
{
	Elf32_Ehdr *header = (Elf32_Ehdr *)elffile;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)elffile;

	base = (unsigned char *) elffile;

	is64bit = header->e_ident[EI_CLASS]==ELFCLASS64?true:false;

	if( is64bit )
	{
		shoff = header64->e_shoff;
		base += shoff;
		entry_size = header64->e_shentsize;

		if( header64->e_shnum==0 )
			return;

		spin->setMaximum( header64->e_shnum-1 );
	}
	else
	{
		shoff = header->e_shoff;
		base += shoff;
		entry_size = header->e_shentsize;

		if( header->e_shnum==0 )
			return;

		spin->setMaximum( header->e_shnum-1 );
	}

	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );

	SetValues( 0 );
}
