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
* Filename: elfhunter.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include <QtGui>
#include <getopt.h>
#include "ElfHunterWindow.h"

bool cmdline_onlyreport = false;
QString cmdline_file2open;

int main( int argc, char *argv[] )
{
	bool cmdline_valid = true;
	char cmdline_option = '\0';
	
	QApplication main_app( argc, argv );
	main_app.setApplicationName("ElfHunter");
	
	while( cmdline_option != -1 )
	{
		cmdline_option = getopt( argc, argv, "hro:" );
		switch( cmdline_option )
		{
			case 'r':
				//TODO recursive report about all files in the specified dir
				qDebug() << "Option \'r\' recognized!";
				break;
			case 'o':
				//TODO report to file
				qDebug() << "Option \'o\' recognized with arg:" << optarg;
				break;
			case 'h':
			case '?':
				cmdline_valid = false;
				break;
		}
	}
	
	if( !cmdline_valid )
	{
		//FIXME
		qDebug() << "\n\n---\nUsage: ElfHunter [ -h , -o <output file> , -r ] <file to open>\n---\n";
		return 0;
	}
	
	if( optind>0 )
	{
		cmdline_file2open = QString( argv[optind] );
	}
	
	ElfHunterWindow w;
	w.show();

	return main_app.exec();
}