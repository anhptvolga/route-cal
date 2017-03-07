#ifndef WMAIN_H
#define WMAIN_H

#include <QtWidgets/QMainWindow>
#include "ui_wmain.h"
#include <QtWidgets/QInputDialog>


class WMain : public QMainWindow
{
	Q_OBJECT

public:
	WMain(QWidget *parent = 0);
	~WMain();

public slots:
	void on_add_project_clicked();
	void on_del_project_clicked();
	void on_ren_project_clicked();

	void on_add_route_clicked();
	void on_del_route_clicked();
	void on_ren_route_clicked();

	void on_calc_clicked();
	void on_save_file_clicked();

private:
	Ui::MainWindow ui;
};

#endif // WMAIN_H
