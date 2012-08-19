#ifndef ElfProgHeaderWidget_H
	#define ElfProgHeaderWidget_H

	#include <QtGui>

	//Makes item being enabled, selectable and drag-able
	#define EHW_ITEMFLAGS (Qt::ItemFlag)37

	const QString proghdr_field_names[] =
	{
		"[Offset]",
		"p_type",
		"p_offset",
		"p_vaddr",
		"p_filesz",
		"p_memsz",
		"p_flags",
		"p_align"
	};

	#define PROGHDRTABLEROWS 8
	#define PROGHDRTABLECOLUMNS 1

	class ElfProgHeaderWidget : public QWidget
	{
		Q_OBJECT

		private:
			QVBoxLayout *layout;
			QTableWidget *table;
			QStringList stringlist;

			bool is64bit;
			__uint64_t base_offset;

		public:
			ElfProgHeaderWidget();
			~ElfProgHeaderWidget();
			void GetValues( char *progheader );
	};

#endif