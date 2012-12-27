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
* Filename: ElfHunterExec.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file ElfHunterExec.h
 * @brief Definition of ElfHunterExec class
 */

#ifndef ElfHunterExec_H
	#define ElfHunterExec_H
	
	#include <QtGui>
	
	/** @class ElfHunterExec
	 * @brief Executes a shell command, showing (standard) output and error*/
	class ElfHunterExec : QWidget
	{
	Q_OBJECT
	private:
		QString command; ///< Command to be executed
		QString target; ///< Filename
		QStringList args; ///< list of arguments to be passed
		int last_return_value; ///< return value of the last execution
		
		bool append_filename; ///< Flag. Specify if include the filename in the process call
		
		QGridLayout *layout; ///< base layout
		QPushButton *bt_execute; ///< "Execute" button
		QLabel *lb_command; ///< label showing the command name
		QLineEdit *le_args; ///< text line where user can insert arguments
		QPlainTextEdit *te_output; ///< output textedit control
		
		/** @brief Prepare the arguments list */
		void ParseArguments();

	public:
		ElfHunterExec(); ///< Constructor
		
		/** @brief Full constructor
		 * @param[in] cmd command to be executed
		 * @param[in] filefullpath actual file full path
		 * @param[in] wantfilename Specify if include the filename in the process call */
		ElfHunterExec( QString cmd, QString filefullpath, bool wantfilename=true );
		
		/** @brief ElfHunterExec common initialization */
		void Init();
		
		~ElfHunterExec(); ///< Destructor
		
		/** @brief Sets the command
		 * @param[in] command Command to be executed */
		QString SetCommand( QString command );
		
		/** @brief Retrieve the current command
		 * @return The current command */
		QString GetCommand() const;
		
		/** @brief Sets the current target
		 * @param[in] filefullpath target file full path */
		QString SetTarget( QString filefullpath );
		
		/** @brief Retrive the current target
		 * @return The current target file name */
		QString GetTarget() const;
		
		/** @brief Retrieve the return value of the last process execution
		 * @return The return value */
		int GetLastRetValue() const;
		
	public slots:
		/** @brief Execute the command (QT SLOT) */
		void Execute();
	};
#endif