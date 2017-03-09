#include "project.h"

Project::Project()
{

}

Project::Project(QString name)
{
	this->name = name;
}

Project::~Project()
{

}

Route* Project::get_proute(int index)
{
	if (0 <= index && index < this->routes.count())
		return &this->routes[index];
	return nullptr;
}

void Project::add_route(QString name)
{
	this->routes.append(Route(name));
}

QStringList Project::get_routes_name()
{
	QStringList res;
	for (int i = 0; i < routes.count(); ++i)
		res.append(routes[i].get_name());
	return res;
}
