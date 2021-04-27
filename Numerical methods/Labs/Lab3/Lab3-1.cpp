#include "libs.h"

double w(vector<double> x, double x_et, int n)
{
	double w = 1;
	for (int i = 0; i < n;++i)
		w *= (x_et - x[i]);
	return w;
}

double w_diff(vector<double> x, double x_et, int n, int i)
{
	double w_diff = 1;
	for (int k = 0; k < n; ++k)
	{
		if (k != i)
			w_diff *= x[i] - x[k];
	}
	return w_diff;
}

double Lagrange(vector<double> x, double x_et, vector <double> y,  int n)
{
	for (int i = 0; i < n; ++i)
		y[i] = tan(x[i]) + x[i]; 

	vector <double> fu;
	fu.resize(n, 0);
	for (int i = 0; i < n; ++i)
		fu[i] = y[i] / w_diff(x, x_et, n, i);

	vector <double> fufufu;
	fufufu.resize(n, 0);
	for (int i = 0; i < n; ++i)
		fufufu[i] = x_et-x[i];

	cout << endl;
	cout << setw(3) << "i" << '|' << setw(8) << "x(i)" << '|' << setw(8) << "f(i)" << '|' << setw(14) << "w_diff(x(i))" << '|' << setw(18) << "f(i)/w_diff(x(i))" << '|' << setw(8) << "X*-x(i)" << endl;
	for (int i = 0; i < n; ++i)
		cout << setw(3) << i << '|' << setw(8) << x[i] << '|' << setw(8) << y[i] << '|' << setw(14) << w_diff(x, x_et, n, i) << '|' << setw(18) << fu[i] << '|' << setw(8) << fufufu[i] << endl;

	cout << endl;
	double res = 0;
	for (int i = 0; i < n; ++i)
		res += y[i] * w(x, x_et, n) / (x_et - x[i]) / w_diff(x, x_et, n, i);
	cout << "L(X*) = "<<res << endl;
	double eps = 0;
	eps = abs(res - tan(x_et) - x_et);
	cout << "Абсолютная погрешность: " << eps << endl;
	return res;

	
}

double f_1(vector<double> x, vector <double> y, int n, int i, int j)
{
	double f_1 = 0;
	f_1 = (y[i] - y[j]) / (x[i] - x[j]);
	return f_1;
}

double f_2(vector<double> x, vector <double> y, int n, int i, int j, int k)
{
	double f_2 = 0;
	f_2 = (f_1(x, y, n, i, j) - f_1(x, y, n, j, k)) / (x[i] - x[k]);
	return f_2;
}

double f_3(vector<double> x, vector <double> y, int n, int i, int j, int k, int l)
{
	double f_3 = 0;
	f_3 = (f_2(x, y, n, i, j, k) - f_2(x, y, n, j, k, l)) / (x[i] - x[l]);
	return f_3;
}



double Newton(vector<double> x, double x_et, vector <double> y, int n)
{
	cout << endl;
	cout << setw(3) << "i" << '|' << setw(8) << "x(i)" << '|' << setw(8) << "f(i)" << '|' << setw(21) << "f(x(i),x(i+1))" << '|' << setw(18) << "f(x(i),x(i+1),x(i+2))" << '|' << setw(18) << "f(x(i),x(i+1),x(i+2),x(i+3))" << endl;
	
	cout << setw(3) << 0 << '|' << setw(8) << x[0] << '|' << setw(8) << y[0] << '|' << setw(22) << '|' << setw(22) << '|' << endl;
	cout << setw(22) << '|' << setw(21) << f_1(x, y, n, 0, 0 + 1) << '|' << setw(22) << '|' << setw(22) << endl;

	cout << setw(3) << 1 << '|' << setw(8) << x[1] << '|' << setw(8) << y[1] << '|' << setw(22) << '|' << setw(21) << f_2(x, y, n, 0, 1, 2) << '|' << endl;
	cout << setw(22) << '|' << setw(21) << f_1(x, y, n, 1, 1 + 1) << '|' << setw(22) << '|' << setw(22) << f_3(x, y, n, 0, 1, 2, 3) << endl;

		cout << setw(3) << 2 << '|' << setw(8) << x[2] << '|' << setw(8) << y[2] << '|' << setw(22) << '|' << setw(21) << f_2(x, y, n, 1, 2, 3) << '|' << endl;
		cout << setw(22) << '|' << setw(21) << f_1(x, y, n, 2, 2 + 1) << '|' << setw(22) << '|' << endl;

		cout << setw(3) << 3 << '|' << setw(8) << x[3] << '|' << setw(8) << y[3] << '|' << endl;
		cout << endl;
	
		
	
	double P = 0;
	P = y[0] + (x_et - x[0])*f_1(x, y, n, 1, 0) + (x_et - x[0])*(x_et - x[1])*f_2(x, y, n, 0, 1, 2) + (x_et - x[0])*(x_et - x[1])*(x_et - x[2])*f_3(x, y, n, 0, 1, 2, 3);
	cout<<"P(X*) = " << P << endl;
	double eps = 0;
	eps = abs(P - tan(x_et) - x_et);
	cout << "Абсолютная погрешность: " << eps << endl;

	return P;
	
}

void Interpol_main()
{
	 
	int n = 4;
	double x_et = 3*M_PI/16;
	vector <double> x, y;
	x.resize(n, 0);
	y.resize(n, 0);
	
	x[1] = M_PI / 8;
	x[2] = 2 * M_PI / 8;
	x[3] = 3 * M_PI / 8;

	for (int i = 0; i < n; ++i)
		y[i] = tan(x[i]) + x[i];

	cout << "Интерполяционный многочлен Лагранжа" << endl;
	Lagrange(x, x_et, y, n);
	cout << "__________________________________________________________________________________________________" << endl;
	cout << "Интерполяционный многочлен Ньютона" << endl;
	Newton(x, x_et, y, n);
}
