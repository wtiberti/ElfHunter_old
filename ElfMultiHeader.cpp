#include "ElfMultiHeader.h"
#include <elf.h>

ElfMultiHeader::ElfMultiHeader( int r, int c, bool h ) : ElfGenericHeader( r, c, h )
{
	spin = new QSpinBox();
	layout->addWidget( spin );
}

ElfMultiHeader::~ElfMultiHeader()
{
	delete spin;
}

void ElfMultiHeader::SetElfValues( char *elfheader )
{ /* Not needed */ }

void ElfMultiHeader::Changed()
{
	SetValues( spin->value() );
}