#ifndef COORDINATE_H
#define COORDINATE_H

#include <QDialog>
#include "ui_coordinate.h"
#include "route.h"

class CoordinateDialog : public QDialog
{
	Q_OBJECT

public:
	CoordinateDialog(QWidget *parent = 0, Route *prt = nullptr);

	~CoordinateDialog();

public slots:
	void on_add_clicked();
	void on_finish_clicked();

private:
	Ui::CoordinateEditor ui;
	Route *proute;
};

#endif // COORDINATE_H
