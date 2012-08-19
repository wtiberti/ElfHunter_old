#include "ElfProgHeaderWidget.h"
#include <elf.h>

ElfProgHeaderWidget::ElfProgHeaderWidget()
{
	QTableWidgetItem *tempitem;

	layout = new QVBoxLayout();

	spin = new QSpinBox();
	spin->setMinimum( 0 );
	spin->setPrefix( "Program Header # " );

	table = new QTableWidget( PROGHDRTABLEROWS, PROGHDRTABLECOLUMNS, this );
	table->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

	for( int i=0; i<PROGHDRTABLECOLUMNS; i++ )
	{
		// Horizontal table headers
		tempitem = new QTableWidgetItem( "Value" );
		tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setHorizontalHeaderItem( i, tempitem );
	}

	for( int i=0; i<PROGHDRTABLEROWS; i++ )
	{
		tempitem = new QTableWidgetItem( proghdr_field_names[i] );
		//tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setVerticalHeaderItem( i, tempitem );
	}

	table->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
	table->horizontalHeader()->setResizeMode( QHeaderView::Stretch  );

	for( int i=0; i<PROGHDRTABLEROWS; i++ )
	{
		tempitem = new QTableWidgetItem();
		tempitem->setFlags( EHW_ITEMFLAGS );
		table->setItem( i, 0, tempitem );
	}

	layout->addWidget( spin );
	layout->addWidget( table );

	setLayout( layout );
}

ElfProgHeaderWidget::~ElfProgHeaderWidget()
{
	for( int i=0; i<PROGHDRTABLECOLUMNS; i++ )
	{
		for( int j=0; j<PROGHDRTABLEROWS; j++ )
		{
			delete table->item( j, i );
		}
	}

	for( int i=0; i<PROGHDRTABLECOLUMNS; i++ )
		delete table->horizontalHeaderItem( i );

	for( int i=0; i<PROGHDRTABLEROWS; i++ )
		delete table->verticalHeaderItem( i );

	stringlist.clear();

	delete spin;
	delete table;
	delete layout;
}

void ElfProgHeaderWidget::SetValues( int index )
{
	QString *temp_string;
	Elf64_Phdr *prog64 = (Elf64_Phdr *)base;
	Elf32_Phdr *prog = (Elf32_Phdr *)base;

	prog += index;
	prog64 += index;

	stringlist.clear();

	// p_type
	__uint64_t prgtype;
	if( is64bit )
		prgtype = prog64->p_type;
	else
		prgtype = prog->p_type
		;
	switch( prgtype )
	{
		case PT_NULL:
			temp_string = new QString( "Unused / Ignored" );
			break;
		case PT_LOAD:
			temp_string = new QString( "Loadable Segment" );
			break;
		case PT_DYNAMIC:
			temp_string = new QString( "Dynamic Linking Information" );
			break;
		case PT_INTERP:
			temp_string = new QString( "Path to Interpreter" );
			break;
		case PT_NOTE:
			temp_string = new QString( "Auxiliary Information" );
			break;
		case PT_SHLIB:
			temp_string = new QString( "Reserved / non-ABI" );
			break;
		case PT_PHDR:
			temp_string = new QString( "Program Header Info" );
			break;
		case PT_LOPROC:
			temp_string = new QString( "Lower Limit" );
			break;
		case PT_HIPROC:
			temp_string = new QString( "Higher Limit" );
			break;
		default:
			temp_string = new QString( "[Invalid]" );
	}
	stringlist << *temp_string;

	// Data offset
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( prog64->p_offset, 16 );
	else
		temp_string->setNum( prog->p_offset, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// Virtual Address
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( prog64->p_vaddr, 16 );
	else
		temp_string->setNum( prog->p_vaddr, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// Physical Address
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( prog64->p_paddr, 16 );
	else
		temp_string->setNum( prog->p_paddr, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// p_filesz
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( prog64->p_filesz, 16 );
	else
		temp_string->setNum( prog->p_filesz, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// p_memsz
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( prog64->p_memsz, 16 );
	else
		temp_string->setNum( prog->p_memsz, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	// flags
	temp_string = new QString("");
	__uint64_t prgflags;
	if( is64bit )
		prgflags = prog64->p_flags;
	else
		prgflags = prog->p_flags;

	if( prgflags & PF_R )
		temp_string->push_back( "Readable " );
	if( prgflags & PF_W )
		temp_string->push_back( "Writeable " );
	if( prgflags & PF_X )
		temp_string->push_back( "Executable ");

	stringlist << temp_string->trimmed();

	// p_align
	temp_string = new QString();
	if( is64bit )
		temp_string->setNum( prog64->p_align, 16 );
	else
		temp_string->setNum( prog->p_align, 16 );
	stringlist << temp_string->toUpper().prepend( "0x" );

	//qDebug() << stringlist;

	if( is64bit )
		stringlist.move( 6, 1 );

	for( int i=0; i<PROGHDRTABLEROWS; i++ )
	{
		table->item( i, 0 )->setText( stringlist[i] );
	}
}

void ElfProgHeaderWidget::Changed()
{
	SetValues( spin->value() );
}

void ElfProgHeaderWidget::SelectData( char *elffile )
{
	Elf32_Ehdr *header = (Elf32_Ehdr *)elffile;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)elffile;

	base = (unsigned char *) elffile;

	is64bit = header->e_ident[EI_CLASS]==ELFCLASS64?true:false;

	if( is64bit )
	{
		phoff = header64->e_phoff;
		base += phoff;
		entry_size = header64->e_phentsize;

		if( header64->e_phnum==0 )
			return;

		spin->setMaximum( header64->e_phnum-1 );
	}
	else
	{
		phoff = header->e_phoff;
		base += phoff;
		entry_size = header->e_phentsize;

		if( header->e_phnum==0 )
			return;

		spin->setMaximum( header->e_phnum-1 );
	}

	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );

	if( is64bit )
	{
		for( int i=0; i<PROGHDRTABLEROWS; i++ )
			table->verticalHeaderItem( i )->setText( proghdr_field_names64[i] );
	}

	SetValues( 0 );
}
