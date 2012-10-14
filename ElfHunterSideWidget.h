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

	/** @class ElfHunterSideWidget
	 * @brief Handles a list of widget which displays on user will */
	class ElfHunterSideWidget : public QWidget
	{
	Q_OBJECT

	private:
		QVBoxLayout *layout; ///< Layout for the widget
		
		std::vector< QWidget * > elems; ///< Vector containing all the data widget
		QStringList ss; ///< Auxiliary list of string, containing the titles of all the widget added
		
		int current_widget; ///< The current widget (as index in @ref elems )
		QTreeWidgetItem *last_treeitem; ///< Last selected widget
		
		/** @brief Retrieve the index (relative to @ref elems ) of a QTreeWidgetItem
		 * @param[in] item The QTreeWidgetItem
		 * @return The index of the @ref item */
		int GetTreeItemIndex( QTreeWidgetItem *item );

	public:
		/** @brief Constructor
		 * @param[in] parent The parent widget (optional)*/
		ElfHunterSideWidget( QWidget *parent = 0 );
		~ElfHunterSideWidget(); ///< Destructor

	public slots:
		/** @brief Adds a new widget
		 * @param[in] w The widget to be added
		 * @param[in] title The title of the widget
		 *
		 * (The name is inherit from previous "tabbed" implementation) */
		void addTab( QWidget *w, QString title );
		
		/** @brief Clears the widget vector (freeing memory too) */
		void clearwidgets();
		
		/** @brief Selects and shows a previously added widget
		 * @param[in] item The new item to be shown
		 * @param[in] col The column choosen (Not used) */
		void setwidget( QTreeWidgetItem *item ,int col );
		
	};
#endif
