#if 1

#include "wmain.h"
#include <QtWidgets/QApplication>
#include <QString>
#include "TranslatorManager.h"


int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(wmain);

	// Loading config.conf
	if (!QFile::exists(CONFIG_FILENAME))
	{
		// File config not exist
		Setting::Instance()->write_to_file();
	}
	else
	{
		// Loading config
		Setting::Instance()->read_from_file();
	}
	
	// Starting program
	QApplication a(argc, argv);
	// Translator must be created before the application's widgets.
	TranslatorManager* manager = TranslatorManager::instance();
	Q_UNUSED(manager)

	WMain w;
	w.show();
	return a.exec();
}

#endif