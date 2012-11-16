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
	
	okteta_widget = new Okteta::ByteArrayColumnView();
	okteta_widget->setByteTypeColored( false );
	okteta_widget->setFont( QFont( "Monospace", 8 ) );
	//okteta_widget->setNoOfBytesPerLine( 0x10 );
	model = new Okteta::PieceTableByteArrayModel();
	model->setReadOnly( true );
	okteta_widget->setByteArrayModel( model );
	
	l->addWidget( (QWidget *)okteta_widget );
	
	setLayout( l );

	hexdata = NULL;
}

void ElfHunterHexWidget::ClearData()
{
	if( hexdata!=NULL )
	{
		delete hexdata;
		hexdata = NULL;
	}

}

ElfHunterHexWidget::~ElfHunterHexWidget()
{
	ClearData();

	delete model;
	delete okteta_widget;
	delete l;
}

void ElfHunterHexWidget::SetData( char *data, unsigned long datasize )
{
	ClearData();
	
	model->setData( QByteArray::fromRawData( data, datasize ) );
	
	hexdata = data;
	okteta_widget->setCursorPosition( 0 );
}

void ElfHunterHexWidget::Select( __uint64_t offset, __uint64_t size )
{
	Okteta::AddressRange ar( offset, (offset+size-1) );
	okteta_widget->setMarking( ar );
	okteta_widget->ensureVisible( ar, true );
}

void ElfHunterHexWidget::GoToOffset( __uint64_t offset )
{
	Okteta::AddressRange ar( offset, 1 );
	
	if( offset < (okteta_widget->byteArrayModel())->size() )
	{
		okteta_widget->setFocus( Qt::OtherFocusReason );
		okteta_widget->ensureVisible( ar, true );
		okteta_widget->setCursorPosition( offset );
	}
}