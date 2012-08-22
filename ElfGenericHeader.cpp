#include "ElfGenericHeader.h"
#include <elf.h>

ElfGenericHeader::ElfGenericHeader( int r, int c )
{
	QTableWidgetItem *tempitem;

	rows = r;
	columns = c;

	layout = new QVBoxLayout();
	spin = new QSpinBox();
	table = new QTableWidget( rows, columns, this );

	table->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

	for( unsigned int i=0; i<columns; i++ )
	{
		tempitem = new QTableWidgetItem( "Value" );
		tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setHorizontalHeaderItem( i, tempitem );
	}

	for( unsigned int i=0; i<rows; i++ )
	{
		tempitem = new QTableWidgetItem( QString( i ) );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setVerticalHeaderItem( i, tempitem );
	}

	table->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
	table->horizontalHeader()->setResizeMode( QHeaderView::Stretch  );

	for( unsigned int i=0; i<rows; i++ )
	{
		tempitem = new QTableWidgetItem();
		tempitem->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 0, tempitem );
	}

	layout->addWidget( spin );
	layout->addWidget( table );

	setLayout( layout );
}

ElfGenericHeader::~ElfGenericHeader()
{
	for( unsigned int i=0; i<columns; i++ )
		for( unsigned int j=0; j<rows; j++ )
			delete table->item( j, i );

	for( unsigned int i=0; i<rows; i++ )
		delete table->horizontalHeaderItem( i );

	for( unsigned int i=0; i<rows; i++ )
		delete table->verticalHeaderItem( i );

	stringlist.clear();

	delete spin;
	delete table;
	delete layout;
}

void ElfGenericHeader::Changed()
{
	SetValues( spin->value() );
}