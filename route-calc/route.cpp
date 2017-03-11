#include "route.h"

Route::Route()
{
	this->isHasParallel = false;
}

Route::Route(QString name)
{
	this->isHasParallel = false;
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
	this->vtsafter.clear();
	this->details.clear();
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
		this->max_sx = this->max_sy = this->max_sz = 0;
		this->min_sx = this->min_sy = this->min_sz = 0;
		for (int i = 0; i < details.count(); ++i)
		{
			if (abs(details[i].R) > 0.000000000001)
			{
				this->isHasParallel = true;
				calc_max_min(i);
				this->max_sx += details[i].R * details[i].max_sx;
				this->max_sy += details[i].R * details[i].max_sy;
				this->max_sz += details[i].R * details[i].max_sz;
				this->min_sx += details[i].R * details[i].min_sx;
				this->min_sz += details[i].R * details[i].min_sx;
			}
		}
	}
	else
	{
		// TODO: not enough points
	}
}

inline double Route::f(double t, double u, double e)
{
	return sin(t)*u - (1-cos(t))*e;
}

void Route::calc_angle_t(int i, double t)
{
	// Calculate if angle t in range
	if (abs(t) <= Setting::Instance()->limit_angle())
	{
		double value = f(t, details[i].vu.get_x(), details[i].ve.get_x());
		// OX
		if (details[i].max_sx < value)
		{
			details[i].max_sx = value;
			details[i].tmax_x = t;
		}
		if (details[i].min_sx > value)
		{
			details[i].min_sx = value;
			details[i].tmin_x = t;
		}
		// OY
		value = f(t, details[i].vu.get_y(), details[i].ve.get_y());
		if (details[i].max_sy < value)
		{
			details[i].max_sy = value;
			details[i].tmax_y = t;
		}
		if (details[i].min_sy > value)
		{
			details[i].min_sy = value;
			details[i].tmin_y = t;
		}
		// OZ
		value = f(t, details[i].vu.get_z(), details[i].ve.get_z());
		if (details[i].max_sz < value)
		{
			details[i].max_sz = value;
			details[i].tmax_z = t;
		}
		if (details[i].min_sz > value)
		{
			details[i].min_sz = value;
			details[i].tmin_z = t;
		}
	}
}

