#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QWidget>
#include "ui_setting.h"
#include "Setting.h"


class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	SettingDialog(QWidget *parent);
	~SettingDialog();

public slots:
	void on_ok_clicked();

private:
	Ui::SettingDialog ui;
};

#endif // SETTINGDIALOG_H
