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
	Init();
}

void ElfHunterExec::Init()
{
	command = "";
	target = "";
	args.clear();
	
	append_filename = false;
	
	bt_execute = new QPushButton( "Execute" );
	lb_command = new QLabel( "---" );
	le_args = new QLineEdit();
	te_output = new QPlainTextEdit();
	
	le_args->setPlaceholderText( "<arguments>" );
	te_output->setLineWrapMode( QPlainTextEdit::NoWrap );
	te_output->setReadOnly( true );
	te_output->setFont( QFont( "Monospace", 8 ) );
	
	layout = new QGridLayout();
	layout->addWidget( lb_command, 0, 0 );
	layout->addWidget( le_args, 0, 1 );
	layout->addWidget( bt_execute, 0, 2 );
	layout->addWidget( te_output, 1, 0, 1, 3 );
	
	setLayout( layout );
	
	last_return_value = 0;
}

ElfHunterExec::ElfHunterExec( QString cmd, QString filefullpath, bool wantfilename )
{
	Init();
	SetCommand( cmd ); // TODO: verify the command string
	lb_command->setText( cmd );
	SetTarget( filefullpath ); // TODO idem
	
	append_filename = wantfilename;
	
	connect( bt_execute, SIGNAL(clicked()), this, SLOT(Execute()) );
	connect( le_args, SIGNAL(returnPressed()), this, SLOT(Execute()) );
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
	return this->command = command;
}

QString ElfHunterExec::GetCommand() const
{
	return command;
}

QString ElfHunterExec::SetTarget( QString filefullpath )
{
	return target = filefullpath;
}

QString ElfHunterExec::GetTarget() const
{
	return this->target;
}

void ElfHunterExec::Execute()
{
	QProcess process;
	QString buffer;
	
	ParseArguments();
	
	//process.setWorkingDIrectory( ); //TODO
	process.setProcessChannelMode( QProcess::MergedChannels );
	
	if( append_filename )
		args << target;
	
	process.start( command, args );
	
	buffer = "[ELFHUNTER CMD]: ";
	buffer.append( command ).append(" ");
	for( int i=0; i<args.size(); i++ )
	{
		buffer.append( " " ).append( args[i] );
	};
	buffer.append( "\n\n" );
	
	while( process.waitForReadyRead() )
	{
		buffer.append( process.readAll() );
	}
	te_output->setPlainText( buffer );
	last_return_value = process.exitCode();
	
	process.close();
}

int ElfHunterExec::GetLastRetValue() const
{
	return last_return_value;
}

void ElfHunterExec::ParseArguments()
{
	//TODO: insert a tab with checkboxes instead
	args.clear();
	if( le_args->text() != "" )
		args = le_args->text().split(" ");
}