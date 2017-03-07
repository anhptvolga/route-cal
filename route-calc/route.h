#ifndef ROUTE_H
#define ROUTE_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "point.h"
#include "vector.h"

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

	
private:
	QVector<Point> points;
	QVector<int> free_indexs;
	QString name;
};

#endif // ROUTE_H
