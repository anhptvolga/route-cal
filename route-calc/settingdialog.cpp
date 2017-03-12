#include "settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	this->ui.le_author->setText(Setting::Instance()->author());
	this->ui.sb_acc->setValue(Setting::Instance()->accuracy());
	this->ui.sb_angle->setValue(RadToDeg(Setting::Instance()->limit_angle()));
	if (Setting::Instance()->language() == "en")
	{
		this->ui.rb_en->setChecked(true);
	}
	else
	{
		this->ui.rb_ru->setChecked(true);
	}
		
	// TODO: setting current language

	connect(this->ui.buttonBox, SIGNAL(accepted()), this, SLOT(on_ok_clicked()));
	connect(this->ui.rb_en, SIGNAL(toggled(bool)), this, SLOT(on_set_en_lang()));
	connect(this->ui.rb_ru, SIGNAL(toggled(bool)), this, SLOT(on_set_ru_lang()));
}

SettingDialog::~SettingDialog()
{

}

void SettingDialog::on_ok_clicked()
{
	Setting::Instance()->set_author(this->ui.le_author->text());
	Setting::Instance()->set_accuracy(this->ui.sb_acc->value());
	Setting::Instance()->set_limit_angle(DegToRad(this->ui.sb_angle->value()));
	Setting::Instance()->set_language(ui.rb_en->isChecked() ? "en" : "ru");
	// saving
	Setting::Instance()->write_to_file();
}

void SettingDialog::on_set_ru_lang()
{
	TranslatorManager::instance()->setTranslator(QString("ru"));
	ui.retranslateUi(this);
	this->ui.le_author->setText(Setting::Instance()->author());
}

void SettingDialog::on_set_en_lang()
{
	TranslatorManager::instance()->setTranslator(QString("en"));
	ui.retranslateUi(this);
	this->ui.le_author->setText(Setting::Instance()->author());
}
