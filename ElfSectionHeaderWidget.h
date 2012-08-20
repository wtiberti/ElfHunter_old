#ifndef ElfSectionHeaderWidget_H
	#define ElfSectionHeaderWidget_H

	#include <QtGui>

	//Makes item being enabled, selectable and drag-able
	#define EHW_ITEMFLAGS (Qt::ItemFlag)37

	const QString secthdr_field_names[] =
	{
		"[offset]",
		"sh_name",
		"sh_type",
		"sh_flags",
		"sh_addr",
		"sh_offset",
		"sh_size",
		"sh_link",
		"sh_info",
		"sh_addralign",
		"sh_entsize"
	};

	#define SECTHDRTABLEROWS 11
	#define SECTHDRTABLECOLUMNS 1

	class ElfSectionHeaderWidget : public QWidget
	{
		Q_OBJECT

		private:
			QVBoxLayout *layout;
			QSpinBox *spin;
			QTableWidget *table;
			QStringList stringlist;
			bool is64bit;
			unsigned char *base;
			__uint64_t shoff;
			int entry_size;
			void SetValues( int index );

		public:
			ElfSectionHeaderWidget();
			~ElfSectionHeaderWidget();
			void SelectData( char *elffile );
		public slots:
			void Changed();
	};

#endif