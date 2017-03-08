#include "CoordinateDialog.h"

CoordinateDialog::CoordinateDialog(QWidget *parent, Route *prt)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->ui.tableWidget->setItemDelegate(new Delegate);
	this->proute = prt;

	connect(ui.bt_add, SIGNAL(clicked()), this, SLOT(on_add_clicked()));
	connect(ui.bt_finish, SIGNAL(clicked()), this, SLOT(on_finish_clicked()));

	// show old coordiate
	if (proute != nullptr) 
	{
		QVector<Point> points = proute->get_points();
		this->ui.tableWidget->setRowCount(points.count());
		for (int i = 0; i < points.count(); ++i)
		{
			QTableWidgetItem *it = new QTableWidgetItem();
			it->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
			it->setText(QString::number(points[i].get_x()));
			this->ui.tableWidget->setItem(i, 0, it);

			it = new QTableWidgetItem();
			it->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
			it->setText(QString::number(points[i].get_y()));
			this->ui.tableWidget->setItem(i, 1, it);

			it = new QTableWidgetItem();
			it->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
			it->setText(QString::number(points[i].get_z()));
			this->ui.tableWidget->setItem(i, 2, it);
		}
		this->on_add_clicked();
	}
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
	QString x, y, z;
	for (int i = 0; i < rows; ++i) 
	{
		x = this->ui.tableWidget->item(i, 0)->text();
		y = this->ui.tableWidget->item(i, 1)->text();
		z = this->ui.tableWidget->item(i, 2)->text();
		if (!(x.isEmpty() || y.isEmpty() || z.isEmpty()))
			pts.append(Point(x.toDouble(), y.toDouble(), z.toDouble()));
	}
	this->proute->update_points(pts);
	this->done(0);
}
