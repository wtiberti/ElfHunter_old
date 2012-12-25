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
* Filename: ElfHunterExec.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/
#include "ElfHunterExec.h"

ElfHunterExec::ElfHunterExec()
{
	args.clear();
	
	bt_execute = new QPushButton( "Execute", this );
	lb_command = new QLabel( "---", this );
	le_args = new QLineEdit( this );
	te_output = new QPlainTextEdit( this );
	
	le_args->setPlaceholderText( "<arguments>" );
	te_output->setLineWrapMode( QPlainTextEdit::NoWrap );
	te_output->setReadOnly( true );
	
	layout = new QGridLayout( this );
	layout->addWidget( lb_command, 0, 0 );
	layout->addWidget( le_args, 0, 1 );
	layout->addWidget( bt_execute, 0, 2 );
	layout->addWidget( te_output, 1, 0, 1, 3 );
	
	setLayout( layout );
}

ElfHunterExec::ElfHunterExec( QString cmd, QString filefullpath ) : ElfHunterExec()
{
	SetCommand( cmd ); // TODO: verify the command string
	lb_command->setText( cmd ); // TODO idem
	SetTarget( filefullpath );
	
	// DEBUG
	te_output->setPlainText( target );
}

ElfHunterExec::~ElfHunterExec()
{
	delete te_output;
	delete lb_command;
	delete le_args;
	delete bt_execute;
	delete layout;
}

QString ElfHunterExec::SetCommand( QString command )
{
	//QString old_command = this->command;
	return this->command = command;
	//return old_command;
}

QString ElfHunterExec::GetCommand() const
{
	return command;
}

QString ElfHunterExec::SetTarget( QString filefullpath )
{
	//QString old_target = target;
	return target = filefullpath;
	//return old_target;
}

QString ElfHunterExec::GetTarget() const
{
	return this->target;
}

int ElfHunterExec::Exec()
{
	// TODO
	return 0;
}