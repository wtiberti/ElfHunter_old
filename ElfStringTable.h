#ifndef ElfStringTable_H
	#define ElfStringTable_H

	#include "ElfGenericHeader.h"

	#include <vector>

	const QString str_table_h_hdr[] =
	{
		"Offset",
		"String"
	};

	typedef struct
	{
		int sect_n;
		__uint64_t index_name;
		__uint64_t offset;
		char * addr;
		__uint64_t size;
	} SectStruct;

	class ElfStringTable : public ElfGenericHeader
	{
	Q_OBJECT

	private:
		char *hdrstrings;
		std::vector< SectStruct > ss;

		void AddString( QString v, QString s );

	protected:
		void SetValues( int index );

	public:
		ElfStringTable();
		~ElfStringTable();
		void SelectData( char *data );
	};
#endif