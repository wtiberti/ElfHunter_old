/*
* This file is part of ElfHunter software.
*
* ElfHunter is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ElfHunter is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ElfHunter.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright (C) 2012 Walter Tiberti
*/

/*
* Filename: ElfHunterDyn.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/ 

/** @file ElfHunterDyn.h
 * @brief Definition of ElfHunterDyn class
 */


#ifndef ElfHunterDyn_H
	#define ElfHunterDyn_H
	
	#include "ElfMultiHeader.h"
	#include "ElfAuxTypes.h"
	#include <vector>
	
	/** @class ElfHunterDyn
	 * @brief Shows the dynamic linking info from program headers or sections */
	class ElfHunterDyn : public ElfMultiHeader
	{
	Q_OBJECT
		
	private:
		bool SegmentDyn; ///< "true" if the source is a segment ( from the program header )
		std::vector< SectStruct > ss; ///<  Vector containing all the dynamic sections/segment
		QStringList offsetlist; ///< Contains the entry offsets as QStrings
	
	protected:
		void SetValues( int index );///< @ref ElfMultiHeader::SetValues
		
	public:
		ElfHunterDyn( bool segment_dyn = true ); ///< Constructor
		~ElfHunterDyn(); ///< Desctructor
		void SelectData( char *data ); ///< @ref ElfMultiHeader::SelectData
		
	private slots:
		/** @brief Invoke raw data highlighting in the hexdump widget */
		void InvokeSelection( int row, int column );
	};
#endif