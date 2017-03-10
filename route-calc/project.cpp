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

void Project::delete_route(int index)
{
	int count = this->routes.count();
	if (0 <= index && index < count)
	{
		this->routes.remove(index);
	}
}

void Project::rename_project(QString newnName)
{
	this->name = newnName;
}

void Project::load_from_stream(QTextStream& in)
{
	QString tmp;
	int size, i;
	
	in >> tmp;
	this->name = tmp.trimmed();
	
	in >> size;
	this->routes.clear();
	for (i = 0; i < size; ++i)
	{
		this->routes.append(Route());
		this->routes[i].load_from_stream(in);
	}
}

void Project::save_to_stream(QTextStream& out)
{
	out << name << endl;
	out << routes.count() << endl;
	for (int i = 0; i < routes.count(); ++i)
	{
		routes[i].save_to_stream(out);
	}
}

QString Project::get_name()
{
	return this->name;
}
