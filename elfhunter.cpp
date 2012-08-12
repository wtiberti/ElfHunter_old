#include <QtGui>
#include "ElfHunterMainWidget.h"

QMainWindow *w;
ElfHunterMainWidget *mw;
QStatusBar *statusbar;
QMenuBar *menu;
QToolBar *toolbar;

char *rawdata;


QMenuBar *SetupMenu( QApplication *a );
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

	QMenu *im = m->addMenu( "&File" );
	temp = new QAction( "&Open", w );
	im->addAction( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(SetFile()) );
	temp = new QAction( "&Close", w );
	im->addAction( temp );
	QObject::connect( temp, SIGNAL(triggered()), mw, SLOT(CloseFile()) );
	temp = new QAction( "&Exit", w );
	im->addAction( temp );
	QObject::connect( temp, SIGNAL(triggered()), a, SLOT(quit()) );

	im = m->addMenu( "&?" );
	temp = new QAction( "&About ElfHunter", w );
	im->addAction( temp );
	//QObject::connect();

	return m;
}

void Cleaner()
{
	delete menu;
	delete toolbar;
	delete statusbar;
	delete mw;
	delete w;
}
