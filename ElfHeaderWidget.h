#ifndef ElfHeaderWidget_H
	#define ElfHeaderWidget_H

	#include <QtGui>
	#include <elf.h>
	#include <vector>

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
	#define ELFHDRTABLECOLUMNS 2

	class ElfHeaderWidget : public QWidget
	{
	Q_OBJECT
	private:
		unsigned int columns;
		unsigned int rows;
		bool tableheaders;

	protected:
		QVBoxLayout *layout;
		QTableWidget *table;
		QStringList stringlist;
		QStringList valueslist;
		bool is64bit;

	public:
		ElfHeaderWidget( int r, int c, bool h=true );
		~ElfHeaderWidget();
		//void GetValues( char *elfheader );
		virtual void SelectData( char *data );
		bool IsELF64();
		static bool HasSections( char *data );
		void AddHeader_H();
		void AddHeader_V();
		int AddRow();
		int AddCol();
		void ClearRows();

	};
#endif