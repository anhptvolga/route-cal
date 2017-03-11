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
	
	connect(ui.cb_projects, SIGNAL(currentIndexChanged(int)), this, SLOT(on_current_project_changed()));
	connect(ui.cb_routes, SIGNAL(currentIndexChanged(int)), this, SLOT(on_current_route_changed()));

	connect(ui.actionSetting, SIGNAL(triggered(bool)), this, SLOT(on_setting_triggered()));
	connect(ui.actionAbout, SIGNAL(triggered(bool)), this, SLOT(on_about_triggered()));

	connect(ui.actionOpen, SIGNAL(triggered(bool)), this, SLOT(on_action_open()));
	connect(ui.actionSave, SIGNAL(triggered(bool)), this, SLOT(on_action_save()));
	connect(ui.actionImport, SIGNAL(triggered(bool)), this, SLOT(on_action_import()));
	connect(ui.actionExit, SIGNAL(triggered(bool)), this, SLOT(on_action_exit()));

	connect(ui.actionExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
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
		this->projects.append(Project(name));
		ui.cb_projects->addItem(name);
		ui.cb_projects->setCurrentIndex(ui.cb_projects->count()-1);
	}
}

void WMain::on_del_project_clicked()
{
	int index = ui.cb_projects->currentIndex();
	if (index != -1)
	{
		// comfirm
		QMessageBox::StandardButton ok =  QMessageBox::question(
			this, "Sure?", "Are you sure?");
		if (ok == QMessageBox::Yes)
		{
			this->projects.remove(index);
			ui.cb_projects->removeItem(index);
			QMessageBox::information(this, tr("Deleted"), tr("Project deleted."));
		}
	}
	else // No project selected
	{
		QMessageBox::warning(this, tr("No project"), tr("Please create project first."));
	}
}

void WMain::on_ren_project_clicked()
{
	Project *cur = this->get_current_project();
	if (cur != nullptr)
	{
		bool ok;
		QString name = QInputDialog::getText(this, tr("Enter new name"),
			tr("Name:"), QLineEdit::Normal, "", &ok);
		// TODO: rename project
		if (ok && !name.isEmpty()) 
		{
			cur->rename_project(name);
			this->ui.cb_projects->setItemText(ui.cb_projects->currentIndex(), name);
		}
	}
	else // No project selected
	{
		QMessageBox::warning(this, tr("No project"), tr("Please create project first."));
	}
}

void WMain::on_add_route_clicked()
{
	Project *cur = this->get_current_project();
	if (cur != nullptr)
	{
		bool ok;
		QString name = QInputDialog::getText(this, tr("Enter new route name"),
			tr("Name:"), QLineEdit::Normal, "", &ok);
		// TODO: checking repeat name
		if (ok && !name.isEmpty()) 
		{
			cur->add_route(name);
			ui.cb_routes->addItem(name);
			ui.cb_routes->setCurrentIndex(ui.cb_routes->count()-1);
			ui.date_creation->setText(this->get_current_route()->get_dt_creation().toString("hh:mm dd.MM.yyyy"));
			ui.date_change->setText(this->get_current_route()->get_dt_last_change().toString("hh:mm dd.MM.yyyy"));
		}
	}
	else // No project selected
	{
		QMessageBox::warning(this, tr("No project"), tr("Please choose project first."));
	}
}

void WMain::on_del_route_clicked()
{
	int index = ui.cb_routes->currentIndex();
	if (index != -1)
	{
		// comfirm
		QMessageBox::StandardButton ok =  QMessageBox::question(
			this, "Sure?", "Are you sure?");
		if (ok == QMessageBox::Yes)
		{
			Project * prj = this->get_current_project();
			if (prj != nullptr)
			{
				prj->delete_route(index);
				ui.cb_routes->removeItem(index);
				ui.date_creation->setText(this->get_current_route()->get_dt_creation().toString("hh:mm dd.MM.yyyy"));
				ui.date_change->setText(this->get_current_route()->get_dt_last_change().toString("hh:mm dd.MM.yyyy"));
			}
			QMessageBox::information(this, tr("Deleted"), tr("Route deleted."));
		}
	}
	else // No project selected
	{
		QMessageBox::warning(this, tr("No route"), tr("No route to delete."));
	}
}

void WMain::on_ren_route_clicked()
{
	int index = ui.cb_routes->currentIndex();
	if (index != -1)
	{
		bool ok;
		QString name = QInputDialog::getText(this, tr("Enter new name"),
			tr("Name:"), QLineEdit::Normal, "", &ok);
		// TODO: rename project
		if (ok && !name.isEmpty()) 
		{
			Project * prj = this->get_current_project();
			if (prj != nullptr)
			{
				prj->get_proute(index)->set_name(name);
				this->ui.cb_routes->setItemText(ui.cb_routes->currentIndex(), name);
				ui.date_creation->setText(this->get_current_route()->get_dt_creation().toString("hh:mm dd.MM.yyyy"));
				ui.date_change->setText(this->get_current_route()->get_dt_last_change().toString("hh:mm dd.MM.yyyy"));
			}
		}
	}
	else // No project selected
	{
		QMessageBox::warning(this, tr("No route"), tr("No route to rename."));
	}
}

