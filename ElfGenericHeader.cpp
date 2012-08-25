#include "ElfGenericHeader.h"
#include <elf.h>

ElfGenericHeader::ElfGenericHeader( int r, int c, bool h )
	: ElfHeaderWidget( r, c, h );
{
	//QTableWidgetItem *tempitem;

	//rows = r;
	//columns = c;

	//layout = new QVBoxLayout();
	spin = new QSpinBox();
	//table = new QTableWidget( rows, columns, this );

	//table->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

	//tableheaders = h;

	/*if( h )
	{
		AddHeader_H();
		AddHeader_V();
	}*/

	/*
	for( unsigned int j=0; j<columns; j++ )
		for( unsigned int i=0; i<rows; i++ )
		{
			tempitem = new QTableWidgetItem();
			tempitem->setFlags( (Qt::ItemFlag)37 );
			table->setItem( i, j, tempitem );
		}
	*/

	layout->addWidget( spin );
	//layout->addWidget( table );

	//setLayout( layout );
}

/*
void ElfGenericHeader::AddHeader_H()
{
	QTableWidgetItem *tempitem;

	for( unsigned int i=0; i<columns; i++ )
	{
		tempitem = new QTableWidgetItem( generic_horizontal_labels[i] );
		tempitem->setTextAlignment( Qt::AlignHCenter );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setHorizontalHeaderItem( i, tempitem );
	}
	table->horizontalHeader()->setResizeMode( QHeaderView::Stretch  );
}

void ElfGenericHeader::AddHeader_V()
{
	QTableWidgetItem *tempitem;

	for( unsigned int i=0; i<rows; i++ )
	{
		tempitem = new QTableWidgetItem( QString::number( i ) );
		tempitem->setFlags( Qt::NoItemFlags );
		table->setVerticalHeaderItem( i, tempitem );
	}
	table->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
}
*/

ElfGenericHeader::~ElfGenericHeader()
{
	/*
	for( unsigned int i=0; i<columns; i++ )
		for( unsigned int j=0; j<rows; j++ )
			delete table->item( j, i );

	if( tableheaders )
	{
	for( unsigned int i=0; i<rows; i++ )
			delete table->horizontalHeaderItem( i );

		for( unsigned int i=0; i<rows; i++ )
			delete table->verticalHeaderItem( i );
	}

	stringlist.clear();
	*/
	//valueslist.clear();

	delete spin;
	//delete table;
	//delete layout;
}

void ElfGenericHeader::Changed()
{
	SetValues( spin->value() );
}

/*
int ElfGenericHeader::AddRow()
{
	table->setRowCount( table->rowCount()+1 );
	rows = table->rowCount();
	return rows;
}

int ElfGenericHeader::AddCol()
{
	table->setColumnCount( table->columnCount()+1 );
	columns = table->columnCount();
	return columns;
}

void ElfGenericHeader::ClearRows()
{
	for( unsigned int i=0; i<columns; i++ )
		for( unsigned int j=0; j<rows; j++ )
			delete table->item( j, i );

	table->setRowCount( 0 );
	rows = 0;
}*/