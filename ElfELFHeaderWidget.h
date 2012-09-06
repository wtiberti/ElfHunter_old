/** @file ElfELFHeaderWidget.h
 * @brief ElfELFHeaderWidget class definition
 */
#ifndef ElfELFHeaderWidget_H
	#define ElfELFHeaderWidget_H

	#include "ElfGenericHeader.h"

	/** ELF Header fields */
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

	/** @class ElfELFHeaderWidget
	 * @brief ELF Header widget class
	 *
	 * This class care about extracting and display the values
	 * of the ELF header fields of the loaded file */
	class ElfELFHeaderWidget : public ElfGenericHeader
	{
	Q_OBJECT
	public:
		ElfELFHeaderWidget(); ///< Constructor
		~ElfELFHeaderWidget(); ///< Destructor

		/** @brief Insert ELF values in the table
		 * @param[in] elfheader Pointer to the ELF file data */
		void SetElfValues( char *elfheader );
	};
#endif