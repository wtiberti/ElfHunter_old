#ifndef ElfHunterWidget_H
	#define ElfHunterMainWidget_H

	#include "ElfHunterSideWidget.h"
	#include "ElfHunterHexWidget.h"
	#include "AboutWidget.h"

	#include <vector>

	class ElfHunterMainWidget : public QWidget
	{
	Q_OBJECT
	private:
		QGridLayout *layout;

		ElfHunterSideWidget *sidewidget;
		ElfHunterHexWidget *hexdump;

		QFile *actual_file;
		bool file_opened;

		std::vector< QWidget * > tabselem;

		unsigned long OpenFile();
		unsigned long ReadFile();

	public:
		ElfHunterMainWidget( QWidget *parent = 0);
		~ElfHunterMainWidget();
		bool IsFileActive();

	public slots:
		void SetFile();
		void CloseFile();
		void DisplayAbout();
	};
#endif