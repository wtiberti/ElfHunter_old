#ifndef ElfHeaderWidget_H
	#define ElfHeaderWidget_H

	#include <QtGui>

	const QString field_names[] =
	{
		"e_ident",
		"e_type",
		"e_machine",
		"e_version",
		"e_entry",
		"e_phoff",
		"e_shoff",
		"e_flags",
		"e_ehsize",
		"e_pentsize",
		"e_phnum",
		"e_shentsize",
		"e_shnum",
		"e_shstrndx"
	};

	#define TABLEROWS 14
	#define TABLECOLUMNS 1

	class ElfHeaderWidget : public QWidget
	{
		Q_OBJECT

		private:
			QVBoxLayout *layout;

			QTableWidget *table;
		public:
			ElfHeaderWidget();
			~ElfHeaderWidget();

	};
#endif