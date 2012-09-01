/** @file ElfHunterHexWidget.h
 * @brief ElfHunterHexWidget class definition
 */

#ifndef ElfHunterHexWidget_H
	#define ElfHunterHexWidget_H

	#include <khexedit/byteseditinterface.h>
	#include <khexedit/valuecolumninterface.h>
	#include <khexedit/charcolumninterface.h>
	#include <khexedit/clipboardinterface.h>

	#include <QtGui>

	/** @class ElfHunterHexWidget
	 * @brief Implementation of KHexEditor interface
	 *
	 * Implements the KHE interface. It provide the standard hex-dump widget
	 * and sets up some methods to insert and clean data inside it. */
	class ElfHunterHexWidget : public QWidget
	{
	Q_OBJECT

	private:
		QWidget *khe_widget; ///< KHexEditor Widget

		KHE::BytesEditInterface *khe_interface; ///< Part of KHE interface
		KHE::ValueColumnInterface *khe_hexvalues; ///< Part of KHE interface
		KHE::CharColumnInterface *khe_charvalues; ///< Part of KHE interface

		QGridLayout *l; ///< Main layout

		char *hexdata; ///< Pointer to data displayed on the widget

	public:
		/** @brief Contructor
		 * @param[in] parent The parent widget */
		ElfHunterHexWidget( QWidget *parent = 0 );
		~ElfHunterHexWidget(); ///< Destructor

		/** @brief Insert data into the widget
		 * @param[in] data Pointer to data to be inserted
		 * @param[in] datasize Size in bytes of data */
		void SetData( char *data, unsigned long datasize );
		void ClearData(); ///< Empty the widget and clear data
	};
#endif