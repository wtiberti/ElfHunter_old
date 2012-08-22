#ifndef ElfProgHeaderWidget_H
	#define ElfProgHeaderWidget_H

	#include "ElfGenericHeader.h"

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
	#define PROGHDRTABLECOLUMNS 2

	class ElfProgHeaderWidget : public ElfGenericHeader
	{
	Q_OBJECT

	protected:
		void SetValues( int index );

	public:
		ElfProgHeaderWidget();
		~ElfProgHeaderWidget();
		void SelectData( char *data );
	};

#endif