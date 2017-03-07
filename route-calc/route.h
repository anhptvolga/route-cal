#ifndef ROUTE_H
#define ROUTE_H

#include <QObject>
#include <QVector>

typedef struct _POINT {
	double x;
	double y;
	double z;
	_POINT() { x = y = z = 0; }
	_POINT(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }
} Point, Vector;

class Route
{
public:
	Route();
	Route(QString name);
	~Route();

	void update_points(QVector<Point> pts);

	QVector<Point> get_points();

	void calcuate();
	
private:
	QVector<Point> points;
	QString name;
};

#endif // ROUTE_H
