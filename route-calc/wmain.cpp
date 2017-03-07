#include "wmain.h"

WMain::WMain(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// connect signals and slots
	connect(ui.bt_add_project, SIGNAL(clicked()), this, SLOT(on_add_project_clicked()));
	connect(ui.bt_delete_project, SIGNAL(clicked()), this, SLOT(on_del_project_clicked()));
	connect(ui.bt_rename_project, SIGNAL(clicked()), this, SLOT(on_ren_project_clicked()));
	
	connect(ui.bt_add_route, SIGNAL(clicked()), this, SLOT(on_add_route_clicked()));
	connect(ui.bt_delete_route, SIGNAL(clicked()), this, SLOT(on_del_route_clicked()));
	connect(ui.bt_rename_route, SIGNAL(clicked()), this, SLOT(on_ren_route_clicked()));
	
	connect(ui.bt_calculate, SIGNAL(clicked()), this, SLOT(on_calc_clicked()));

	connect(ui.bt_save_text, SIGNAL(clicked()), this, SLOT(on_save_file_clicked()));

}

WMain::~WMain()
{

}

void WMain::on_add_project_clicked() 
{

}

void WMain::on_del_project_clicked()
{

}

void WMain::on_ren_project_clicked()
{

}

void WMain::on_add_route_clicked()
{

}

void WMain::on_del_route_clicked()
{

}

void WMain::on_ren_route_clicked()
{

}

void WMain::on_calc_clicked()
{

}

void WMain::on_save_file_clicked()
{

}
