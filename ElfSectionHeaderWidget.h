#ifndef ElfSectionHeaderWidget_H
	#define ElfSectionHeaderWidget_H

	#include "ElfGenericHeader.h"

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

	class ElfSectionHeaderWidget : public ElfGenericHeader
	{
	Q_OBJECT

	private:
		unsigned int strsectnx;
		__uint64_t str_offset;
		void GetShStrTable();

	protected:
		void SetValues( int index );

	public:
		ElfSectionHeaderWidget();
		~ElfSectionHeaderWidget();
		void SelectData( char *data );
	};
#endif