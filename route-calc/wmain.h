#ifndef WMAIN_H
#define WMAIN_H

#include <QtWidgets/QMainWindow>
#include "ui_wmain.h"

class WMain : public QMainWindow
{
	Q_OBJECT

public:
	WMain(QWidget *parent = 0);
	~WMain();

private:
	Ui::WMainClass ui;
};

#endif // WMAIN_H
