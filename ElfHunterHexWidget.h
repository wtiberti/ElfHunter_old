#ifndef ElfHunterHexWidget_H
	#define ElfHunterHexWidget_H

	#include <khexedit/byteseditinterface.h>
	#include <khexedit/valuecolumninterface.h>
	#include <khexedit/charcolumninterface.h>
	#include <khexedit/clipboardinterface.h>

	#include <QtGui>

	class ElfHunterHexWidget : public QWidget
	{
		Q_OBJECT

	private:
		QWidget *khe_widget;

		KHE::BytesEditInterface *khe_interface;
		KHE::ValueColumnInterface *khe_hexvalues;
		KHE::CharColumnInterface *khe_charvalues;

		QGridLayout *l;

		char *hexdata;

	public:
		ElfHunterHexWidget( QWidget *parent = 0 );
		~ElfHunterHexWidget();

		void SetData( char *data, unsigned long datasize );
		void ClearData();
	};

#endif