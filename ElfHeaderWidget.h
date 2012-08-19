#ifndef ElfHeaderWidget_H
	#define ElfHeaderWidget_H

	#include <QtGui>
	#include <elf.h>

	//Makes item being enabled, selectable and drag-able
	#define EHW_ITEMFLAGS (Qt::ItemFlag)37

	const QString elfhdr_field_names[] =
	{
		"e_ident[MAG]",
		"e_ident[CLASS]",
		"e_ident[DATA]",
		"e_ident[ELF VERSION]",
		"e_ident[OS ABI]",
		"e_ident[ABI VERSION]",
		"e_ident[IDENT SIZE]",
		"e_type",
		"e_machine",
		"e_version",
		"e_entry",
		"e_phoff",
		"e_shoff",
		"e_flags",
		"e_ehsize",
		"e_phentsize",
		"e_phnum",
		"e_shentsize",
		"e_shnum",
		"e_shstrndx"
	};

	#define ELFHDRTABLEROWS 20
	#define ELFHDRTABLECOLUMNS 1

	class ElfHeaderWidget : public QWidget
	{
		Q_OBJECT

		private:
			QVBoxLayout *layout;
			QTableWidget *table;
			QStringList stringlist;
			bool is64bit;

		public:
			ElfHeaderWidget();
			~ElfHeaderWidget();
			void GetValues( char *elfheader );
			bool IsELF64();
	};
#endif