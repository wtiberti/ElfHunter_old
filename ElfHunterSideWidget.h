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
* Filename: ElfHunterSideWidget.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

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
	#include "ElfSymTable.h"

	/** @class ElfHunterSideWidget
	 * @brief Handles the QTabWidget on the right side
	 *
	 * It create the QTabWidget and offer a public slot for adding new tabs.*/
	class ElfHunterSideWidget : public QWidget
	{
	Q_OBJECT

	private:
		QVBoxLayout *layout; ///< Layout for the widget
		
		std::vector< QWidget * > elems;
		QStringList ss;
		int current_widget;
		
		int GetTreeItemIndex( QTreeWidgetItem *index );

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
		
		void clearwidgets();
		void setwidget( QTreeWidgetItem *item ,int col );
		
	};
#endif
