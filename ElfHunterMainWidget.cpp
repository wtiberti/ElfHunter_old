#include "ElfHunterMainWidget.h"

#ifndef ELFHUNTER_STANDALONE
#include <vector>
extern std::vector< QAction * > menuactions;
extern std::vector< QAction * > tbactions;
#endif

ElfHunterMainWidget::ElfHunterMainWidget( QWidget *parent )
	: QWidget(parent)
{
	layout = new QGridLayout();
	sidewidget = new ElfHunterSideWidget( this );
	hexdump = new ElfHunterHexWidget( this );

	// VERTICAL LAYOUT
	//layout->setColumnStretch( 0, 2 );
	//layout->setColumnStretch( 1, 3 );
	//layout->addWidget( sidewidget, 0, 0 );
	//layout->addWidget( hexdump, 0, 1 );

	// HORIZONTAL LAYOUT
	layout->addWidget( sidewidget, 0, 0 );
	layout->addWidget( hexdump, 1, 0 );

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
	{
		CloseFile();
	}

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

	filedata = new char[ actual_file->size() ];
	dataread = actual_file->read( filedata, actual_file->size() );

	signature = * ( int * )filedata;

	if( signature != 0x464C457F )
	{
		delete filedata;
		throw 2;
	}

	ElfHeaderWidget *temp_elfhdr = new ElfHeaderWidget();
	sidewidget->addTab( (QWidget *)temp_elfhdr, "ELF Hdr" );
	tabselem.push_back( (QWidget *)temp_elfhdr );
	temp_elfhdr->GetValues( filedata );

	int n_sh = temp_elfhdr->GetNumOfSections();
	int n_ph = temp_elfhdr->GetNumOfProgHeaders();

	/*
	qDebug() << temp_elfhdr->IsELF64();
	qDebug() << n_ph;
	qDebug() << n_sh;
	qDebug() << temp_elfhdr->GetProgHeaderOff( 0 );
	qDebug() << temp_elfhdr->GetProgHeaderOff( 1 );
	qDebug() << temp_elfhdr->GetSectHeaderOff( 0 );
	qDebug() << temp_elfhdr->GetSectHeaderOff( 1 );
	*/

	for( int i=0; i<n_ph; i++ )
	{
		ElfProgHeaderWidget *temp_proghdr = new ElfProgHeaderWidget();
		sidewidget->addTab( (QWidget *)temp_proghdr, "Prog Hdr "+QString::number(i) );
		tabselem.push_back( (QWidget *)temp_proghdr );
		temp_proghdr->GetValues( filedata );
	}


	hexdump->SetData( filedata, dataread );
	return dataread;
}

void ElfHunterMainWidget::CloseFile()
{
	for( int i=0; i<tabselem.size(); i++ )
	{
		delete tabselem[ i ];
	}

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
		{
			CloseFile();
		}
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

		return;
	}
}

void ElfHunterMainWidget::DisplayAbout()
{
	AboutWidget about;

	about.exec();
}