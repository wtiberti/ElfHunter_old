#ifndef ElfHeader_H
	#define ElfHeader_H

	#include <QtGui>

	const QString generic_horizontal_labels[] =
	{
		"Value",
		"Meaning"
	};

	class ElfGenericHeader : public ElfHeaderWidget//public QWidget
	{
	Q_OBJECT

	//private:
		//unsigned int columns;
		//unsigned int rows;
		// bool tableheaders;

	protected:
		//QVBoxLayout *layout;
		QSpinBox *spin;
		//QTableWidget *table;
		//QStringList stringlist;
		//QStringList valueslist;
		//bool is64bit;

		unsigned char *base;
		int entry_size;
		__uint64_t offset;

		virtual void SetValues( int index ) = 0;

	public:
		ElfGenericHeader( int r, int c, bool h=true );
		~ElfGenericHeader();
		/*void AddHeader_H();
		void AddHeader_V();
		int AddRow();
		int AddCol();
		void ClearRows();*/
		virtual void SelectData( char *data ) = 0;

	public slots:
		void Changed();
	};


#endif