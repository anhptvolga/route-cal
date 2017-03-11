#ifndef __SETTING_H__
#define __SETTING_H__

#include <QString>

#define ESP 0.00000000001
#define PI 3.14159265358979323846264338
#define RadToDeg(x) ((x * 180) / 3.14159265358979323846264338)
#define DegToRad(x) ((x * 3.14159265358979323846264338) / 180)

/**
 *  Singleton setting class
 */

class Setting
{
public:

	static Setting* Instance();

	void  set_accuracy(double a);
	double accuracy();

	/**
	 * Setter and getter for limit angle
	 * [in] a : angle in radian
	 */
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

	double value_accuracy;		/// value of accuracy
	double value_limit_angle;	/// limit angle in radian

	QString value_author;		/// author name
	QString value_language;		/// language
};

#endif
