#ifndef ElfHunterSideWidget_H
	#define ElfHunterSideWidget_H

	#include <QtGui>
	#include "ElfHeaderWidget.h"

	class ElfHunterSideWidget : public QWidget
	{
		Q_OBJECT

		private:
			QVBoxLayout *layout;
			QTabWidget *tabs;

			ElfHeaderWidget *elfhdr_w;

		public:
			ElfHunterSideWidget( QWidget *parent = 0 );
			~ElfHunterSideWidget();

		public slots:
			void addTab( QWidget *w, QString title );
	};

#endif
