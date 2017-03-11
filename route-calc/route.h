#ifndef ROUTE_H
#define ROUTE_H

#include <climits>
#include <QDateTime>
#include <QObject>
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "point.h"
#include "vector.h"
#include "settingdialog.h"


struct DetailPar
{
	int i, j; // parallel pair vector i and j in vtsafter
	Vector vn;
	Vector delta_T;
	double R;
	double L;
	double max_sx, max_sy, max_sz;
	double min_sx, min_sy, min_sz;
	double tmax_x, tmax_y, tmax_z;
	double tmin_x, tmin_y, tmin_z;
	Vector vR;
	Vector ve;
	Vector vu;
};

class Route
{

public:
	Route();
	Route(QString name);
	~Route();

	void update_points(QVector<Point> pts);

	QVector<Point> get_points();

	void set_free_indexs(QVector<int> frindexs);
	QString get_free_indexs();

	void calcuate();
	bool can_calculate();

	void set_name(QString value);
	QString get_name();

	void write_detail_to_file(QString filename);

	int count_number_of_straight_sections();
	int count_parrallel_pairs();

	bool is_has_parallel();

	/*
	 * getter for date time
	 */
	QDateTime get_dt_creation();
	QDateTime get_dt_last_change();
	
	/*
	 * getters for max, min values
	 */
	double get_max_sx();
	double get_max_sy();
	double get_max_sz();
	double get_min_sx();
	double get_min_sy();
	double get_min_sz();

	//--- saving and loading methods
	void load_from_stream(QTextStream& in);
	void save_to_stream(QTextStream& out);

private:
	QVector<Point> points;
	QVector<int> free_indexs;

	// Results
	QVector<Vector> vtsafter;	/// List of vector with free points connection.
	QVector<DetailPar> details;
	double max_sx, max_sy, max_sz;
	double min_sx, min_sy, min_sz;
	bool isHasParallel;

	QString name;

	double f(double t, double u, double e);
	void calc_max_min(int i);

	void calc_angle_t(int i, double t);
	
	QDateTime dt_creation;
	QDateTime dt_last_change;
};

#endif // ROUTE_H
