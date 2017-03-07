#include "CoordinateDialog.h"

CoordinateDialog::CoordinateDialog(QWidget *parent, Route *prt)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->proute = prt;

	connect(ui.bt_add, SIGNAL(clicked()), this, SLOT(on_add_clicked()));
	connect(ui.bt_finish, SIGNAL(clicked()), this, SLOT(on_finish_clicked()));

}

CoordinateDialog::~CoordinateDialog()
{

}

void CoordinateDialog::on_add_clicked()
{
	int rows = this->ui.tableWidget->rowCount() + 1;

	this->ui.tableWidget->setRowCount(rows);
}

void CoordinateDialog::on_finish_clicked()
{
	QVector<Point> pts;
	int rows = this->ui.tableWidget->rowCount();
	for (int i = 0; i < rows; ++i) 
	{
		qDebug() <<  this->ui.tableWidget->itemAt(i, 0)->text();
		pts.append(Point(
			this->ui.tableWidget->item(i, 0)->text().toDouble(),
			this->ui.tableWidget->item(i, 1)->text().toDouble(),
			this->ui.tableWidget->item(i, 2)->text().toDouble()
			));
	}
	this->proute->update_points(pts);
	this->done(0);
}
