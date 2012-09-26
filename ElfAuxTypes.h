#ifndef ElfAuxTypes_H
	#define ElfAuxTypes_H

	/** @brief SectStruct definition
	 *
	 * This struct is used to store all the meaningful
	 * values for each string section */
	typedef struct
	{
		int sect_n; ///< Index of the section
		__uint64_t index_name; ///< Index of the name (inside the section header string table)
		__uint64_t offset; ///< Offset to section
		char *addr; ///< Address to section
		__uint64_t size; ///< Size of the section
	} SectStruct;

#endif