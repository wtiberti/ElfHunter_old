#ifndef ElfGenericHeader_H
	#define ElfGenericHeader_H

	#include <QtGui>
	#include <elf.h>
	#include <vector>

	//Makes item being enabled, selectable and drag-able
	#define EHW_ITEMFLAGS (Qt::ItemFlag)37

	const QString generic_horizontal_labels[] =
	{
		"Value",
		"Meaning",
		"Info"
	};

	class ElfGenericHeader : public QWidget
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
		ElfGenericHeader( int r, int c, bool h=true );
		~ElfGenericHeader();

		bool IsELF64();
		void AddHeader_H();
		void AddHeader_V();
		int AddRow();
		int AddCol();
		void ClearRows();

		static bool HasSections( char *data );
		static QString *ToHexString( unsigned char *stream, unsigned int size );

		virtual void SetElfValues( char *elfheader ) = 0;
	};
#endif