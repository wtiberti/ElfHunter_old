#include "ElfHeaderWidget.h"

ElfHeaderWidget::ElfHeaderWidget()
{
	QTableWidgetItem *tempitem;

	layout = new QVBoxLayout();
	table = new QTableWidget( TABLEROWS, TABLECOLUMNS, this );

	//table->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );

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

	delete table;
	delete layout;
}

void ElfHeaderWidget::GetValues( char *elfheader )
{
	//TODO QString Methods for parsing numbers
	//TODO QTableWidgetItems are deleted upon deletion of QTableWidget?
}
