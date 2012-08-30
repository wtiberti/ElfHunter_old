/** @file ElfHunterMainWidget.h
 * @brief Definition of ElfHunterMainWidget class
 */

#ifndef ElfHunterWidget_H
	#define ElfHunterMainWidget_H

	#include "ElfHunterSideWidget.h"
	#include "ElfHunterHexWidget.h"
	#include "AboutWidget.h"

	#include <vector>

	/** @class ElfHunterMainWidget
	 * @brief Handles the internal widget set
	 *
	 * Defines a widget which is used both as a wrapper and a handler to
	 * the internal widget set. It handles all the read operation and all
	 * things related to the internal widgets (such as creation, deletion etc. )
	 */
	class ElfHunterMainWidget : public QWidget
	{
	Q_OBJECT
	private:
		QGridLayout *layout; ///< Main layout of the widget

		ElfHunterSideWidget *sidewidget; ///< Left side main widget
		ElfHunterHexWidget *hexdump; ///< Right side hex dump widget

		QFile *actual_file; ///< Pointer to actual file
		bool file_opened; ///< Flag. If a file is opened, it's true

		/** A std::vector which groups all the widgets used in the tabs
		 * @see ElfHunterSideWidget.h
		 */
		std::vector< QWidget * > tabselem;

		/** @brief Open a file
		 *
		 * Shows the QT's "Open File" standard dialog, and try to open
		 * the selected file. Altough there's no restriction on the file choosen,
		 * all non-ELF file will be discared in the @ref ReadFile method
		 * @return The opened file size
		 *
		 */
		unsigned long OpenFile();

		/** @brief Read the opened file
		 *
		 * Try to read the previously opened file by @ref OpenFile and create all the information widgets
		 * according the file content.
		 * @return The pointer to the file content
		 */
		unsigned long ReadFile();

	public:
		/** @brief Constructor
		 *
		 * Initialize the layout, create a @ref ElfHunterSideWidget and a @ref ElfHunterHexWidget.
		 * @param[in] parent The parent widget. (Optional)
		 */
		ElfHunterMainWidget( QWidget *parent = 0);

		/** @brief Destructor
		 *
		 * Close the file (if open) and delete all the created widgets
		 */
		~ElfHunterMainWidget();

		/** @brief Detect if a file is opened
		 */
		bool IsFileActive();

	public slots:
		/** @brief Wrapper method. (QT slot)
		 */
		void SetFile();

		/** @brief Close the file. (QT slot)
		 */
		void CloseFile();

		/** @brief Display a @ref AboutWidget (QT slot)
		 */
		void DisplayAbout();
	};
#endif