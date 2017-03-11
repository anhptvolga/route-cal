#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QWidget>
#include "TranslatorManager.h"
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
	void on_set_en_lang();
	void on_set_ru_lang();

private:
	Ui::SettingDialog ui;
};

#endif // SETTINGDIALOG_H
