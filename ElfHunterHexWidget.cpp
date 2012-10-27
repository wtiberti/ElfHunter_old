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
	
	model = NULL;
	
	okteta_widget = new Okteta::ByteArrayColumnView();
	l->addWidget( (QWidget *)okteta_widget );
	
	/*khe_widget = KHE::createBytesEditWidget( parent );

	if( khe_widget )
	{
		khe_interface = KHE::bytesEditInterface( khe_widget );
		Q_ASSERT( khe_interface );

		khe_interface->setReadOnly( true );
		->setAutoDelete( true );

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
	}
	
	l->addWidget( khe_widget );
	
	*/
	
	setLayout( l );

	hexdata = NULL;
}

void ElfHunterHexWidget::ClearData()
{
	//okteta_widget->
	
	if( model != NULL )
	{
		delete model;
		model = NULL;
	}
	
	// Data is deleted upon destruction, so we do only "burocracy"
	// setting hexdata to NULL, avoiding double-free exception
	if( hexdata!=NULL )
	{
		delete hexdata;
		hexdata = NULL;
	}

	//khe_interface->setData( hexdata, 0 );
	//khe_interface->setMaxDataSize( 0 );
}

ElfHunterHexWidget::~ElfHunterHexWidget()
{
	ClearData();

	//delete khe_widget;
	delete okteta_widget;
	delete l;
}

void ElfHunterHexWidget::SetData( char *data, unsigned long datasize )
{
	//khe_interface->setData( data, datasize );
	//khe_interface->setMaxDataSize( datasize );
	
	ClearData();
	model = new Okteta::PieceTableByteArrayModel( QByteArray::fromRawData( data, datasize ), this );
	okteta_widget->setByteArrayModel( model );
	hexdata = data;
}