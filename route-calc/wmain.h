#ifndef WMAIN_H
#define WMAIN_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "ui_wmain.h"
#include "CoordinateDialog.h"
#include "project.h"
#include "settingdialog.h"

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

	void on_edit_coord();
	void on_pt_connection_clicked();

	void on_calc_clicked();
	void on_save_file_clicked();

	void on_current_project_changed();
	void on_current_route_changed();

	void on_setting_triggered();
	void on_about_triggered();

	void on_action_open();
	void on_action_save();
	void on_action_import();

private:
	Ui::MainWindow ui;

	QVector<Project> projects;

	Project* get_current_project();
	Route* get_current_route();

};

#endif // WMAIN_H
