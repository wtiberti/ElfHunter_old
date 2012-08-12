#include "ElfHunterSideWidget.h"
#include "ElfHeaderWidget.h"

ElfHunterSideWidget::ElfHunterSideWidget( QWidget *parent ) : QWidget(parent)
{
	layout = new QVBoxLayout();

	tabs = new QTabWidget();
	layout->addWidget( tabs );

	//test
	//elfhdr_w = new ElfHeaderWidget();
	//tabs->addTab( elfhdr_w, "Elf Header" );
	//end test

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