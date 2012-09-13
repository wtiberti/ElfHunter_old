/** @file ElfSectionHeaderWidget.h
 * @brief ElfSectionHeaderWidget class definition */
#ifndef ElfSectionHeaderWidget_H
	#define ElfSectionHeaderWidget_H

	#include "ElfMultiHeader.h"

	/** Section Header fields */
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

	#define SECTHDRTABLEROWS 11 ///<Number of rows needed for a section header
	#define SECTHDRTABLECOLUMNS 2 ///<Number of columns needed for a section header

	/** @class ElfSectionHeaderWidget
	 * @brief Class for Section Headers
	 *
	 * This class aims to read and show all the Section Headers and their fields */
	class ElfSectionHeaderWidget : public ElfMultiHeader
	{
	Q_OBJECT

	private:
		unsigned int strsectnx; ///< Index of the section headers' string table
		__uint64_t str_offset; ///<  Offset to the section headers' string table
		void GetShStrTable(); ///< Gets the offset to the section headers' string table

	protected:
		void SetValues( int index ); ///< @ref ElfMultiHeader::SetValues

	public:
		ElfSectionHeaderWidget(); ///< Constructor
		~ElfSectionHeaderWidget(); ///< Destructor
		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData
	};
#endif