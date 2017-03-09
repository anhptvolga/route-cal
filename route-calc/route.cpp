#include "route.h"

Route::Route()
{
}

Route::Route(QString name)
{
	this->name = name;
	this->points.append(Point(0,0,0));
	this->isHasParallel = false;
}

Route::~Route()
{

}

QVector<Point> Route::get_points()
{
	return this->points;
}

void Route::update_points(QVector<Point> pts) 
{
	this->points = pts;
}



void Route::calcuate()
{
	this->isHasParallel = false;
	if (this->points.count() > 1)
	{
		// 2.
		Vector v12(points[0], points[1]);
		// 3.		
		vtsafter.resize(this->free_indexs.count()+1);
		vtsafter[0] = v12;
		for (int i = 0; i < this->free_indexs.count(); ++i)
		{
			// free_indexs diem nhap vao tinh tu 1
			vtsafter[i+1] = Vector(points[free_indexs[i]-1], points[free_indexs[i]]);
		}
		// 4.		
		for (int i = 0; i < vtsafter.count() - 1; ++i)
		{
			for (int j = i+1; j < vtsafter.count(); ++j)
			{
				bool a = vtsafter[i].is_parallel(vtsafter[j]);
				if (vtsafter[i].is_parallel(vtsafter[j]))
				{
					DetailPar detail;
					detail.i = i;
					detail.j = j;					
					// 5.
					// 5.a.
					double leni = vtsafter[i].get_len();
					Vector n1(vtsafter[i].get_x()/leni, vtsafter[i].get_y()/leni, vtsafter[i].get_z()/leni);
					// 5.b.
					Vector deltaT(i == 0 ? points[0] : points[free_indexs[i-1]-1],
						points[free_indexs[j-1]]);
					double L1 = deltaT.get_x()*n1.get_x() + deltaT.get_y()*n1.get_y() + deltaT.get_z()*n1.get_z();					
					double R1 = sqrt(deltaT.get_x()*deltaT.get_x() + deltaT.get_y()*deltaT.get_y() + deltaT.get_z()*deltaT.get_z() - L1*L1);
					Vector vR1(deltaT.get_x() - L1 * n1.get_x(),
						deltaT.get_y() - L1 * n1.get_y(),
						deltaT.get_z() - L1 * n1.get_z() );
					Vector ve1(vR1.get_x()/R1, vR1.get_y()/R1, vR1.get_z()/R1);
					Vector vu1(n1.get_y()*ve1.get_z() - n1.get_z()*ve1.get_y(),
								n1.get_z()*ve1.get_x() - n1.get_x()*ve1.get_z(),
								n1.get_x()*ve1.get_y() - n1.get_y()*ve1.get_x());
					// Saving
					detail.vn = n1;
					detail.delta_T = deltaT;
					detail.L = L1;
					detail.R = R1;
					detail.vR = vR1;
					detail.ve = ve1;
					detail.vu = vu1;
					this->details.append(detail);
				}
			}
		}
		// 6. Calculate delta S
		double sum_ux = 0, sum_uy = 0, sum_uz = 0;
		double sum_ex = 0, sum_ey = 0, sum_ez = 0;
		for (int i = 0; i < details.count(); ++i)
		{
			if (abs(details[i].R) > 0.000000000001)
			{
				this->isHasParallel = true;
				sum_ux += details[i].R * details[i].vu.get_x();
				sum_uy += details[i].R * details[i].vu.get_y();
				sum_uz += details[i].R * details[i].vu.get_z();

				sum_ex += details[i].ve.get_x();
				sum_ey += details[i].ve.get_y();
				sum_ez += details[i].ve.get_z();
			}
		}
		if (isHasParallel)
		{
			double lmx = sin(-Setting::Instance()->limit_angle()) * sum_ux + (1-cos(Setting::Instance()->limit_angle()))*sum_ex;
			double lmy = sin(-Setting::Instance()->limit_angle()) * sum_uy + (1-cos(Setting::Instance()->limit_angle()))*sum_ey;
			double lmz = sin(-Setting::Instance()->limit_angle()) * sum_uz + (1-cos(Setting::Instance()->limit_angle()))*sum_ez;
			double ulmx = sin(-Setting::Instance()->limit_angle()) * sum_ux + (1-cos(Setting::Instance()->limit_angle()))*sum_ex;
			double ulmy = sin(-Setting::Instance()->limit_angle()) * sum_uy + (1-cos(Setting::Instance()->limit_angle()))*sum_ey;
			double ulmz = sin(-Setting::Instance()->limit_angle()) * sum_uz + (1-cos(Setting::Instance()->limit_angle()))*sum_ez;
		
			this->max_sx = max(lmx, ulmx);
			this->max_sy = max(lmy, ulmy);
			this->max_sz = max(lmz, ulmz);
			this->min_sx = min(lmx, ulmx);
			this->min_sy = min(lmy, ulmy);
			this->min_sz = min(lmz, ulmz);
			if (sum_ex != 0)
			{
				double t = sum_ux / sum_ex;
				this->max_sx = max(this->max_sx, 
					max(sin(t)*sum_ux + (1-cos(t))*sum_ex, sin(-t)*sum_ux + (1-cos(t))*sum_ex));
				this->min_sx = min(this->min_sx, 
					min(sin(t)*sum_ux + (1-cos(t))*sum_ex, sin(-t)*sum_ux + (1-cos(t))*sum_ex));
			}
			if (sum_ey != 0)
			{
				double t = sum_uy / sum_ey;
				this->max_sy = max(this->max_sy, 
					max(sin(t)*sum_uy + (1-cos(t))*sum_ey, sin(-t)*sum_uy + (1-cos(t))*sum_ey));
				this->min_sy = min(this->min_sy, 
					min(sin(t)*sum_uy + (1-cos(t))*sum_ey, sin(-t)*sum_uy + (1-cos(t))*sum_ey));
			}
			if (sum_ez != 0)
			{
				double t = sum_uz / sum_ez;
				this->max_sz = max(this->max_sz, 
					max(sin(t)*sum_uz + (1-cos(t))*sum_ez, sin(-t)*sum_uz + (1-cos(t))*sum_ez));
				this->min_sz = min(this->min_sz, 
					min(sin(t)*sum_uz + (1-cos(t))*sum_ez, sin(-t)*sum_uz + (1-cos(t))*sum_ez));
			}
		}
	}
	else
	{
		// TODO: not enough points
	}
}

