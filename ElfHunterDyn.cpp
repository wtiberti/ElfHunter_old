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
* Filename: ElfHunterDyn.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/
#include "ElfSectionHeaderWidget.h"
#include "ElfHunterDyn.h"

ElfHunterDyn::ElfHunterDyn( bool segment_dyn ) : ElfMultiHeader( 0, 4 )
{
	SegmentDyn = segment_dyn;
	
	spin->setMinimum( 0 );
	table->horizontalHeader()->setResizeMode( QHeaderView::Interactive );
	
	if( SegmentDyn )
	{
		table->horizontalHeaderItem(0)->setText( "[SEGMENT]" );
		spin->setPrefix( "Dynamic Header # " );
	}
	else
	{
		table->horizontalHeaderItem(0)->setText( "[SECTION]" );
		spin->setPrefix( "Dynamic Section # " );
	}
	
	table->horizontalHeaderItem(1)->setText( "[OFFSET]" );
	table->horizontalHeaderItem(2)->setText( "d_tag" );
	table->horizontalHeaderItem(3)->setText( "d_val / d_ptr" );
	
	table->horizontalHeader()->setStretchLastSection( true );

	le_search->hide();
};

ElfHunterDyn::~ElfHunterDyn()
{
	ss.clear();
};

void ElfHunterDyn::SelectData( char *data )
{
	SectStruct temp_s;
	__uint64_t hdroff;
	unsigned int hdrnum;
	
	ss.clear();
	
	Elf32_Ehdr *header = (Elf32_Ehdr *)data;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)data;
	
	base = (unsigned char *) data;
	is64bit = header->e_ident[EI_CLASS]==ELFCLASS64?true:false;
	
	ss.clear();
	
	if( SegmentDyn )
	{
		Elf64_Phdr *prog64;
		Elf32_Phdr *prog;
		
		if( is64bit )
		{
			hdroff = header64->e_phoff;
			hdrnum = header64->e_phnum;
		}
		else
		{
			hdroff = header->e_phoff;
			hdrnum = header->e_phnum;
		}
		
		prog = (Elf32_Phdr *)(data+hdroff);
		prog64 = (Elf64_Phdr *)(data+hdroff);
		
		for( unsigned int i=0; i<hdrnum; i++ )
		{
			if( is64bit )
			{
				if( prog64[i].p_type==PT_DYNAMIC )
				{
					temp_s.sect_n = i;
					temp_s.index_name = 0;
					temp_s.offset = prog64[i].p_offset;
					temp_s.addr = (char *)(base + temp_s.offset);
					temp_s.size = prog64[i].p_filesz;
					ss.push_back( temp_s );
				}
			}
			else
			{
				if( prog[i].p_type==PT_DYNAMIC )
				{
					temp_s.sect_n = i;
					temp_s.index_name = 0;
					temp_s.offset = prog[i].p_offset;
					temp_s.addr = (char *)(base + temp_s.offset);
					temp_s.size = prog[i].p_filesz;
					ss.push_back( temp_s );
				}
			}
		}
	}
	else
	{
		Elf64_Shdr *sect64;
		Elf32_Shdr *sect;
		
		if( is64bit )
		{
			hdroff = header64->e_shoff;
			hdrnum = header64->e_shnum;
		}
		else
		{
			hdroff = header->e_shoff;
			hdrnum = header->e_shnum;
		}
		
		sect = (Elf32_Shdr *)(data+hdroff);
		sect64 = (Elf64_Shdr *)(data+hdroff);
		
		for( unsigned int i=0; i<hdrnum; i++ )
		{
			if( is64bit )
			{
				if( sect64[i].sh_type==SHT_DYNAMIC )
				{
					temp_s.sect_n = i;
					temp_s.index_name = sect64[i].sh_name;
					temp_s.offset = sect64[i].sh_offset;
					temp_s.addr = (char *)(base + temp_s.offset);
					temp_s.size = sect64[i].sh_size;
					ss.push_back( temp_s );
				}
			}
			else
			{
				if( sect[i].sh_type==SHT_DYNAMIC )
				{
					temp_s.sect_n = i;
					temp_s.index_name = sect[i].sh_name;
					temp_s.offset = sect[i].sh_offset;
					temp_s.addr = (char *)(base + temp_s.offset);
					temp_s.size = sect[i].sh_size;
					ss.push_back( temp_s );
				}
			}
		}
	}
	
	spin->setMaximum( (ss.size()==0)?0:ss.size()-1 );
	spin->setSuffix( " of " + QString::number( spin->maximum() ) );
	if( ss.size()>0 )
	{
		connect( table, SIGNAL(cellClicked(int, int)), this, SLOT(InvokeSelection(int,int)) );
		connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
		SetValues( 0 );
	}
};

