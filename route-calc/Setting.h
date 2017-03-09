
#ifndef __SETTING_H__
#define __SETTING_H__

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
	
private:
	Setting();
	~Setting();

	static Setting* _pinstance;

	double value_accuracy;
	double value_limit_angle;
};

#endif
