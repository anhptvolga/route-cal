#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QWidget>
#include "ui_setting.h"

class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	SettingDialog(QWidget *parent);
	~SettingDialog();

private:
	Ui::SettingDialog ui;
};

#endif // SETTINGDIALOG_H
