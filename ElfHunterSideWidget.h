/** @file ElfHunterSideWidget.h
 * @brief Definition of ElfHunterSideWidget class
 */

#ifndef ElfHunterSideWidget_H
	#define ElfHunterSideWidget_H

	#include <QtGui>
	#include "ElfELFHeaderWidget.h"
	#include "ElfProgHeaderWidget.h"
	#include "ElfSectionHeaderWidget.h"
	#include "ElfStringTable.h"

	/** @class ElfHunterSideWidget
	 * @brief Handles the QTabWidget on the right side
	 *
	 * It create the QTabWidget and offer a public slot for adding new tabs.*/
	class ElfHunterSideWidget : public QWidget
	{
	Q_OBJECT

	private:
		QVBoxLayout *layout; ///< Layout for the widget
		QTabWidget *tabs; ///< QTabWidget

	public:
		/** @brief Constructor
		 * @param[in] parent The parent widget (optional)*/
		ElfHunterSideWidget( QWidget *parent = 0 );
		~ElfHunterSideWidget(); ///< Destructor

	public slots:
		/** @brief Adds a new widget in a new tab
		 * @param[in] w The widget to be added
		 * @param[in] title The name of the new tab
		 *
		 * Just a wrapper for QTabWidget::addTab*/
		void addTab( QWidget *w, QString title );
	};
#endif
