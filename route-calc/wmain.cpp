#include "wmain.h"

WMain::WMain(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//////////////////////////////////////////////////////////////////////////
	// connect signals and slots
	connect(ui.bt_add_project, SIGNAL(clicked()), this, SLOT(on_add_project_clicked()));
	connect(ui.bt_delete_project, SIGNAL(clicked()), this, SLOT(on_del_project_clicked()));
	connect(ui.bt_rename_project, SIGNAL(clicked()), this, SLOT(on_ren_project_clicked()));
	
	connect(ui.bt_add_route, SIGNAL(clicked()), this, SLOT(on_add_route_clicked()));
	connect(ui.bt_delete_route, SIGNAL(clicked()), this, SLOT(on_del_route_clicked()));
	connect(ui.bt_rename_route, SIGNAL(clicked()), this, SLOT(on_ren_route_clicked()));

	connect(ui.bt_edit_coordinate, SIGNAL(clicked()), this, SLOT(on_edit_coord()));
	connect(ui.bt_points_connection, SIGNAL(clicked()), this, SLOT(on_pt_connection_clicked()));

	connect(ui.bt_calculate, SIGNAL(clicked()), this, SLOT(on_calc_clicked()));

	connect(ui.bt_save_text, SIGNAL(clicked()), this, SLOT(on_save_file_clicked()));

}

WMain::~WMain()
{

}

void WMain::on_add_project_clicked() 
{
	bool ok;
	QString name = QInputDialog::getText(this, tr("Enter new project name"),
		tr("Name:"), QLineEdit::Normal, "", &ok);
	// TODO: checking repeat name
	if (ok && !name.isEmpty()) 
	{
		ui.cb_projects->addItem(name);
		this->projects.append(Project(name));
	}
}

void WMain::on_del_project_clicked()
{

}

void WMain::on_ren_project_clicked()
{
	bool ok;
	QString name = QInputDialog::getText(this, tr("Enter new name"),
		tr("Name:"), QLineEdit::Normal, "", &ok);
	// TODO: rename project
	if (ok && !name.isEmpty()) 
	{
	}
}

void WMain::on_add_route_clicked()
{
	bool ok;
	QString name = QInputDialog::getText(this, tr("Enter new route name"),
		tr("Name:"), QLineEdit::Normal, "", &ok);
	// TODO: checking repeat name
	if (ok && !name.isEmpty()) 
	{
		ui.cb_routes->addItem(name);
		this->get_current_project()->add_route(name);
	}
}

void WMain::on_del_route_clicked()
{

}

void WMain::on_ren_route_clicked()
{
	bool ok;
	QString name = QInputDialog::getText(this, tr("Enter new name"),
		tr("Name:"), QLineEdit::Normal, "", &ok);
	// TODO: rename route
	if (ok && !name.isEmpty()) 
	{
	}
}

void WMain::on_calc_clicked()
{
	Route *curr = this->get_current_route();
	curr->calcuate();
}

void WMain::on_save_file_clicked()
{

}

void WMain::on_edit_coord()
{
	Route* curroute = this->get_current_route();
	if (curroute != nullptr)
	{
		CoordinateDialog ce(this, curroute);
		ce.exec();
	}
}

Route* WMain::get_current_route()
{
	Route *rt = nullptr;
	int index_route = this->ui.cb_routes->currentIndex();
	if (index_route != -1)
	{
		rt = get_current_project()->get_proute(index_route);
	}
	return rt;
}

Project* WMain::get_current_project()
{
	int index_project = this->ui.cb_projects->currentIndex();
	if (0 <= index_project && index_project < projects.count())
	{
		return &this->projects[index_project];
	} 
	else
	{
		// TODO: Show warning here
	}
	return nullptr;
}

void WMain::on_pt_connection_clicked()
{
	bool ok;
	QString name = QInputDialog::getText(this, tr("Enter indexs of points"),
		tr("Indexs (seperate by \',\'):"), QLineEdit::Normal, "", &ok);
	// TODO: rename route
	if (ok && !name.isEmpty()) 
	{
		QStringList nums = name.split(",", QString::SkipEmptyParts);
		QVector<int> indexs;
		int tmp;
		for (int i = 0; i < nums.count(); ++i)
		{
			tmp = nums[i].toInt();
			if (!indexs.contains(tmp))
			{
				indexs.append(tmp);
			}
		}
		this->get_current_route()->set_free_indexs(indexs);
	}
}
