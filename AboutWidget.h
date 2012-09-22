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
* Filename: AboutWidget.h
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

/** @file AboutWidget.h
 * @brief AboutWidget class definition*/

#ifndef AboutWidget_H
	#define AboutWidget_H

	#include <QtGui>

	/** @class AboutWidget
	 * @brief Shows the "about" dialog
	 *
	 * Create a QDialog and put some info on it.
	 * At the moment, it only contains a QLabel with dummy text, but in the
	 * future, will be also a picture and maybe scrolling text*/
	class AboutWidget : public QDialog
	{
	private:
		QLabel *abouttext; ///< A label that contains the about text

	public:
		/** @brief Constructor
		 *
		 * Adjust the layout and set the information text into the label*/
		AboutWidget();

		/** @brief Destructor
		 *
		 * Destroy the QLabel item contening the information text*/
		~AboutWidget();
	};
#endif