void Route::calc_max_min(int i)
{
	details[i].max_sx = details[i].max_sy = details[i].max_sz = LONG_MIN;
	details[i].min_sx = details[i].min_sy = details[i].min_sz = LONG_MAX;
	// calculate in limits
	calc_angle_t(i, Setting::Instance()->limit_angle());
	calc_angle_t(i, -Setting::Instance()->limit_angle());
	
	if (details[i].ve.get_x() != 0)
	{
		calc_angle_t(i, atan(details[i].vu.get_x() / details[i].ve.get_x()));
	}
	if (details[i].ve.get_y() != 0)
	{
		calc_angle_t(i, atan(details[i].vu.get_y() / details[i].ve.get_y()));
	}
	if (details[i].ve.get_z() != 0)
	{
		calc_angle_t(i, atan(details[i].vu.get_z() / details[i].ve.get_z()));
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
								
		out << "Parallel: " << details[k].i +1 << ", " << details[k].j+1
			<< " Points: (" << (details[k].i == 0 ? 1 : free_indexs[details[k].i-1]) << "; " << (details[k].i == 0 ? 2 : free_indexs[details[k].i-1]+1) << ") "
			<< " Points: (" << (details[k].j == 0 ? 1 : free_indexs[details[k].j-1]) << "; " << (details[k].j == 0 ? 2 : free_indexs[details[k].j-1]+1) << ")" << endl;
		if (abs(details[k].R) > 0.0000000000001)
		{
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
			<< "	Max: " << this->max_sx << endl;
		//if (abs(max_sx)-0 > 0.0000000001)
		//{
			for (int i = 0; i < details.count(); ++i)
			{
				if (abs(details[i].R) > 0.0000001) out << "		t" << i+1 << " = " << details[i].tmax_x << endl;
			}
		//}
		out << "	Min: " << this->min_sx << endl;
		//if (abs(min_sx)-0 > 0.0000000001)
		//{
			for (int i = 0; i < details.count(); ++i)
			{
				if (abs(details[i].R) > 0.0000001) out << "		t" << i+1 << " = " << details[i].tmin_x << endl;
			}
		//}
		//--------
		out << "Oy: " << endl
			<< "	Max: " << this->max_sy << endl;
		//if (abs(max_sy)-0 > 0.0000000001)
		//{
			for (int i = 0; i < details.count(); ++i)
			{
				if (abs(details[i].R) > 0.0000001) out << "		t" << i+1 << " = " << details[i].tmax_y << endl;
			}
		//}
		out << "	Min: " << this->min_sy << endl;
		//if (abs(min_sy)-0 > 0.0000000001)
		//{
			for (int i = 0; i < details.count(); ++i)
			{
				if (abs(details[i].R) > 0.0000001) out << "		t" << i+1 << " = " << details[i].tmin_y << endl;
			}
		//}
		
		out << "Oz: " << endl
			<< "	Max: " << this->max_sz << endl;
		//if (abs(max_sz)-0 > 0.0000000001)
		//{
			for (int i = 0; i < details.count(); ++i)
			{
				if (abs(details[i].R) > 0.0000001) out << "		t" << i+1 << " = " << details[i].tmax_z << endl;
			}
		//}
		out << "	Min: " << this->min_sz << endl;
		//if (abs(min_sz)-0 > 0.0000000001)
		//{
			for (int i = 0; i < details.count(); ++i)
			{
				if (abs(details[i].R) > 0.0000001) out << "		t" << i+1 << " = " << details[i].tmin_z << endl;
			}
		//}
		//////////////////////////////////////////////////////////////////////////
		// 7.
		out << "---------- 7 ------------" << endl;
		if (abs(this->max_sx) < 0.0000000001 && abs(this->min_sx) < 0.0000000001) 
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
		if (abs(max_sy) < 0.0000000001 && abs(min_sy) < 0.0000000001) 
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
		if (abs(max_sz) < 0.0000000001 && abs(min_sz) < 0.0000000001) 
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

void Route::load_from_stream(QTextStream& in)
{
	QString tmp;
	int size = 0, i = 0;
	int x=0, y=0, z=0;
	in >> tmp;
	this->name = tmp.trimmed();
	
	in >> size;
	this->points.clear();
	for (i = 0; i < size; ++i)
	{
		in >> x >> y >> z;
		points.append(Point(x, y, z));
	}

	in >> size;
	this->free_indexs.clear();
	for (i = 0; i < size; ++i)
	{
		in >> x;
		free_indexs.append(x);
	}
}

void Route::save_to_stream(QTextStream& out)
{
	int i;
	out << this->name << endl;
	
	out << this->points.count() << endl;
	for (i = 0; i < points.count(); ++i)
		out << points[i].get_x() << " "
			<< points[i].get_y() << " "
			<< points[i].get_z() << endl;
	
	out << this->free_indexs.count() << endl;
	for (i = 0; i < free_indexs.count(); ++i)
		out << free_indexs[i] << " ";
	out << endl;
}

int Route::count_number_of_straight_sections()
{
	return this->points.count() - 1;
}

int Route::count_parrallel_pairs()
{
	int res = 0;
	for (int i = 0; i < details.count(); ++i)
	{
		if (abs(details[i].R) > 0.0000000001) ++res;
	}
	return res;
}

double Route::get_max_sx()
{
	return this->max_sx;
}

double Route::get_max_sy()
{
	return this->max_sy;
}

double Route::get_max_sz()
{
	return this->max_sz;
}

double Route::get_min_sx()
{
	return this->min_sx;
}

double Route::get_min_sy()
{
	return this->min_sy;
}

double Route::get_min_sz()
{
	return this->min_sz;
}

bool Route::is_has_parallel()
{
	return this->isHasParallel;
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