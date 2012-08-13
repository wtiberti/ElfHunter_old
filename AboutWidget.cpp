#include "AboutWidget.h"

AboutWidget::AboutWidget()
{
	QVBoxLayout l;

	abouttext = new QLabel( "bla bla", this );

	l.addWidget( abouttext );

	setLayout( &l );
}

AboutWidget::~AboutWidget()
{
	delete abouttext;
}