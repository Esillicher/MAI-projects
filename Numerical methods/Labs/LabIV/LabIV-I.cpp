#include "libs.h"
//вариант 23

double ff(double x, double y, double z)
{
	return z;
}
double gg(double x, double y, double z)
{
	return (-x * z +  y + 3*x*x ) / (x*x);
}

vector <double> RRR(vector <double> y, vector <double> y2, vector <double> y_ist, vector <double> R)
{
	for (int i = 0; i < 6; ++i)
	{
		R[i] = y[i] + (y[i] - y2[i]) / (pow(2, 4) - 1);
	}

	cout << "Оценка Р-Р-Р" << endl;
	for (int i = 0; i < 6; i++){
		cout << R[i] << "\t" << fabs(R[i] - y_ist[i]) << endl;
	}
	cout << endl;
	return R;
}

vector<double> Eiler(vector<double> x, vector<double> y, vector<double> z, vector<double> y_ist, int n, double h)
{
	vector<double> y2, R;
	y2.resize(n, 0);
	R.resize(6, 0);
	y2[0] = 3;

	for (int i = 1; i < n; ++i)
	{
		y[i] = y[i - 1] + h*ff(x[i - 1], y[i - 1], z[i - 1]);
		z[i] = z[i - 1] + h*gg(x[i - 1], y[i - 1], z[i - 1]);
	}	
	return y;
}

vector <double> RK(vector<double> y, vector<double> y_ist, vector<double> x, vector<double> z, double h, double z0, double y0, double x0, int n)
{
	vector<double> K, L;
	K.resize(4, 0);
	L.resize(4, 0);

	for (int i = 1; i < n; ++i)
	{
		K[0] = h*ff(x0, y0, z0);
		L[0] = h*gg(x0, y0, z0);
		K[1] = h*ff(x0 + h / 2, y0 + K[0] / 2, z0 + L[0] / 2);
		L[1] = h*gg(x0 + h / 2, y0 + K[0] / 2, z0 + L[0] / 2);
		K[2] = h*ff(x0 + h / 2, y0 + K[1] / 2, z0 + L[1] / 2);
		L[2] = h*gg(x0 + h / 2, y0 + K[1] / 2, z0 + L[1] / 2);
		K[3] = h*ff(x0 + h, y0 + K[2], z0 + L[2]);
		L[3] = h*gg(x0 + h, y0 + K[2], z0 + L[2]);

		y0 = y0 + (K[0] + 2 * K[1] + 2 * K[2] + K[3]) / 6;
		z0 = z0 + (L[0] + 2 * L[1] + 2 * L[2] + L[3]) / 6;
		x0 = x0 + h;
		y[i] = y0;
		z[i] = z0;
	}
	return y;
}

vector <double> Adams(vector<double> y, vector<double> y_ist, vector<double> x, vector<double> z, double h, double z0, double y0, double x0, int n)
{
	vector<double> K, L;
	K.resize(4, 0);
	L.resize(4, 0);

	for (int i = 1; i < 4; ++i)
	{
		K[0] = h*ff(x0, y0, z0);
		L[0] = h*gg(x0, y0, z0);
		K[1] = h*ff(x0 + h / 2, y0 + K[0] / 2, z0 + L[0] / 2);
		L[1] = h*gg(x0 + h / 2, y0 + K[0] / 2, z0 + L[0] / 2);
		K[2] = h*ff(x0 + h / 2, y0 + K[1] / 2, z0 + L[1] / 2);
		L[2] = h*gg(x0 + h / 2, y0 + K[1] / 2, z0 + L[1] / 2);
		K[3] = h*ff(x0 + h, y0 + K[2], z0 + L[2]);
		L[3] = h*gg(x0 + h, y0 + K[2], z0 + L[2]);

		y0 = y0 + (K[0] + 2 * K[1] + 2 * K[2] + K[3]) / 6;
		z0 = z0 + (L[0] + 2 * L[1] + 2 * L[2] + L[3]) / 6;
		x0 = x0 + h;
				
		y[i] = y0;
		z[i] = z0;
	}
	
	for (int i = 4; i < n; ++i)
	{
	
		z[i] = z[i - 1] + (h / 24)*(55 * gg(x[i - 1], y[i - 1], z[i - 1]) - 59 * gg(x[i - 2], y[i - 2], z[i - 2]) + 37 * gg(x[i - 3], y[i - 3], z[i - 3]) - 9 * gg(x[i - 4], y[i - 4], z[i - 4]));
		y[i] = y[i - 1] + (h / 24)*(55 * ff(x[i - 1], y[i - 1], z[i - 1]) - 59 * ff(x[i - 2], y[i - 2], z[i - 2]) + 37 * ff(x[i - 3], y[i - 3], z[i - 3]) - 9 * ff(x[i - 4], y[i - 4], z[i - 4]));
		
	}
		
	return y;
}

