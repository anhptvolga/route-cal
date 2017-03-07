#include "wmain.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WMain w;
	w.show();
	return a.exec();
}
