#include "route.h"

double Setting::accuracy;
double Setting::limit_angle;


Route::Route()
{
}

Route::Route(QString name)
{
	this->name = name;
	this->points.append(Point(0,0,0));
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
	QFile file("out.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	
	// 1. 
	int nlines = this->points.count() - 1;
	out << "Number of lines: " << nlines << endl;

	if (nlines > 0)
	{
		// 2.
		Vector v12(points[0], points[1]);
		out << "Vector12: " << v12.to_string() << endl;
		// 3.
		out << "------------------------------" << endl;
		out << "3. Calculate vector" << endl;
		QVector<Vector> vtsafter(this->free_indexs.count()+1);
		vtsafter[0] = v12;
		for (int i = 0; i < this->free_indexs.count(); ++i)
		{
			// free_indexs diem nhap vao tinh tu 1
			vtsafter[i+1] = Vector(points[free_indexs[i]-1], points[free_indexs[i]]);
		}
		// print out vectors
		for (int i = 0; i < vtsafter.count(); ++i){
			out << "	" << i << ". " << vtsafter[i].to_string()
				<< " Points: (" << (i == 0 ? 1 : free_indexs[i-1]) << "; " << (i == 0 ? 2 : free_indexs[i-1]+1) << ") " << endl;
		}
		// 4.
		out << "------------------------------" << endl;
		out << "4. Calculate parallel" << endl;
		count_parallel = 0;
		for (int i = 0; i < vtsafter.count() - 1; ++i)
		{
			for (int j = i+1; j < vtsafter.count(); ++j)
			{
				bool a = vtsafter[i].is_parallel(vtsafter[j]);
				if (vtsafter[i].is_parallel(vtsafter[j]))
				{
					
					out << "Parallel: " << i << ", " << j
						<< " Points: (" << (i == 0 ? 1 : free_indexs[i-1]) << "; " << (i == 0 ? 2 : free_indexs[i-1]+1) << ") "
						<< " Points: (" << (j == 0 ? 1 : free_indexs[j-1]) << "; " << (j == 0 ? 2 : free_indexs[j-1]+1) << ")" << endl;
					// 5.
					// 5.a.
					double leni = vtsafter[i].get_len();
					Vector n1(vtsafter[i].get_x()/leni, vtsafter[i].get_y()/leni, vtsafter[i].get_z()/leni);
					// 5.b.
					Vector deltaT( points[free_indexs[j-1]], 
						i == 0 ? points[0] : points[free_indexs[i-1]-1] );
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
					if (abs(R1) > 0.0000000000001)
					{
						out << "	vector n1: " << n1.to_string() << endl;
						out << "	vector delta_T: " << deltaT.to_string() << endl;
						out << "	L1 = " << L1 << endl;
						out << "	R1 = " << R1 << endl;
						out << "	vector R: " << vR1.to_string() << endl;
						out << "	vector e: " << vR1.to_string() << endl;
						out << "	vector u: " << vu1.to_string() << endl;
						this->vus.append(vu1);
						this->vns.append(n1);
						this->ves.append(ve1);
						this->vRs.append(R1);
					}
					else
					{
						out << "	R = 0. Rejected." << endl;
					}
				}
			}
		}
		// 6. Calculate delta S
		double sum_ux = 0;
		double sum_uy = 0;
		double sum_uz = 0;
		double sum_ex = 0;
		double sum_ey = 0;
		double sum_ez = 0;
		for (int i = 0; i < vus.count(); ++i)
		{
			sum_ux += vRs[i] * vus[i].get_x();
			sum_uy += vRs[i] * vus[i].get_y();
			sum_uz += vRs[i] * vus[i].get_z();

			sum_ex += ves[i].get_x();
			sum_ey += ves[i].get_y();
			sum_ez += ves[i].get_z();
		}

		double lmx = sin(-Setting::limit_angle) * sum_ux + (1-cos(Setting::limit_angle))*sum_ex;
		double lmy = sin(-Setting::limit_angle) * sum_uy + (1-cos(Setting::limit_angle))*sum_ey;
		double lmz = sin(-Setting::limit_angle) * sum_uz + (1-cos(Setting::limit_angle))*sum_ez;
		
		double ulmx = sin(-Setting::limit_angle) * sum_ux + (1-cos(Setting::limit_angle))*sum_ex;
		double ulmy = sin(-Setting::limit_angle) * sum_uy + (1-cos(Setting::limit_angle))*sum_ey;
		double ulmz = sin(-Setting::limit_angle) * sum_uz + (1-cos(Setting::limit_angle))*sum_ez;

		double max_sx = max(lmx, ulmx);
		double max_sy = max(lmx, ulmx);
		double max_sz = max(lmx, ulmx);
		double min_sx = min(lmx, ulmx);
		double min_sy = min(lmx, ulmx);
		double min_sz = min(lmx, ulmx);
		if (sum_ex != 0)
		{
			double t = sum_ux / sum_ex;
			max_sx = max(max_sx, 
				max(sin(t)*sum_ux + (1-cos(t))*sum_ex, sin(-t)*sum_ux + (1-cos(t))*sum_ex));
			min_sx = min(min_sx, 
				min(sin(t)*sum_ux + (1-cos(t))*sum_ex, sin(-t)*sum_ux + (1-cos(t))*sum_ex));
		}
		if (sum_ey != 0)
		{
			double t = sum_uy / sum_ey;
			max_sy = max(max_sy, 
				max(sin(t)*sum_uy + (1-cos(t))*sum_ey, sin(-t)*sum_uy + (1-cos(t))*sum_ey));
			min_sy = min(min_sy, 
				min(sin(t)*sum_uy + (1-cos(t))*sum_ey, sin(-t)*sum_uy + (1-cos(t))*sum_ey));
		}
		if (sum_ez != 0)
		{
			double t = sum_uz / sum_ez;
			max_sz = max(max_sz, 
				max(sin(t)*sum_uz + (1-cos(t))*sum_ez, sin(-t)*sum_uz + (1-cos(t))*sum_ez));
			min_sz = min(min_sz, 
				min(sin(t)*sum_uz + (1-cos(t))*sum_ez, sin(-t)*sum_uz + (1-cos(t))*sum_ez));
		}
		out << "---------- 6 ------------" << endl;
		out << "Ox: " << endl
			<< "	Max: " << max_sx << endl
			<< "	Min: " << min_sx << endl;
		out << "Oy: " << endl
			<< "	Max: " << max_sy << endl
			<< "	Min: " << min_sy << endl;	
		out << "Oz: " << endl
			<< "	Max: " << max_sz << endl
			<< "	Min: " << min_sz << endl;
		//////////////////////////////////////////////////////////////////////////
		// 7.
		out << "---------- 7 ------------" << endl;
		out << "Ox: "
			<< "	Field of compensations\' possibilities: from " << min_sx << " to " << max_sx << endl;
		if (100 - min(max_sx, abs(min_sx)) > 0) { 
			out << "	Note: appoint overdimension: delta_L = " << 100 - min(max_sx, abs(min_sx)) << endl;
		} else {
			out << "	Note: don\'t appoint overdimension." << endl;
		}

		out << "Oy: "
			<< "	Field of compensations\' possibilities: from " << min_sy << " to " << max_sy << endl;
		if (100 - min(max_sy, abs(min_sy)) > 0) { 
			out << "	Note: appoint overdimension: delta_L = " << 100 - min(max_sy, abs(min_sy)) << endl;
		} else {
			out << "	Note: don\'t appoint overdimension." << endl;
		}

		out << "Oz: "
			<< "	Field of compensations\' possibilities: from " << min_sz << " to " << max_sz << endl;
		if (100 - min(max_sz, abs(min_sz)) > 0) { 
			out << "	Note: appoint overdimension: delta_L = " << 100 - min(max_sz, abs(min_sz)) << endl;
		} else {
			out << "	Note: don\'t appoint overdimension." << endl;
		}
	}
	else
	{
		// TODO: not enough points
	}
	file.close();
}

void Route::set_free_indexs(QVector<int> frindexs)
{
	this->free_indexs = frindexs;
}

QString Route::get_name()
{
	return this->name;
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