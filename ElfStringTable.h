/** @file ElfStringTable.hS
 * @brief ElfStringTable class definition */
#ifndef ElfStringTable_H
	#define ElfStringTable_H

	#include "ElfMultiHeader.h"

	#include <vector>

	/** Field used to display strings */
	const QString str_table_h_hdr[] =
	{
		"Offset",
		"String"
	};

	/** @brief SectStruct definition
	 *
	 * This struct is used to store all the meaningful
	 * values for each string section */
	typedef struct
	{
		int sect_n; ///< Index of the section
		__uint64_t index_name; ///< Index of the name (inside the section header string table)
		__uint64_t offset; ///< Offset to section
		char * addr; ///< Address to section
		__uint64_t size; ///< Size of the section
	} SectStruct;


	/** @class ElfStringTable
	 * @brief Select the string sections and extract all the strings
	 *
	 * This class analyze the section headers and filter all the section marked as
	 * string table. Then, for each section, search for all the strings and display them
	 * on the table.
	 * *NOTE* This class handles *only* strings in sections. Since sections are optional in
	 * pure ELF executable file, you should refer to ElfProgStrings class for strings found in ".DYN" program headers */
	class ElfStringTable : public ElfMultiHeader
	{
	Q_OBJECT

	private:
		char *hdrstrings;
		std::vector< SectStruct > ss; ///< One SectStruct for string section

		/** @brief Add a string to the table
		 * @param[in] v Offset of the string
		 * @param[in] s Pointer to the string */
		void AddString( QString v, QString s );

	protected:
		void SetValues( int index );///< @ref ElfMultiHeader::SetValues

	public:
		ElfStringTable(); ///< Constructor
		~ElfStringTable(); ///< Destructor
		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData
	};
#endif