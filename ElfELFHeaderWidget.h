#ifndef ElfELFHeaderWidget_H
	#define ElfELFHeaderWidget_H

	#include "ElfGenericHeader.h"

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

	class ElfELFHeaderWidget : public ElfGenericHeader
	{
	Q_OBJECT
	public:
		ElfELFHeaderWidget();
		~ElfELFHeaderWidget();
		void SetElfValues( char *elfheader );
	};
#endif