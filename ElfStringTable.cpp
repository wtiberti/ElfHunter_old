#include "ElfStringTable.h"
#include <elf.h>

ElfStringTable::ElfStringTable() : ElfGenericHeader( 1, 2 )
{
	spin->setMinimum( 0 );
	spin->setPrefix( "String table # " );

	table->horizontalHeaderItem( 0 )->setText( str_table_h_hdr[0] );
	table->horizontalHeaderItem( 1 )->setText( str_table_h_hdr[1] );

	//TODO funzione per killare gli header verticali
}

ElfStringTable::~ElfStringTable()
{}

void ElfStringTable::SetValues( int index )
{
	//TODO
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

	for( int i=0; i<sectnum; i++ )
	{
		if( is64bit )
			if( sect64[i].sh_type==SHT_STRTAB )
			{
				temp_s.index_name = sect64[i].sh_name;
				temp_s.offset = (__uint64_t)base + sect64[i].sh_offset;
				temp_s.size = sect64[i].sh_size;
				ss.push_back( temp_s );
			}
		else
			if( sect[i].sh_type==SHT_STRTAB )
			{
				temp_s.index_name = sect[i].sh_name;
				temp_s.offset = (__uint64_t)base + sect[i].sh_offset;
				temp_s.size = sect[i].sh_size;
				ss.push_back( temp_s );
			}
	}

	spin->setMaximum( ss.size()-1 );
	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(Changed()) );
	//SetValues( 0 );
}