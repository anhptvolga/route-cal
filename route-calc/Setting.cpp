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
	value_limit_angle = 15;
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
