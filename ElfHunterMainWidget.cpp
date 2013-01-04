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
//#include "ElfHunterMainWidget.h"
#include "ElfHunterWindow.h"

extern QString cmdline_file2open;

ElfHunterMainWidget::ElfHunterMainWidget( QWidget *parent ) : QWidget(parent)
{
	treewidgetvisible = false;
	hexvisible = false;
	user_can_show_hex = false;
	
	connect( this, SIGNAL(s_filechanged(QString,__uint64_t)), parent, SLOT(SetFileDesc(QString,__uint64_t)) );

	layout = new QGridLayout();
	widget_selector = new QTreeWidget( this );
	sidewidget = new ElfHunterSideWidget( this );
	hexdump = new ElfHunterHexWidget( this );
	
	connect ( hexdump, SIGNAL(s_hexcursorchanged(__uint64_t)), parent, SLOT(SetCurrentOffset(__uint64_t)) );
	
	widget_selector->setHeaderLabel( "ELF structure" );
	
	connect( widget_selector, SIGNAL(itemClicked(QTreeWidgetItem*,int)), sidewidget, SLOT(setwidget(QTreeWidgetItem*,int)) );
	connect( widget_selector, SIGNAL(itemActivated(QTreeWidgetItem*,int)), sidewidget, SLOT(setwidget(QTreeWidgetItem*,int)) );
	
	widget_selector->setVisible( false );
	hexdump->setVisible( false );

	spl = new QSplitter( this );
	v_spl = new QSplitter( this );
	
	v_spl->setOrientation( Qt::Vertical );
	
	spl->addWidget( widget_selector );
	spl->addWidget( sidewidget );
	QList<int> widgets_size_list;
	widgets_size_list.append( 180 ); //TODO: HEDUMPSIZE
	widgets_size_list.append( 450 ); //TODO: HEDUMPSIZE
	spl->setSizes( widgets_size_list );
	
	v_spl->addWidget( spl );
	v_spl->addWidget( hexdump );
	
	layout->addWidget( v_spl );

	file_opened = false;
	actual_file = NULL;

	setLayout( layout );
	
	if( cmdline_file2open!="" )
	{
		SetFile( true );
	}
}

ElfHunterMainWidget::~ElfHunterMainWidget()
{
	disconnect( this, 0, 0, 0 );
	
	if( file_opened )
	{
		actual_file->close();
		file_opened = false;
		delete actual_file;
	}
	
	delete sidewidget;
	delete widget_selector;
	delete spl;
	delete v_spl;
	delete hexdump;
	delete layout;
}

bool ElfHunterMainWidget::IsFileActive()
{
	return file_opened;
}

QString ElfHunterMainWidget::OpenFile_Dialog()
{
	QString filename;
	
	filename = QFileDialog::getOpenFileName( this, "Open", "", "" );
	return filename;
}

unsigned long ElfHunterMainWidget::OpenFile( QString &filename )
{
	if( file_opened )
		CloseFile();

	if( filename != "" )
	{
		if( !QFile::exists( filename ) )
		{
			QMessageBox msg( QMessageBox::Critical, "Error", "The file doesn't exist" );
			msg.exec();
			throw ERR_OPEN_FILE_NOT_EXISTS;
		}
	}

	actual_file = new QFile( filename );
	actual_file->open( QIODevice::ReadOnly );
	
	if( actual_file->error() != QFile::NoError )
	{
		QMessageBox msg( QMessageBox::Critical, "Error", "Error while opening the file" );
		msg.exec();
		throw ERR_OPEN_FILE_OPEN_ERROR;
	};

	file_opened = true;
	
	return actual_file->size();
}

unsigned long ElfHunterMainWidget::ReadFile()
{
	char *filedata;
	unsigned long dataread;

	uint32_t signature = 0;
	
	if( !file_opened )
		throw ERR_READ_FILE_NOT_OPEN;

	filedata = new char[ actual_file->size() ];
	dataread = actual_file->read( filedata, actual_file->size() );

	signature = * ( int * )filedata;

	if( signature != ELFSIGNATURE )
	{
		delete filedata;
		throw ERR_READ_INVALID_SIG;
	}
	
	Populate( filedata, dataread );
	
	return dataread;
}

