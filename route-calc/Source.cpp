#if 0

#include <stdlib.h>
#include <QVector>
#include "Setting.h"
#include "route.h"
#include "point.h"
#include "vector.h"


void test1()
{
	Route route("test1");
	QVector<Point> pts;
	//////////////////////////////////////////////////////////////////////////
	pts.append(Point(0, 0 , 0));
	pts.append(Point(0, 0, 500));
	pts.append(Point(0, 0, 1000));
	
	pts.append(Point(0, 300, 1000));
	pts.append(Point(0, 800, 1000));
	pts.append(Point(200, 800, 1000));
	
	pts.append(Point(600, 800, 1000));
	pts.append(Point(600, 800, 1200));
	pts.append(Point(600, 800, 1500));
	
	pts.append(Point(600, 1000, 1500));
	pts.append(Point(600, 1500, 1500));
	pts.append(Point(1000, 1500, 1500));
	
	pts.append(Point(1000, 1500, 1800));
	pts.append(Point(1000, 1500, 2000));
	pts.append(Point(1200, 1500, 2000));
	
	route.update_points(pts);

	//////////////////////////////////////////////////////////////////////////
	QVector<int> free;	
	free.append(2);
	free.append(4);
	free.append(6);
	free.append(8);
	free.append(10);
	free.append(12);
	free.append(14);
	route.set_free_indexs(free);

	route.calcuate();
	
}

void test2()
{
	Route route("test1");
	QVector<Point> pts;
	//////////////////////////////////////////////////////////////////////////
	pts.append(Point(0, 0, 0));
	pts.append(Point(0, 450, 0));
	pts.append(Point(600, 450, 0));
	
	pts.append(Point(600, 800, 0));
	pts.append(Point(600, 1150, 0));
	pts.append(Point(600, 1150, -500));

	pts.append(Point(600, 1535, -500));
	pts.append(Point(600, 1800, -500));
	pts.append(Point(0, 2500, -500));
	
	pts.append(Point(-298, 2500, -500));
	pts.append(Point(-700, 2500, -500));
	pts.append(Point(-700, 2500, -1100));
	pts.append(Point(-700, 2900, -1100));
	route.update_points(pts);

	//////////////////////////////////////////////////////////////////////////
	QVector<int> free;	
	free.append(4);
	free.append(7);
	free.append(10);
	route.set_free_indexs(free);

	route.calcuate();

}

void test3()
{
	Route route("test1");
	QVector<Point> pts;
	//////////////////////////////////////////////////////////////////////////
	pts.append(Point(0, 0 , 0));
	pts.append(Point(250, 21, -210));
	pts.append(Point(250, 401, -210));

	pts.append(Point(250, 998, -210));
	pts.append(Point(250, 1150, -210));
	pts.append(Point(250, 1469, -210));
	
	pts.append(Point(-1379, 1469, -210));
	pts.append(Point(-1379, 1659, -217));
	pts.append(Point(-1379, 2502, -242));

	pts.append(Point(-1379, 2502, 599));
	pts.append(Point(-1379, 2502, -1985));
	pts.append(Point(-1379, 2593, -1985));

	pts.append(Point(-1379, 2648, -1985));
	pts.append(Point(-1379, 2748, -1985));

	route.update_points(pts);

	//////////////////////////////////////////////////////////////////////////
	QVector<int> free;	
	free.append(2);
	free.append(4);
	free.append(7);
	free.append(9);
	free.append(11);
	route.set_free_indexs(free);

	route.calcuate();

}

void test4()
{
	Route route("test1");
	QVector<Point> pts;
	//////////////////////////////////////////////////////////////////////////
	pts.append(Point(0, 0 , 0));
	pts.append(Point(3045, 2709, -277));
	pts.append(Point(3045, 1336, -277));

	pts.append(Point(3045, 1278, -277));
	pts.append(Point(3045, 794, -277));
	pts.append(Point(2001, 794, -277));

	pts.append(Point(1806, 794, -277));
	pts.append(Point(1806, 135, -277));
	pts.append(Point(1806, 135, -768));
	
	pts.append(Point(1806, 135, -1985));
	pts.append(Point(1806, 22, -1985));

	route.update_points(pts);

	//////////////////////////////////////////////////////////////////////////
	QVector<int> free;	
	free.append(2);
	free.append(4);
	free.append(6);
	free.append(8);
	route.set_free_indexs(free);

	route.calcuate();

}

int main() 
{
	Setting::accuracy = 0.02;
	Setting::limit_angle = 15 * 3.14 / 180;
	test4();
	// system("pause");
}

#endif