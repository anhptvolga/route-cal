#ifndef COORDINATE_H
#define COORDINATE_H

#include <QDialog>
#include "ui_coordinate.h"
#include "route.h"
#include <QDebug>
#include <QItemDelegate>
#include <QLineEdit>

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

class Delegate : public QItemDelegate
{
public:
	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
		const QModelIndex & index) const
	{
		QLineEdit *lineEdit = new QLineEdit(parent);
		// Set validator
		QDoubleValidator *validator = new QDoubleValidator(lineEdit);
		lineEdit->setValidator(validator);
		return lineEdit;
	}
};

#endif // COORDINATE_H
