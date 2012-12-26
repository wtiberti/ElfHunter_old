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
#ifndef ElfHunterExec_H
	#define ElfHunterExec_H
	
	#include <QtGui>
	
	class ElfHunterExec : QWidget
	{
	Q_OBJECT
	private:
		QString command;
		QString target;
		QStringList args;
		int last_return_value;
		
		QGridLayout *layout;
		QPushButton *bt_execute;
		QLabel *lb_command;
		QLineEdit *le_args;
		QPlainTextEdit *te_output;
		
		void ParseArguments();

	public:
		ElfHunterExec();
		ElfHunterExec( QString cmd, QString filefullpath );
		~ElfHunterExec();
		QString SetCommand( QString command );
		QString GetCommand() const;
		QString SetTarget( QString filefullpath );
		QString GetTarget() const;
		int GetLastRetValue() const;
		
	public slots:
		void Execute();
	};
#endif