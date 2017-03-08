#include "CoordinateDialog.h"

CoordinateDialog::CoordinateDialog(QWidget *parent, Route *prt)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->ui.tableWidget->setItemDelegate(new Delegate);
	this->proute = prt;

	connect(ui.bt_add, SIGNAL(clicked()), this, SLOT(on_add_clicked()));
	connect(ui.bt_finish, SIGNAL(clicked()), this, SLOT(on_finish_clicked()));

}

CoordinateDialog::~CoordinateDialog()
{

}

void CoordinateDialog::on_add_clicked()
{
	int rows = this->ui.tableWidget->rowCount();

	this->ui.tableWidget->setRowCount(rows+1);
	QTableWidgetItem *it = new QTableWidgetItem();
	it->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
	this->ui.tableWidget->setItem(rows, 0, it);

	it = new QTableWidgetItem();
	it->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
	this->ui.tableWidget->setItem(rows, 1, it);

	it = new QTableWidgetItem();
	it->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
	this->ui.tableWidget->setItem(rows, 2, it);
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
