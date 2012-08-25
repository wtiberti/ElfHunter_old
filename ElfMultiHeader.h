#ifndef ElfMultiHeader_H
	#define ElfMultiHeader_H

	#include "ElfGenericHeader.h"

	class ElfMultiHeader : public ElfGenericHeader
	{
	Q_OBJECT

	protected:
		QSpinBox *spin;

		unsigned char *base;
		int entry_size;
		__uint64_t offset;

		virtual void SetValues( int index ) = 0;

	public:
		ElfMultiHeader( int r, int c, bool h=true );
		~ElfMultiHeader();

		void SetElfValues( char *elfheader ); // to be "dummy-fied"

		virtual void SelectData( char *data ) = 0;

	public slots:
		void Changed();
	};
#endif