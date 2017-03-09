#ifndef ROUTE_H
#define ROUTE_H

#include <climits>
#include <QObject>
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "point.h"
#include "vector.h"

#define PI 3.14159265


class Route
{
public:
	Route();
	Route(QString name);
	~Route();

	void update_points(QVector<Point> pts);

	QVector<Point> get_points();

	void set_free_indexs(QVector<int> frindexs);

	void calcuate();
	bool can_calculate();

	void set_name(QString value);
	QString get_name();

	void write_detail_to_file(QString filename);

private:
	QVector<Point> points;
	QVector<int> free_indexs;

	// For each pair of parallel routes
	QVector<Vector> vus, ves, vns;
	QVector<double> vRs;

	QString name;
	int count_parallel;
};

#endif // ROUTE_H
