#ifndef AboutWidget_H

	#define AboutWidget_H

	#include <QtGui>

	class AboutWidget : public QDialog
	{
		private:
		QLabel *abouttext;

		public:
		AboutWidget();
		~AboutWidget();
	};
#endif