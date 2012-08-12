#include "ElfHunterHexWidget.h"

ElfHunterHexWidget::ElfHunterHexWidget( QWidget *parent )
{
	l = new QGridLayout();

	khe_widget = KHE::createBytesEditWidget( parent );

	if( khe_widget )
	{
		khe_interface = KHE::bytesEditInterface( khe_widget );
		Q_ASSERT( khe_interface );

		khe_interface->setReadOnly( true );
		khe_interface->setAutoDelete( true );

		khe_hexvalues = KHE::valueColumnInterface( khe_widget );

		if( khe_hexvalues )
		{
			khe_hexvalues->setCoding( KHE::ValueColumnInterface::HexadecimalCoding );
			khe_hexvalues->setByteSpacingWidth( 4 );
			khe_hexvalues->setNoOfGroupedBytes( 4 );
			khe_hexvalues->setGroupSpacingWidth( 8 );;
		}

		khe_charvalues = KHE::charColumnInterface( khe_widget );

		if( khe_charvalues )
		{
			khe_charvalues->setShowUnprintable( false );
			khe_charvalues->setSubstituteChar( '.' );
		}

		/*
		KHE::ClipboardInterface *clipboard = KHE::clipboardInterface( khe_widget );

		if( clipboard )
		{
			connect( khe_widget, SIGNAL(copyAvailable(bool)), this, SLOT(offerCopy(bool)) );
		}*/
	}

	l->addWidget( khe_widget );

	setLayout( l );

	hexdata = NULL;
}

void ElfHunterHexWidget::ClearData()
{
	// Data is deleted upon destruction, so we do only "burocracy"
	// setting hexdata to NULL, avoiding double-free exception
	hexdata = NULL;

	khe_interface->setData( hexdata, 0 );
	khe_interface->setMaxDataSize( 0 );

}

ElfHunterHexWidget::~ElfHunterHexWidget()
{
	ClearData();

	delete l;
	delete khe_widget;
}

void ElfHunterHexWidget::SetData( char *data, unsigned long datasize )
{
	//if( hexdata!=NULL )
		//delete hexdata;

	khe_interface->setData( data, datasize );
	khe_interface->setMaxDataSize( datasize );
	hexdata = data;
}