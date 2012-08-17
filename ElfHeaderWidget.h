#ifndef ElfHeaderWidget_H
	#define ElfHeaderWidget_H

	#include <QtGui>
	#include <elf.h>

	const QString field_names[] =
	{
		"e_ident[MAG]",
		"e_ident[CLASS]",
		"e_ident[DATA]",
		"e_ident[VERSION]",
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
		"e_pentsize",
		"e_phnum",
		"e_shentsize",
		"e_shnum",
		"e_shstrndx"
	};

	#define TABLEROWS 20
	#define TABLECOLUMNS 1

	class ElfHeaderWidget : public QWidget
	{
		Q_OBJECT

		private:
			QVBoxLayout *layout;
			QTableWidget *table;
			QStringList stringlist;

			QString *ToHexString( unsigned char *stream, unsigned int size );

		public:
			ElfHeaderWidget();
			~ElfHeaderWidget();
			void GetValues( char *elfheader );
	};
#endif