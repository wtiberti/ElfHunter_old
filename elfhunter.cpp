#include <QtGui>
#include <vector>
#include "ElfHunterMainWidget.h"

QMainWindow *w;
ElfHunterMainWidget *mw;

QStatusBar *statusbar;

QMenuBar *menu;
std::vector< QAction * > menuactions;

QToolBar *toolbar;
std::vector< QAction * > tbactions;

QToolBar *SetupToolBar();
QMenuBar *SetupMenu( QApplication *a );
QString *ToHexString( unsigned char *stream, unsigned int size );
void Cleaner();

int main( int argc, char *argv[] )
{
	QApplication main_app( argc, argv );

	w = new QMainWindow();
	w->resize( 1000, 700 );

	statusbar = new QStatusBar( w );
	toolbar = new QToolBar( w );
	mw = new ElfHunterMainWidget( w );

	menu = SetupMenu( &main_app );
	toolbar = SetupToolBar();

	w->setMenuBar( menu );
	w->setStatusBar( statusbar );
	w->addToolBar( toolbar );
	w->setCentralWidget( mw );
	w->show();

	main_app.exec();

	Cleaner();

	return 0;
}

QMenuBar *SetupMenu( QApplication *a )
{
	QMenuBar *m = new QMenuBar();
	QAction *temp;

	menuactions.clear();

	QMenu *im = m->addMenu( "&File" );
	temp = new QAction( "&Open", im );
	im->addAction( temp );
	menuactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(SetFile()) );

	temp = new QAction( "&Close", im );
	temp->setEnabled( false );
	im->addAction( temp );
	menuactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(CloseFile()) );

	temp = new QAction( "&Exit", im );
	im->addAction( temp );
	menuactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), a, SLOT(quit()) );

	im = m->addMenu( "&?" );
	temp = new QAction( "&About ElfHunter", im );
	im->addAction( temp );
	menuactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(DisplayAbout()) );

	return m;
}

QToolBar *SetupToolBar()
{
	QAction *temp;

	tbactions.clear();

	QToolBar *t = new QToolBar( "Main Toolbar", w );

	//TODO Add icons

	temp = new QAction( "Open", t );
	t->addAction( temp );
	tbactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(SetFile()) );

	temp = new QAction( "Close", t );
	temp->setEnabled( false );
	t->addAction( temp );
	tbactions.push_back( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(CloseFile()) );

	return t;
}

QString *ToHexString( unsigned char *stream, unsigned int size )
{
	char *buffer = new char[5*size+1];
	char temp_buffer[10];
	QString *result;

	memset( buffer, 0, sizeof(char)*(5*size+1) );

	for( unsigned int i=0; i<size; i++ )
	{
		memset( temp_buffer, 0, sizeof(char)*10 );
		snprintf( temp_buffer, 6, "0x%.2X ", stream[i] );
		strncat( buffer, temp_buffer, 6 );
	}

	result = new QString( buffer );
	*result = result->trimmed();

	delete buffer;

	return result;
}

void Cleaner()
{
	menuactions.clear();
	delete menu;

	tbactions.clear();
	delete toolbar;

	delete statusbar;
	delete mw;
	delete w;
}
