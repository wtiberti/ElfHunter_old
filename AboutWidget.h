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