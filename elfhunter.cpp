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
#include <iostream>
#include <getopt.h>

#include <QtGui>
#include <QtXml/QDomDocument>

#include "ElfHunterWindow.h"
#include "ElfHunterConfStruct.h"

/* CONSTANTS SECTION */
// TODO: using a more standard path
#define CONF_FILE_PATH "./ElfHunter.conf"


/* COMMAND LINE SECTION */
bool cmdline_onlyreport = false; ///< Generate a report about the file without show ui
QString cmdline_file2open; ///< Filename passed through command line


/* CONFIGURATION FILE SECTION */
QFile conf_file( CONF_FILE_PATH );
QDomDocument conf_file_dom;
bool conf_file_valid = true;
ElfHunterConfStruct conf_struct;


/** @brief ElfHunter program Entry Point */
int main( int argc, char *argv[] )
{
	bool cmdline_valid = true;
	char cmdline_option = '\0';
	
	if( conf_file.open( QIODevice::ReadOnly ) )
	{
		if( conf_file_dom.setContent( &conf_file ) )
		{
			QDomNodeList conf_nodes;
			QDomElement conf_element = conf_file_dom.documentElement();
			
			/* ExecModules parsing */
			conf_nodes = conf_element.elementsByTagName("ExecModules").at(0).toElement().elementsByTagName("mod");
			conf_struct.exec_mods.clear();
			for( int i=0; i<conf_nodes.count(); i++ )
			{
				_execmod tempmod;
				tempmod.name = conf_nodes.at(i).attributes().namedItem("cmd").nodeValue();
				tempmod.append = conf_nodes.at(i).attributes().namedItem("appendfile").nodeValue().toInt();
				conf_struct.exec_mods.push_back( tempmod );
			}
			
			//TODO: other options
			
			
			//TEST
			for( unsigned int i=0; i<conf_struct.exec_mods.size(); i++ )
			{
				qDebug() << "[DEBUG]: Added " << conf_struct.exec_mods[i].name << " exec module ( wantfilename=" << conf_struct.exec_mods[i].append << ")";
			}
			
		}
		else
			conf_file_valid = false;
		
		conf_file.close();
	}
	else
		conf_file_valid = false;
	
	if( !conf_file_valid )
	{
		// TODO: re-create a default configuration file
		qDebug() << "[DEBUG]: Configuration not found! (path: \"" << CONF_FILE_PATH << "\" )";
	}
	
	QApplication main_app( argc, argv );
	main_app.setApplicationName( "ElfHunter" );
	
	while( cmdline_option != -1 )
	{
		cmdline_option = getopt( argc, argv, "hr:o:" );
		switch( cmdline_option )
		{
			case 'r':
				//TODO recursive report about all files in the specified dir
				qDebug() << "[DEBUG]: Option \'r\' recognized with arg:" << optarg;
				break;
			case 'o':
				//TODO report to file
				qDebug() << "[DEBUG]: Option \'o\' recognized with arg:" << optarg;
				break;
			case 'h':
			case '?':
				cmdline_valid = false;
				break;
		}
	}
	
	if( !cmdline_valid )
	{
		std::cerr << "\n---\nUsage: ElfHunter [ -h , -o <output file> , -r ] [<file to open>]\n---\n";
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