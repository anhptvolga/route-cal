#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QVector>
#include "route.h"

class Project
{

public:
	Project();
	Project(QString name);
	~Project();

	void add_route(QString name);
	void rename_route(QString newnName);
	void delete_route(QString name);

	Route* get_proute(int index);

private:
	QString name;
	QVector<Route> routes;
};

#endif // PROJECT_H
