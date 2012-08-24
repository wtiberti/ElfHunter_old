#include "ElfStringTable.h"
#include <elf.h>

ElfStringTable::ElfStringTable() : ElfGenericHeader( 0, 2 )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "String table # " );

	table->horizontalHeaderItem( 0 )->setText( str_table_h_hdr[0] );
	table->horizontalHeaderItem( 1 )->setText( str_table_h_hdr[1] );
}

ElfStringTable::~ElfStringTable()
{}

void ElfStringTable::SetValues( int index )
{
	QTableWidgetItem *table_item;
	QString *temp_string;
	QString *str_off;

	stringlist.clear();
	valueslist.clear();

	temp_string = new QString( (char *)(hdrstrings+ss[index].index_name) );
	str_off = new QString();
	str_off->setNum( ss[index].sect_n );
	AddString( str_off->prepend( "[SECT n°] " ), *temp_string );

	unsigned int i=0;
	while( i<ss[index].size )
	{
		str_off = new QString();
		str_off->setNum( (ss[index].offset)+i, 16 );
		temp_string = new QString( (char *)(ss[index].addr+i) );

		AddString( str_off->toUpper().prepend("0x"), *temp_string );

		i += temp_string->length() + 1;
	}

	ClearRows();
	for( int i=0; i<valueslist.size(); i++ )
	{
		AddRow();
		table_item = new QTableWidgetItem( valueslist[i] );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 0, table_item );

		table_item = new QTableWidgetItem( stringlist[i] );
		table_item->setFlags( (Qt::ItemFlag)37 );
		table->setItem( i, 1, table_item );
	}
}

void ElfStringTable::SelectData( char *data )
{
	SectStruct temp_s;
	__uint64_t sectoff;
	unsigned int sectnum;

	Elf32_Ehdr *header = (Elf32_Ehdr *)data;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)data;
	Elf64_Shdr *sect64;
	Elf32_Shdr *sect;

	base = (unsigned char *) data;
	is64bit = header->e_ident[EI_CLASS]==ELFCLASS64?true:false;

	if( is64bit )
	{
		sectoff = header64->e_shoff;
		hdrstrings = (char *) (base + sectoff + (int)(header64->e_shstrndx)*(int)(header64->e_shentsize));

		hdrstrings = (char *)(base + ((Elf64_Shdr *)hdrstrings)->sh_offset);
		sectnum = header64->e_shnum;
	}
	else
	{
		sectoff = header->e_shoff;
		hdrstrings = (char *) (base + sectoff + (int)(header->e_shstrndx)*(int)(header->e_shentsize));
		hdrstrings = (char *)(base + ((Elf32_Shdr *)hdrstrings)->sh_offset);
		sectnum = header->e_shnum;
	}

	sect = (Elf32_Shdr *)(data+sectoff);
	sect64 = (Elf64_Shdr *)(data+sectoff);

	for( unsigned int i=0; i<sectnum; i++ )
	{
		if( is64bit )
		{
			if( sect64[i].sh_type==SHT_STRTAB )
			{
				temp_s.sect_n = i;
				temp_s.index_name = sect64[i].sh_name;
				temp_s.offset = sect64[i].sh_offset;
				temp_s.addr = (char *)(base + temp_s.offset);
				temp_s.size = sect64[i].sh_size;

				/*TEST
				qDebug() << temp_s.index_name;
				qDebug() << temp_s.offset;
				qDebug() << (__uint64_t) temp_s.addr;
				QString *test = new QString( temp_s.addr+1 );
				qDebug() << *test;
				delete test;
				qDebug() << temp_s.size;*/


				ss.push_back( temp_s );
			}
		}
		else
		{
			if( sect[i].sh_type==SHT_STRTAB )
			{
				temp_s.index_name = sect[i].sh_name;
				temp_s.offset = sect[i].sh_offset;
				temp_s.addr = (char *)(base + temp_s.offset);
				temp_s.size = sect[i].sh_size;
				ss.push_back( temp_s );
			}
		}
	}

	spin->setMaximum( ss.size()-1 );
	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );

	/*TEST
	for( int i=0; i<ss.size(); i++ )
	{
		qDebug() << i;
		qDebug() << ss[i].index_name;
		qDebug() << ss[i].offset << (__uint64_t)ss[i].addr;
		qDebug() << ss[i].size;
	}*/

	SetValues( 0 );
}

void ElfStringTable::AddString( QString v, QString s )
{
	valueslist << v;
	stringlist << s;
}