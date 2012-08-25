#include "ElfHunterSideWidget.h"

//#include "ElfHWidget.h"

ElfHunterSideWidget::ElfHunterSideWidget( QWidget *parent ) : QWidget(parent)
{
	layout = new QVBoxLayout();

	tabs = new QTabWidget();
	layout->addWidget( tabs );
	setLayout( layout );
}

ElfHunterSideWidget::~ElfHunterSideWidget()
{
	delete tabs;
	delete layout;
}

void ElfHunterSideWidget::addTab( QWidget *w, QString title )
{
	tabs->addTab( w, title );
}