void ElfHunterDyn::SetValues( int index )
{
	QString hdr_name;
	QString temp_string;
	__uint64_t cursor = 0;
	__uint64_t temp_value;

	offsetlist.clear();
	stringlist.clear();
	valueslist.clear();
	
	if( SegmentDyn )
	{
		hdr_name = QString( "Prog Header #" );
		hdr_name.append( QString::number(ss[index].sect_n) );
	}
	else
	{
		hdr_name = QString( ElfSectionHeaderWidget::GetSectionName( (char*)base, ss[index].sect_n ) );
	}
	
	Elf32_Dyn *cur = (Elf32_Dyn *)(ss[index].addr);
	Elf64_Dyn *cur64 = (Elf64_Dyn *)(ss[index].addr);
	
	while( cursor < ss[index].size )
	{
		temp_string = QString::number( cursor+ss[index].offset, 16 );
		temp_string = temp_string.toUpper().prepend( "0x" );
		offsetlist << temp_string;
		
		temp_value = is64bit?cur64->d_tag:cur->d_tag;
		
		switch( temp_value )
		{
			case DT_NULL:
				stringlist << "DT_NULL";
				break;
			case DT_NEEDED:
				stringlist << "DT_NEEDED";
				break;
			case DT_PLTRELSZ:
				stringlist << "DT_PLTRELSZ";
				break;
			case DT_PLTGOT:
				stringlist << "DT_PLTGOT";
				break;
			case DT_HASH:
				stringlist << "DT_HASH";
				break;
			case DT_STRTAB:
				stringlist << "DT_STRTAB";
				break;
			case DT_SYMTAB:
				stringlist << "DT_SYMTAB";
				break;
			case DT_RELA:
				stringlist << "DT_RELA";
				break;
			case DT_RELASZ:
				stringlist << "DT_RELASZ";
				break;
			case DT_RELAENT:
				stringlist << "DT_RELAENT";
				break;
			case DT_STRSZ:
				stringlist << "DT_STRSZ";
				break;
			case DT_SYMENT:
				stringlist << "DT_SYMENT";
				break;
			case DT_INIT:
				stringlist << "DT_INIT";
				break;
			case DT_FINI:
				stringlist << "DT_FINI";
				break;
			case DT_SONAME:
				stringlist << "DT_SONAME";
				break;
			case DT_RPATH:
				stringlist << "DT_RPATH";
				break;
			case DT_SYMBOLIC:
				stringlist << "DT_SYMBOLIC";
				break;
			case DT_REL:
				stringlist << "DT_REL";
				break;
			case DT_RELSZ:
				stringlist << "DT_RELSZ";
				break;
			case DT_RELENT:
				stringlist << "DT_RELENT";
				break;
			case DT_PLTREL:
				stringlist << "DT_PLTREL";
				break;
			case DT_DEBUG:
				stringlist << "DT_DEBUG";
				break;
			case DT_TEXTREL:
				stringlist << "DT_TEXTREL";
				break;
			case DT_JMPREL:
				stringlist << "DT_JMPREL";
				break;
			case DT_BIND_NOW:
				stringlist << "DT_BIND_NOW";
				break;
			case DT_INIT_ARRAY:
				stringlist << "DT_INIT_ARRAY";
				break;
			case DT_FINI_ARRAY:
				stringlist << "DT_FINI_ARRAY";
				break;
			case DT_INIT_ARRAYSZ:
				stringlist << "DT_INIT_ARRAYSZ";
				break;
			case DT_FINI_ARRAYSZ:
				stringlist << "DT_FINIT_ARRAYSZ";
				break;
				
			// TODO add other
				
			default:
				if( temp_value >= DT_LOPROC )
				{
					if( temp_value >= DT_HIPROC )
						stringlist << "DT_HIPROC";
					else
						stringlist << "DT_LOPROC";
				}
				else
				{
					if( temp_value >= DT_LOOS )
					{
						if( temp_value >= DT_HIOS )
							stringlist << "DT_HIOS";
						else
							stringlist << "DT_LOOS";
					}
					else
					{
						stringlist << "[unknown]";
					}
				}
		}
		
		temp_value = is64bit?(cur64->d_un.d_val):(cur->d_un.d_val);
		temp_string = QString::number( temp_value, 16 );
		temp_string = temp_string.toUpper().prepend( "0x" );
		valueslist << temp_string;
		
		cur++;
		cur64++;
		cursor += is64bit?sizeof(Elf64_Dyn):sizeof(Elf32_Dyn);
	}
	
	
	ClearRows();
	QTableWidgetItem *table_item;
	
	for( int i=0; i<offsetlist.size(); i++ )
	{
		AddRow();
		
		table_item = new QTableWidgetItem( hdr_name );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 0, table_item );
		
		table_item = new QTableWidgetItem( offsetlist[i] );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 1, table_item );
		
		table_item = new QTableWidgetItem( stringlist[i] );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 2, table_item );
		
		table_item = new QTableWidgetItem( valueslist[i] );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 3, table_item );
	}
	
	table->horizontalHeader()->resizeSections( QHeaderView::ResizeToContents );
};

void ElfHunterDyn::InvokeSelection( int row, int column )
{
	unsigned int spin_value = spin->value();
	
	__uint64_t offset = ss[spin_value].offset;
	__uint64_t size = is64bit?sizeof(Elf64_Dyn):sizeof(Elf32_Dyn);
	
	offset += row*size;
	switch( column )
	{
		case 2:
			size = is64bit?sizeof(Elf64_Sxword):sizeof(Elf32_Sword);
			break;
		case 3:
			size = is64bit?sizeof(Elf64_Xword):sizeof(Elf32_Word);
			offset += is64bit?sizeof(Elf64_Sxword):sizeof(Elf32_Sword);
			break;
	}
	emit S_selection_changed( offset, size );
};

void ElfHunterDyn::Update( char *data )
{
	SelectData( data );
}