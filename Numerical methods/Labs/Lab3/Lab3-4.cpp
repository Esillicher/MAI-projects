#include "libs.h"

double left_proisv(vector<double> x, vector<double> y)
{
	double f_diff = 0;
	f_diff = (y[2] - y[1]) / (x[2] - x[1]);
	return f_diff;
}

double right_proisv(vector<double> x, vector<double> y)
{
	double f_diff = 0;
	f_diff = (y[3] - y[2]) / (x[3] - x[2]);
	return f_diff;
}

double double_prec_proisv(vector<double> x, vector<double> y, double x_et)
{
	double f_diff = 0;
	
	f_diff =(  ( ( (y[3] - y[2]) / (x[3] - x[2]) ) - ( (y[2] - y[1]) / (x[2] - x[1]) ) )/ (x[3] - x[1])  ) * (-x[1] - x[2] + 2 * x_et) + ((y[2] - y[1]) / (x[2] - x[1]));
	return f_diff;
}

double double_proisv(vector<double> x, vector<double> y)
{
	double f_diff = 0;
	f_diff = 2 * ((((y[3] - y[2]) / (x[3] - x[2])) - ((y[2] - y[1]) / (x[2] - x[1]))) / (x[3] - x[1]));
	return f_diff;
}

void Proisv_main()
{
	 
	int n;
	double x_et;
	ifstream test("test3-Proisv.txt");
	test >> n;
	test >> x_et;

	vector <double> x, y;

	x.resize(n);
	y.resize(n);
	for (int i = 0; i < n; ++i)
	{
		test >> x[i];
		test >> y[i];
	}

	cout << "X* = "<<x_et << endl;

	cout << "Производные первого порядка точности"  << endl;
	cout << endl;
	cout << "Левосторонняя производная: y`(3) = " << left_proisv(x, y) << endl;
	cout << "Правосторонняя производная: y`(3) = " << right_proisv(x, y) << endl;
	cout << endl;
	cout << "Поизводная второго порядка точности: y`(3) = " << double_prec_proisv(x, y, x_et) << endl;
	cout << endl;
	cout << "Вторая производная: y``(3) = " << double_proisv(x, y) << endl;
}