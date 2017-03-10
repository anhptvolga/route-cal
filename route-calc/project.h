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
	
	void rename_project(QString newnName);

	void delete_route(QString name);
	void delete_route(int index);

	QString get_name();
	QStringList get_routes_name();
	Route* get_proute(int index);

	//--- saving and loading methods
	void load_from_stream(QTextStream& in);
	void save_to_stream(QTextStream& out);

private:
	QString name;
	QVector<Route> routes;
};

#endif // PROJECT_H