void ElfHunterMainWidget::Populate( char *filedata, unsigned long size )
{
	ElfELFHeaderWidget *temp_elfhdr;
	ElfProgHeaderWidget *temp_proghdr;
	ElfSectionHeaderWidget *temp_secthdr;
	
	QTreeWidgetItem *elfhdr_treeitem;
	QTreeWidgetItem *proghdr_treeitem;
	QTreeWidgetItem *secthdr_treeitem;
	QTreeWidgetItem *temp_treeitem;
	
	widget_selector->show();
	treewidgetvisible = true;
	
	hexdump->show();
	hexvisible = true;
	
	temp_elfhdr = new ElfELFHeaderWidget();
	sidewidget->addTab( (QWidget *)temp_elfhdr, "ELF Header" );
	temp_elfhdr->SetElfValues( filedata );
	elfhdr_treeitem = new QTreeWidgetItem( widget_selector );
	elfhdr_treeitem->setText( 0, "ELF Header" );
	widget_selector->addTopLevelItem( elfhdr_treeitem );
	tree_elem.push_back( elfhdr_treeitem );
	
	connect( temp_elfhdr, SIGNAL( S_selection_changed(__uint64_t,__uint64_t) ), hexdump, SLOT( Select(__uint64_t,__uint64_t) ) );
	
	//
	sidewidget->setwidget( elfhdr_treeitem, 0 );
	//

	if( ElfGenericHeader::HasSegments( filedata ) )
	{
		temp_proghdr = new ElfProgHeaderWidget();
		temp_proghdr->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_proghdr, "Program Headers" );
		proghdr_treeitem = new QTreeWidgetItem();
		proghdr_treeitem->setText( 0, "Program Headers" );
		elfhdr_treeitem->addChild( proghdr_treeitem );
		tree_elem.push_back( proghdr_treeitem );
		connect( temp_proghdr, SIGNAL( S_selection_changed(__uint64_t,__uint64_t) ), hexdump, SLOT( Select(__uint64_t,__uint64_t) ) );
	}

	if( ElfGenericHeader::HasSections( filedata ) )
	{
		temp_secthdr = new ElfSectionHeaderWidget();
		temp_secthdr->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_secthdr, "Section Headers" );
		secthdr_treeitem = new QTreeWidgetItem();
		secthdr_treeitem->setText( 0, "Section Headers" );
		elfhdr_treeitem->addChild( secthdr_treeitem );
		tree_elem.push_back( secthdr_treeitem );
		connect( temp_secthdr, SIGNAL( S_selection_changed(__uint64_t,__uint64_t) ), hexdump, SLOT( Select(__uint64_t,__uint64_t) ) );

		ElfStringTable *temp_strtbl = new ElfStringTable();
		temp_strtbl->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_strtbl, "String Tables" );
		temp_treeitem = new QTreeWidgetItem();
		temp_treeitem->setText( 0, "String Tables" );
		secthdr_treeitem->addChild( temp_treeitem );
		tree_elem.push_back( temp_treeitem );
		connect( temp_strtbl, SIGNAL( S_selection_changed(__uint64_t,__uint64_t) ), hexdump, SLOT( Select(__uint64_t,__uint64_t) ) );
		
		ElfSymTable *temp_symtbl = new ElfSymTable();
		temp_symtbl->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_symtbl, "Symbol Tables" );
		temp_treeitem = new QTreeWidgetItem();
		temp_treeitem->setText( 0, "Symbol Tables" );
		secthdr_treeitem->addChild( temp_treeitem );
		tree_elem.push_back( temp_treeitem );
		connect( temp_symtbl, SIGNAL( S_selection_changed(__uint64_t,__uint64_t) ), hexdump, SLOT( Select(__uint64_t,__uint64_t) ) );
	
		ElfHunterRelTable *temp_rlctbl = new ElfHunterRelTable();
		temp_rlctbl->SelectData( filedata );
		sidewidget->addTab( (QWidget *)temp_rlctbl, "Reloc Tables" );
		temp_treeitem = new QTreeWidgetItem();
		temp_treeitem->setText( 0, "Reloc Tables" );
		secthdr_treeitem->addChild( temp_treeitem );
		tree_elem.push_back( temp_treeitem );
		connect( temp_rlctbl, SIGNAL( S_selection_changed(__uint64_t,__uint64_t) ), hexdump, SLOT( Select(__uint64_t,__uint64_t) ) );
	}
	
	ElfHunterExec *temp_ehexec1 = new ElfHunterExec( "objdump", long_file_name );
	sidewidget->addTab( (QWidget *)temp_ehexec1, temp_ehexec1->GetCommand().prepend("Exec: ") );
	temp_treeitem = new QTreeWidgetItem();
	temp_treeitem->setText( 0, temp_ehexec1->GetCommand().prepend("Exec: ") );
	widget_selector->addTopLevelItem( temp_treeitem );
	tree_elem.push_back( temp_treeitem );
	
	ElfHunterExec *temp_ehexec2 = new ElfHunterExec( "readelf", long_file_name );
	sidewidget->addTab( (QWidget *)temp_ehexec2, temp_ehexec2->GetCommand().prepend("Exec: ") );
	temp_treeitem = new QTreeWidgetItem();
	temp_treeitem->setText( 0, temp_ehexec2->GetCommand().prepend("Exec: ") );
	widget_selector->addTopLevelItem( temp_treeitem );
	tree_elem.push_back( temp_treeitem );

	ElfHunterExec *temp_ehexec3 = new ElfHunterExec( "hexdump", long_file_name );
	sidewidget->addTab( (QWidget *)temp_ehexec3, temp_ehexec3->GetCommand().prepend("Exec: ") );
	temp_treeitem = new QTreeWidgetItem();
	temp_treeitem->setText( 0, temp_ehexec3->GetCommand().prepend("Exec: ") );
	widget_selector->addTopLevelItem( temp_treeitem );
	tree_elem.push_back( temp_treeitem );

	hexdump->SetData( filedata, size );
	user_can_show_hex = true;
	
	widget_selector->expandAll();
}

