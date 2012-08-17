#include "ElfHeaderWidget.h"

#include <elf.h>
#include <cstdio>
#include <cstring>

ElfHeaderWidget::ElfHeaderWidget()
{
	QTableWidgetItem *tempitem;

	layout = new QVBoxLayout();
	table = new QTableWidget( TABLEROWS, TABLECOLUMNS, this );
	table->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );


	for( int i=0; i<TABLECOLUMNS; i++ )
	{
		// Horizontal table headers
		tempitem = new QTableWidgetItem( "Value" );
		tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setHorizontalHeaderItem( i, tempitem );
	}

	for( int i=0; i<TABLEROWS; i++ )
	{
		tempitem = new QTableWidgetItem( field_names[i] );
		//tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setVerticalHeaderItem( i, tempitem );
	}

	table->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
	table->horizontalHeader()->setResizeMode( QHeaderView::Stretch  );

	layout->addWidget( table );

	setLayout( layout );
}

ElfHeaderWidget::~ElfHeaderWidget()
{
	for( int i=0; i<TABLECOLUMNS; i++ )
	{
		for( int j=0; j<TABLEROWS; j++ )
		{
			delete table->item( j, i );
		}
	}

	for( int i=0; i<TABLECOLUMNS; i++ )
		delete table->horizontalHeaderItem( i );

	for( int i=0; i<TABLEROWS; i++ )
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
	//Makes item being enabled, selectable and drag-able
	#define EHW_ITEMFLAGS (Qt::ItemFlag)37

	QTableWidgetItem *temp_item;
	QString *temp_string;
	Elf32_Ehdr *header = (Elf32_Ehdr *)elfheader;


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
			temp_string = new QString( "Unix System V ABI" );
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




	for( int i=0; i<stringlist.size(); i++ )
	{
		temp_item = new QTableWidgetItem( stringlist[i] );
		temp_item->setFlags( EHW_ITEMFLAGS );
		table->setItem( i, 0, temp_item );
	}
}

QString *ElfHeaderWidget::ToHexString( unsigned char *stream, unsigned int size )
{
	// well, each byte to parse is in the form 0xXX<space>
	// so we need 5 chars per byte plus a zero ending byte
	char *buffer = new char[5*size+1];
	char temp_buffer[10];
	QString *result;

	memset( buffer, 0, sizeof(char)*(5*size+1) );

	for( int i=0; i<size; i++ )
	{
		memset( temp_buffer, 0, sizeof(char)*10 );
		snprintf( temp_buffer, 6, "0x%.2X ", stream[i] );
		strncat( buffer, temp_buffer, 6 );
	}

	result = new QString( buffer );
	*result = result->trimmed();

	delete buffer;

	return result;
}
