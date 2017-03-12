#include "Setting.h"

Setting* Setting::_pinstance = nullptr;


Setting* Setting::Instance()
{
	if (_pinstance == nullptr)
	{
		_pinstance = new Setting();
	}
	return _pinstance;
}

Setting::Setting()
{
	value_accuracy = 1;
	value_limit_angle = DegToRad(15);
	value_author = "author";
	value_language = "en";
}

Setting::~Setting()
{
	if (_pinstance != nullptr)
	{
		delete _pinstance;
	}
}

void Setting::set_accuracy(double a)
{
	value_accuracy = a;
}

double Setting::accuracy()
{
	return value_accuracy;
}

void Setting::set_limit_angle(double a)
{
	value_limit_angle = a;
}

double Setting::limit_angle()
{
	return value_limit_angle;
}

void Setting::set_author(QString name)
{
	value_author = name;
}

QString Setting::author()
{
	return value_author;
}

void Setting::set_language(QString lang)
{
	value_language = lang;
}

QString Setting::language()
{
	return value_language;
}

void Setting::write_to_file()
{
	QFile file(CONFIG_FILENAME);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	out << this->value_author << endl;
	out << this->value_accuracy << endl;
	out << this->value_limit_angle << endl;
	out << this->value_language << endl;
	file.close();
}

void Setting::read_from_file()
{
	QFile file(CONFIG_FILENAME);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	this->value_author = in.readLine();
	in >> this->value_accuracy;
	in >> this->value_limit_angle;
	in >> this->value_language;
	file.close();
}