void ElfHunterMainWidget::CloseFile()
{
	memset( long_file_name, 0, sizeof(char)*MAX_PATH );
	
	for( int i=tree_elem.size()-1; i>=0; i-- )
	{
		delete tree_elem[ i ];
	}

	sidewidget->clearwidgets();
	tree_elem.clear();

	if( file_opened )
	{
		actual_file->close();
		file_opened = false;
		delete actual_file;
		
		emit s_filechanged( " --- ", 0 );
	}

	emit s_enable_action( A_OPEN );
	emit s_disable_action( A_CLOSE );
	emit s_disable_action( A_TOGGLEHEX );
	emit s_disable_action( A_TOGGLETREE );
	emit s_disable_action( A_GOTOOFFSET );
	
	widget_selector->hide();
	treewidgetvisible = false;
	
	hexdump->ClearData();
	hexdump->hide();
	hexvisible = false;
	user_can_show_hex = false;
}

void ElfHunterMainWidget::SetFile( bool fromcmdline )
{
	QString fn;
	
	try
	{
		if( fromcmdline )
		{
			fn = cmdline_file2open;
		}
		else
		{
			fn = OpenFile_Dialog();
		}
		OpenFile( fn );
	}
	catch( int ErrorNum )
	{
		if( ErrorNum==ERR_OPEN_FILE_OPEN_ERROR )
			CloseFile();
		return;
	}
	
	if( fn.length() < MAX_PATH )
	{
		memset( long_file_name, 0, sizeof(char)*MAX_PATH );
		realpath( fn.toStdString().c_str(), long_file_name );
		emit s_filechanged( long_file_name, actual_file->size() );
	}
	else // If the path is longer than MAX_PATH, shows only the basename
		emit s_filechanged( fn.toStdString().c_str(), actual_file->size() );
	
	try
	{
		ReadFile();
		emit s_disable_action( A_OPEN );
		emit s_enable_action( A_CLOSE );
		emit s_enable_action( A_TOGGLEHEX );
		emit s_enable_action( A_TOGGLETREE );
		emit s_enable_action( A_GOTOOFFSET );
	}
	catch( int ErrorNum )
	{
		CloseFile();

		QMessageBox msg( QMessageBox::Critical, "Error", "" );

		switch( ErrorNum )
		{
			case ERR_READ_FILE_NOT_OPEN:
				msg.setText( "Error: no file opened. Code 1" );
				break;

			case ERR_READ_INVALID_SIG:
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

void ElfHunterMainWidget::ToggleWidgetTree()
{
	if( treewidgetvisible )
	{
		widget_selector->hide();
		treewidgetvisible = false;
	}
	else
	{
		widget_selector->show();
		treewidgetvisible = true;
	}
}

void ElfHunterMainWidget::Hexdump_GoToOffset()
{
	__uint64_t user_offset = 0;
	
	QString user_offset_str = QInputDialog::getText( this, "Go To Offset", "Offset:" );

	if( user_offset_str.startsWith( "0x", Qt::CaseInsensitive ) )
		user_offset = user_offset_str.toULongLong( 0, 16 );
	else
		user_offset = user_offset_str.toULongLong();
	
	hexdump->GoToOffset( user_offset );
}