void WMain::on_calc_clicked()
{
	Route *curr = this->get_current_route();
	if (curr != nullptr && curr->can_calculate())
	{
		curr->calcuate();
		// show results to ui
		int cparallel = curr->count_parrallel_pairs();
		ui.number_of_parallel->setText(QString::number(cparallel));
		if (cparallel != 0)
		{
			double  max_sx = curr->get_max_sx(),
				    max_sy = curr->get_max_sy(),
					max_sz = curr->get_max_sz(),
					min_sx = curr->get_min_sx(),
					min_sy = curr->get_min_sy(),
					min_sz = curr->get_min_sz();
			
			ui.field_ox->setText((abs(max_sx) < 0.00000001 && abs(min_sx) < 0.00000001) ? "0" :
				tr("From") + " " + QString::number(min_sx) + " " + tr("To") + " " + QString::number(max_sx));
			ui.field_oy->setText((abs(max_sy) < 0.00000001 && abs(min_sy) < 0.00000001) ? "0" :
				tr("From") + " " + QString::number(min_sy) + " " + tr("To") + " " + QString::number(max_sy));
			ui.field_oz->setText((abs(max_sz) < 0.00000001 && abs(min_sz) < 0.00000001) ? "0" :
				tr("From") + " " + QString::number(min_sz) + " " + tr("To") + " " + QString::number(max_sz));
			if (100 - min(max_sx, abs(min_sx)) > 0) { 
				ui.note_ox->setText(tr("Appoint overdimension: ") + QString::fromWCharArray(L"\u2206") + "L = " + QString::number(100 - min(max_sx, abs(min_sx))));
			} else {
				ui.note_ox->setText(tr("Don\'t appoint overdimension."));
			}
			if (100 - min(max_sy, abs(min_sy)) > 0) { 
				ui.note_oy->setText(tr("Appoint overdimension: ") + QString::fromWCharArray(L"\u2206") + "L = " + QString::number(100 - min(max_sy, abs(min_sy))));
			} else {
				ui.note_oy->setText(tr("Don\'t appoint overdimension."));
			}
			if (100 - min(max_sz, abs(min_sz)) > 0) { 
				ui.note_oz->setText(tr("Appoint overdimension: ") + QString::fromWCharArray(L"\u2206") + "L = " + QString::number(100 - min(max_sz, abs(min_sz))));
			} else {
				ui.note_oz->setText(tr("Don\'t appoint overdimension."));
			}
		}
	}
	else
	{
		QMessageBox::warning(this, tr("Can not calculate"), tr("Please checking route again."));
	}
}

void WMain::on_save_file_clicked()
{
	Route* curroute = this->get_current_route();
	if (curroute != nullptr)
	{
		QString filename = QFileDialog::getSaveFileName(this, tr("Save"));
		if (!filename.isEmpty())
		{
			curroute->write_detail_to_file(filename);
			QMessageBox::information(this, tr("Saved"), tr("Saved."));
		}
	}
}

void WMain::on_edit_coord()
{
	Route* curroute = this->get_current_route();
	if (curroute != nullptr)
	{
		CoordinateDialog ce(this, curroute);
		ce.exec();
		this->ui.number_of_straight_sections->setText(QString::number(curroute->count_number_of_straight_sections()));
	}
}

Route* WMain::get_current_route()
{
	Route *rt = nullptr;
	int index_route = this->ui.cb_routes->currentIndex();
	Project * prj = get_current_project();
	if (prj != nullptr && index_route != -1)
	{
		rt = prj->get_proute(index_route);
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

void WMain::on_current_project_changed()
{
	//QStringList rts = ;
	this->ui.cb_routes->clear();
	Project *prj = this->get_current_project();
	if (prj != nullptr)
		this->ui.cb_routes->addItems(prj->get_routes_name());
}

void WMain::on_setting_triggered()
{
	SettingDialog st(this);
	st.exec();
}

void WMain::on_about_triggered()
{
	QMessageBox msgBox;
	QString about = "About program\n";
	about += "Program calculates the values of compensations\'s possibilities of pipelines \nVersion: 1.0\nAuthor: Ngo Gia Viet,\
Postgraduate student of department \'Shipbuilding and Marine Engineering Energy Complexes\', ASTU";
	msgBox.setText(about);
	msgBox.exec();
}

void WMain::on_action_open()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open"));
	if (!filename.isEmpty())
	{
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
		QTextStream in(&file);
		
		int size = 0, i = 0;
		in >> size;
		this->projects.clear();		
		ui.cb_projects->clear();
		ui.cb_routes->clear();
		for (i = 0; i < size; ++i)
		{
			this->projects.append(Project());
			this->projects[i].load_from_stream(in);
			ui.cb_projects->addItem(projects[i].get_name());
		}

		file.close();

	}
}

void WMain::on_action_save()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save"));
	if (!filename.isEmpty())
	{
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream out(&file);

		out << this->projects.count() << endl;
		for (int i = 0; i < this->projects.count(); ++i)
		{
			this->projects[i].save_to_stream(out);
		}

		file.close();
	}
}

void WMain::on_action_import()
{

}

void WMain::on_action_exit()
{

}

void WMain::on_current_route_changed()
{
	Route * rt = this->get_current_route();
	if (rt != nullptr)
	{
		ui.number_of_straight_sections->setText(QString::number(rt->count_number_of_straight_sections()));
		ui.date_creation->setText(rt->get_dt_creation().toString("hh:mm dd.MM.yyyy"));
		ui.date_change->setText(rt->get_dt_last_change().toString("hh:mm dd.MM.yyyy"));
	}
	else
	{
		ui.date_creation->setText("");
		ui.date_change->setText("");
	}
}
