
#ifndef __SETTING_H__
#define __SETTING_H__

#include <QString>

/**
 *  Singleton setting class
 */

class Setting
{
public:

	static Setting* Instance();

	void  set_accuracy(double a);
	double accuracy();

	void set_limit_angle(double a);
	double limit_angle();

	void set_author(QString name);
	QString author();

	void set_language(QString lang);
	QString language();
	
private:
	Setting();
	~Setting();

	static Setting* _pinstance;

	double value_accuracy;
	double value_limit_angle;

	QString value_author;
	QString value_language;
};

#endif
