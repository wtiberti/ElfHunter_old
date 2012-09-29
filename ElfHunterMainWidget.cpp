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
* Filename: ElfHunterMainWidget.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfHunterMainWidget.h"

#ifndef ELFHUNTER_STANDALONE
#include <vector>
extern std::vector< QAction * > menuactions;
extern std::vector< QAction * > tbactions;
#endif

ElfHunterMainWidget::ElfHunterMainWidget( QWidget *parent ) : QWidget(parent)
{
	hexvisible = false;
	user_can_show_hex = false;

	layout = new QGridLayout();
	sidewidget = new ElfHunterSideWidget( this );
	hexdump = new ElfHunterHexWidget( this );

	hexdump->setVisible( false );

	layout->addWidget( sidewidget, 0, 0 );
	layout->addWidget( hexdump, 0, 1 );

	file_opened = false;
	actual_file = NULL;

	setLayout( layout );
}

ElfHunterMainWidget::~ElfHunterMainWidget()
{
	if( file_opened )
	{
		actual_file->close();
		file_opened = false;
		delete actual_file;
	}

	delete hexdump;
	delete sidewidget;
	delete layout;
}

bool ElfHunterMainWidget::IsFileActive()
{
	return file_opened;
}

unsigned long ElfHunterMainWidget::OpenFile()
{
	QString filename;

	filename = QFileDialog::getOpenFileName( this, "Open", "", "" );

	if( filename != "" )
	{
		if( !QFile::exists( filename ) )
		{
			QMessageBox msg( QMessageBox::Critical, "Error", "The file doesn't exist" );
			msg.exec();
			throw 1;
		}
	}

	if( file_opened )
		CloseFile();

	actual_file = new QFile( filename );
	actual_file->open( QIODevice::ReadOnly );

	if( actual_file->error() != QFile::NoError )
	{
		QMessageBox msg( QMessageBox::Critical, "Error", "Error while opening the file" );
		msg.exec();
		throw 2;
	};

	file_opened = true;

	#ifndef ELFHUNTER_STANDALONE
	menuactions[0]->setEnabled( false );
	menuactions[1]->setEnabled( true );
	tbactions[0]->setEnabled( false );
	tbactions[1]->setEnabled( true );
	#endif

	return actual_file->size();
}

unsigned long ElfHunterMainWidget::ReadFile()
{
	char *filedata;
	unsigned long dataread;

	uint32_t signature = 0;

	if( !file_opened )
		throw 1;

	hexdump->show();
	hexvisible = true;
	//

	filedata = new char[ actual_file->size() ];
	dataread = actual_file->read( filedata, actual_file->size() );

	signature = * ( int * )filedata;

	if( signature != 0x464C457F )
	{
		delete filedata;
		throw 2;
	}

	ElfELFHeaderWidget *temp_elfhdr = new ElfELFHeaderWidget();
	sidewidget->addTab( (QWidget *)temp_elfhdr, "ELF Header" );
	tabselem.push_back( (QWidget *)temp_elfhdr );
	temp_elfhdr->SetElfValues( filedata );

	if( ElfGenericHeader::HasSegments( filedata ) )
	{
		ElfProgHeaderWidget *temp_proghdr = new ElfProgHeaderWidget();
		temp_proghdr->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_proghdr, "Program Headers" );
		tabselem.push_back( (QWidget *)temp_proghdr );
	}

	if( ElfGenericHeader::HasSections( filedata ) )
	{
		ElfSectionHeaderWidget *temp_secthdr = new ElfSectionHeaderWidget();
		temp_secthdr->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_secthdr, "Section Headers" );
		tabselem.push_back( (QWidget *)temp_secthdr );

		ElfStringTable *temp_strtbl = new ElfStringTable();
		temp_strtbl->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_strtbl, "String Tables" );
		tabselem.push_back( (QWidget *)temp_strtbl );

		ElfSymTable *temp_symtbl = new ElfSymTable();
		temp_symtbl->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_symtbl, "Symbol Tables" );
		tabselem.push_back( (QWidget *)temp_symtbl );
	}

	hexdump->SetData( filedata, dataread );
	user_can_show_hex = true;

	return dataread;
}

void ElfHunterMainWidget::CloseFile()
{
	for( unsigned int i=0; i<tabselem.size(); i++ )
		delete tabselem[ i ];

	tabselem.clear();

	if( file_opened )
	{
		actual_file->close();
		file_opened = false;
		delete actual_file;
	}

	#ifndef ELFHUNTER_STANDALONE
	menuactions[0]->setEnabled( true );
	menuactions[1]->setEnabled( false );
	tbactions[0]->setEnabled( true );
	tbactions[1]->setEnabled( false );
	#endif

	hexdump->ClearData();


	hexdump->hide();
	hexvisible = false;
	user_can_show_hex = false;
}

void ElfHunterMainWidget::SetFile()
{
	try
	{
		OpenFile();
	}
	catch( int ErrorNum )
	{
		if( ErrorNum==2 )
			CloseFile();
		return;
	}

	try
	{
		ReadFile();
	}
	catch( int ErrorNum )
	{
		CloseFile();

		QMessageBox msg( QMessageBox::Critical, "Error", "" );

		switch( ErrorNum )
		{
			case 1:
				msg.setText( "Error: no file opened. Code 1" );
				break;

			case 2:
				msg.setText( "Error: no valid ELF file. Code 2" );
				break;
		}

		msg.exec();
	}
}

void ElfHunterMainWidget::DisplayAbout()
{
	AboutWidget about;
	about.exec();
}

void ElfHunterMainWidget::ToggleHexView()
{
	if( user_can_show_hex )
	{
		if( hexvisible )
		{
			hexdump->hide();
			hexvisible = false;
		}
		else
		{
			hexdump->show();
			hexvisible = true;
		}
	}
}