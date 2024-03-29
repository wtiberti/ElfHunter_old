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
* Filename: ElfHunterConfStruct.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include <QtGui>
#include <vector>

/** @brief Structure holding ElfHunterExec modules information */
struct _execmod
{
	QString name; ///< command name
	int append; ///< append file after the arguments? (1: true, 0:false)
};

/** @brief Contains the current ElfHunter configuration options */
struct ElfHunterConfStruct
{
	std::vector< _execmod > exec_mods; ///< Exec modules list
	// ....
};