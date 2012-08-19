#ifndef ElfProgHeaderWidget_H
	#define ElfProgHeaderWidget_H

	#include <QtGui>

	//Makes item being enabled, selectable and drag-able
	#define EHW_ITEMFLAGS (Qt::ItemFlag)37

	const QString proghdr_field_names[] =
	{
		"p_type",
		"p_offset",
		"p_vaddr",
		"p_paddr",
		"p_filesz",
		"p_memsz",
		"p_flags",
		"p_align"
	};

	const QString proghdr_field_names64[] =
	{
		"p_type",
		"p_flags",
		"p_offset",
		"p_vaddr",
		"p_paddr",
		"p_filesz",
		"p_memsz",
		"p_align"
	};

	#define PROGHDRTABLEROWS 8
	#define PROGHDRTABLECOLUMNS 1

	class ElfProgHeaderWidget : public QWidget
	{
		Q_OBJECT

		private:
			QVBoxLayout *layout;
			QSpinBox *spin;
			QTableWidget *table;
			QStringList stringlist;
			bool is64bit;
			unsigned char *base;
			__uint64_t phoff;
			int entry_size;
			void SetValues( int index );

		public:
			ElfProgHeaderWidget();
			~ElfProgHeaderWidget();
			void SelectData( char *elffile );
		public slots:
			void Changed();
	};

#endif