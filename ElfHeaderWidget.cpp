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
	temp_string = ToHexString( elfheader, 4 );
	stringlist << *temp_string;


	for( int i=0; i<stringlist.size(); i++ )
	{
		temp_item = new QTableWidgetItem( stringlist[i] );
		temp_item->setFlags( EHW_ITEMFLAGS );
		table->setItem( i, 0, temp_item );
	}
}

QString *ElfHeaderWidget::ToHexString( char *stream, unsigned int size )
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
		snprintf( temp_buffer, 6, "0x%.2X ", (unsigned char)stream[i] );
		strncat( buffer, temp_buffer, 6 );
	}

	result = new QString( buffer );
	//result->trimmed();

	delete buffer;

	return result;
}