void PartI_main()
{
	int n = 11;
	vector<double> y, y_ist, x, z;
	y.resize(n, 0);
	y_ist.resize(n, 0);
	x.resize(n, 0);
	z.resize(n, 0);
	vector<double> y2, R;
	y2.resize(n, 0);
	R.resize(6, 0);
	y2[0] = 3;

	double h = 0.1;
	double z0 = 2;
	double y0 = 3;
	double x0 = 1;

	x[0] = x0;
	y[0] = y0;
	y_ist[0] = y0;
	z[0] = z0;
	for (int i = 1; i < n; ++i)
	{
		x[i] = x[i - 1] + h;
		y_ist[i] = x[i] * x[i] + x[i] + (1/x[i]);
	}
	// М. Эйлера
	y = Eiler(x, y, z, y_ist, n, h);

	cout << "Метод Эйлера" << endl;
	cout << setw(3) << "i" << "|" << setw(4) << "x" << "|" << setw(14) << "y_k" << "|" << setw(14) << "y_ist" << "|" << setw(14) << "Eps" << "|" << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << setw(3) << i << "|" << setw(4) << x[i] << "|" << setw(14) << y[i] << "|" << setw(14) << y_ist[i] << "|" << setw(14) << fabs(y[i] - y_ist[i]) << "|" << endl;//<< fixed << setprecision(12) 
	}
	cout << endl;

	for (int i = 1; i < 6; ++i)
	{
		y2[i] = y2[i - 1] + 2 * h*ff(x[i - 1], y2[i - 1], z[i - 1]);
		z[i] = z[i - 1] + h*gg(x[i - 1], y2[i - 1], z[i - 1]);
	}

	y2 = Eiler(x, y2, z, y_ist, 6, 2*h);
	R = RRR(y, y2, y_ist, R);

	// М. Р-К
	y = RK(y, y_ist, x, z, h, z0, y0, x0, n);

	cout << "Метод Рунге-Кутта" << endl;
	cout << setw(3) << "k" << "|" << setw(14) << "x" << "|" << setw(14) << "y_k" << "|" << setw(14) << "z_k" << "|" << setw(14) << "y_ист" << "|" << setw(14) << "eps_k" << "|" << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << setw(3) << i << "|" << setw(14) << x[i] << "|" << setw(14) << y[i] << "|" << setw(14) << z[i] << "|" << setw(14) << y_ist[i] << "|" << setw(14) << fixed << setprecision(12) << fabs(y[i] - y_ist[i]) << "|" << endl;

	}
	cout << endl;

	y2 = RK(y2, y_ist, x, z, 2*h, z0, y0, x0, 6);
	R = RRR(y, y2, y_ist, R);

	y = Adams(y, y_ist, x, z, h, z0, y0, x0, n);

	cout << "Метод Адамса" << endl;
	cout << setw(3) << "k" << "|" << setw(14) << "x" << "|" << setw(14) << "y_k" << "|" << setw(14) << "f(x_k,y_k)" << "|" << setw(14) << "y_ист" << "|" << setw(14) << "eps_k" << "|" << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << setw(3) << i << "|" << setw(14) << x[i] << "|" << setw(14) << y[i] << "|" << setw(14) << z[i] << "|" << setw(14) << y_ist[i] << "|" << setw(12) << fixed << setprecision(10) << fabs(y[i] - y_ist[i]) << "|" << endl;
	}cout << endl;

	y2 = Adams(y2, y_ist, x, z, 2 * h, z0, y0, x0, 6);	
	R = RRR(y, y2, y_ist, R);
}
