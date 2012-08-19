#include "ElfProgHeaderWidget.h"
#include <elf.h>

ElfProgHeaderWidget::ElfProgHeaderWidget()
{
	QTableWidgetItem *tempitem;

	layout = new QVBoxLayout();
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

	delete table;
	delete layout;
}

void ElfProgHeaderWidget::GetValues( char *progheader )
{}
