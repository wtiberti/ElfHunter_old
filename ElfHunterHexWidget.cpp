/*
* This file is part of ElfHunter software.
*
* ElfHunter is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ElfHunter is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ElfHunter.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright (C) 2012 Walter Tiberti
*/

/*
* Filename: ElfHunterHexWidget.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

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
			khe_hexvalues->setGroupSpacingWidth( 8 );
			//khe_hexvalues->setNoOfBytesPerLine( 16 );
		}

		khe_charvalues = KHE::charColumnInterface( khe_widget );

		if( khe_charvalues )
		{
			khe_charvalues->setShowUnprintable( false );
			khe_charvalues->setSubstituteChar( '.' );
		}
		
		/*
		KHE::ZoomInterface *khe_zoom = KHE::zoomInterface( khe_widget );
		
		if( khe_zoom )
		{
			khe_zoom->zoomTo( 10 );
		}*/

		/*
		// TODO 
		KHE::ClipboardInterface *clipboard = KHE::clipboardInterface( khe_widget );

		if( clipboard )
		{
			connect( khe_widget, SIGNAL(copyAvailable(bool)), this, SLOT(offerCopy(bool)) );
		}
		*/
	}

	//khe_widget->setFont( QFont( "Courier" ) );
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
	khe_interface->setData( data, datasize );
	khe_interface->setMaxDataSize( datasize );
	hexdata = data;
}