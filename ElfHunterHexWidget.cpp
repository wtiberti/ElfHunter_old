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
	//
	model = new Okteta::PieceTableByteArrayModel();
	okteta_widget->setByteArrayModel( model );
	//
	
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

	delete okteta_widget;
	delete l;
}

void ElfHunterHexWidget::SetData( char *data, unsigned long datasize )
{
	ClearData();
	
	//NOTE SEGFAULT HERE!
	model->setData( QByteArray::fromRawData( data, datasize ) );
	
	hexdata = data;
}