void Route::set_free_indexs(QVector<int> frindexs)
{
	this->free_indexs = frindexs;
}

void Route::set_name(QString value)
{
	this->name = value;
}

QString Route::get_name()
{
	return this->name;
}

bool Route::can_calculate()
{
	return  this->points.count() > 2 && !this->free_indexs.isEmpty();
}

void Route::write_detail_to_file(QString filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);

	out << "Number of lines: " << this->points.count() - 1 << endl;
	out << "Vector12: " << vtsafter[0].to_string() << endl;
	out << "------------------------------" << endl;
	out << "3. Calculate vector" << endl;
	// print out vectors
	for (int i = 0; i < vtsafter.count(); ++i){
		out << "	" << i+1 << ". " << vtsafter[i].to_string()
			<< " Points: (" << (i == 0 ? 1 : free_indexs[i-1]) << "; " << (i == 0 ? 2 : free_indexs[i-1]+1) << ") " << endl;
	}
	// 4.
	out << "------------------------------" << endl;
	out << "4. Calculate parallel" << endl;

	for (int k = 0; k < this->details.count(); ++k)
	{
		if (abs(details[k].R) > 0.0000000000001)
		{						
		out << "Parallel: " << details[k].i +1 << ", " << details[k].j+1
			<< " Points: (" << (details[k].i == 0 ? 1 : free_indexs[details[k].i-1]) << "; " << (details[k].i == 0 ? 2 : free_indexs[details[k].i-1]+1) << ") "
			<< " Points: (" << (details[k].j == 0 ? 1 : free_indexs[details[k].j-1]) << "; " << (details[k].j == 0 ? 2 : free_indexs[details[k].j-1]+1) << ")" << endl;
		out << "	vector n1: " << details[k].vn.to_string() << endl;
		out << "	vector delta_T: " << details[k].delta_T.to_string() << endl;
		out << "	L1 = " << details[k].L << endl;
		out << "	R1 = " << details[k].R << endl;
		out << "	vector R: " << details[k].vR.to_string() << endl;
		out << "	vector e: " << details[k].ve.to_string() << endl;
		out << "	vector u: " << details[k].vu.to_string() << endl;
		}
		else
		{
			out << "	R = 0. Rejected." << endl;
		}
	}
	if (isHasParallel)
	{
		out << "---------- 6 ------------" << endl;
		out << "Ox: " << endl
			<< "	Max: " << this->max_sx << endl
			<< "	Min: " << this->min_sx << endl;
		out << "Oy: " << endl
			<< "	Max: " << this->max_sy << endl
			<< "	Min: " << this->min_sy << endl;	
		out << "Oz: " << endl
			<< "	Max: " << this->max_sz << endl
			<< "	Min: " << this->min_sz << endl;

		//////////////////////////////////////////////////////////////////////////
		// 7.
		out << "---------- 7 ------------" << endl;
		if (abs(this->max_sx)-0 < 0.0000000001 && abs(this->min_sx)-0 < 0.0000000001) 
		{
			out << "Ox: "
				<< "	Field of compensations\' possibilities: 0" << endl;
		}
		else
		{
			out << "Ox: "
				<< "	Field of compensations\' possibilities: from " << this->min_sx << " to " << this->max_sx << endl;
		}

		if (100 - min(max_sx, abs(min_sx)) > 0) { 
			out << "	Note: appoint overdimension: delta_L = " << 100 - min(max_sx, abs(min_sx)) << endl;
		} else {
			out << "	Note: don\'t appoint overdimension." << endl;
		}
		//----------
		if (abs(max_sy)-0 < 0.0000000001 && abs(min_sy)-0 < 0.0000000001) 
		{
			out << "Oy: "
				<< "	Field of compensations\' possibilities: 0" << endl;
		}
		else
		{
			out << "Oy: "
				<< "	Field of compensations\' possibilities: from " << min_sy << " to " << max_sy << endl;
		}

		if (100 - min(max_sy, abs(min_sy)) > 0) { 
			out << "	Note: appoint overdimension: delta_L = " << 100 - min(max_sy, abs(min_sy)) << endl;
		} else {
			out << "	Note: don\'t appoint overdimension." << endl;
		}
		//----------
		if (abs(max_sz)-0 < 0.0000000001 && abs(min_sz)-0 < 0.0000000001) 
		{
			out << "Oz: "
				<< "	Field of compensations\' possibilities: 0" << endl;
		}
		else
		{
			out << "Oz: "
				<< "	Field of compensations\' possibilities: from " << min_sz << " to " << max_sz << endl;
		}
		if (100 - min(max_sz, abs(min_sz)) > 0) { 
			out << "	Note: appoint overdimension: delta_L = " << 100 - min(max_sz, abs(min_sz)) << endl;
		} else {
			out << "	Note: don\'t appoint overdimension." << endl;
		}
	}
	file.close();
}

/*
QFile file("out.txt");
if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	return;

QTextStream out(&file);
for (int i = 0; i < this->points.count(); ++i) 
{
	out << points[i].x << ' ' 
		<< points[i].y << ' ' 
		<< points[i].z << ' ' 
		<< "\n";
}
file.close();
*/