/** @file ElfProgHeaderWidget.h
 * @brief ElfProgHeaderWidget class definition */
#ifndef ElfProgHeaderWidget_H
	#define ElfProgHeaderWidget_H

	#include "ElfMultiHeader.h"

	/** Program Header fields ( 32-bit version ) */
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

	/** Program Header fields ( 64-bit version ) */
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

	#define PROGHDRTABLEROWS 8 ///< Number of rows needed for a program header
	#define PROGHDRTABLECOLUMNS 2 ///< Number of columns needed for a program header

	/** @class ElfProgHeaderWidget
	 * @brief Class for Program Headers
	 *
	 * This class aims to read all the program headers and their fields. */
	class ElfProgHeaderWidget : public ElfMultiHeader
	{
	Q_OBJECT

	protected:
		void SetValues( int index ); ///< @ref ElfMultiHeader::SetValues

	public:
		ElfProgHeaderWidget(); ///< Constructor
		~ElfProgHeaderWidget(); ///< Destructor

		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData
	};

#endif