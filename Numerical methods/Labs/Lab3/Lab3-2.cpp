#include "libs.h"

vector <double> x, y, a, b, e, d, c, c_i;

double h_i(vector<double>x, int i)
{
	double h_i = 0;
	h_i = x[i] - x[i - 1];
	return h_i;
}

//Решение СЛАУ
double Q(int i, double P_prev, double Q_prev, vector <double> d, vector <double> b, vector <double> a)
{
	if (i == 0)
		return d[0] / b[0];

	return
		(d[i] - a[i] * Q_prev) / (b[i] + a[i] * P_prev);
}

double P(int i, double P_prev, vector <double> e, vector <double> b, vector <double> a)
{
	if (i == 0)
		return -e[0] / b[0];

	return
		-e[i] / (b[i] + a[i] * P_prev);
}

double get_c(int i, double P_prev, double Q_prev, int k, vector <double> a, vector <double> b, vector <double> d, vector<double> e)
{
	if (i == k - 1)
	{
		double Qfinal = Q(i, P_prev, Q_prev, d,b,a);
		c[i] = Qfinal;
		return Qfinal;
	}

	double Ptec = P(i, P_prev, e,b,a);
	double Qtec = Q(i, P_prev, Q_prev, d, b, a);

	c[i] = Ptec * get_c(i + 1, Ptec, Qtec, k, a,b,d,e) + Qtec;
	return c[i];
}
//--------

double Splaine(vector<double> x, vector<double> y, vector<double> c_i, double x_et, int n)
{

	vector <double> a_i, b_i, d_i;
	a_i.resize(n, 0);
	b_i.resize(n, 0);
	d_i.resize(n, 0);

	
	for (int i = 1; i < n; ++i)
	{
		if (i < n - 1)
		{
			a_i[i] = y[i - 1];
			b_i[i] = (y[i] - y[i - 1]) / h_i(x, i) - h_i(x, i)*(c_i[i + 1] + 2 * c_i[i]) / 3;
			d_i[i] = (c_i[i + 1] - c_i[i]) / (3 * h_i(x, i));
		}
		else
		{
			a_i[i] = y[i - 1];
			b_i[i] = y[i] - y[i - 1] / h_i(x, i) - 2 * h_i(x, i)*c_i[i] / 3;
			d_i[i] = (-1)*c_i[i] / (3 * h_i(x, i));
		}

	}

	cout << endl;

	cout << setw(3) << "i" << "|" << setw(16) << "[x[i - 1], x[i]]" << "|" << setw(10) << "a_i" << "|" << setw(10) << "b_i" << "|" << setw(10) << "c_i" << "|" << setw(10) << "d_i" ;
	cout << endl;
	for (int i = 1; i < n; ++i)
	{
		cout << setw(3) << i << "|" << setw(5) << "[" << x[i - 1] << "," << setw(6) << x[i] << "]" << "|" << setw(10) << a_i[i] << "|" << setw(10) << b_i[i] << "|" << setw(10) << c_i[i] << "|" << setw(10) << d_i[i] << endl;
	}

	cout << endl;

	cout << "X=1.5 принадледит отрезку [0.9 ; 1.8], на этом отреке функция представляется кубическим сплайном: " << endl;

	double f = 0;
	f = a_i[2] + b_i[2] * (x_et - x[1]) + c_i[2] * pow((x_et - x[1]), 2) + d_i[2]*pow((x_et - x[1]), 3);
	cout << "f(1.5) = " << f << endl;
	return f;

}

void Splaine_main()
{
	 
	int n = 5;
	double x_et = 1.5;
	int k = 3;
	x.resize(n, 0);
	y.resize(n, 0);
	a.resize(k, 0);
	b.resize(k, 0);
	e.resize(k, 0);
	c.resize(k, 0);
	d.resize(k, 0);
	c_i.resize(n, 0);
	
	x[0] = 0.0;
	x[1] = 0.9;
	x[2] = 1.8;
	x[3] = 2.7;
	x[4] = 3.6;
	y[0] = 0.0;

	y[1] = 0.72235;
	y[2] = 1.5609;
	y[3] = 2.8459;
	y[4] = 7.7275;
	
	b[0] = 2 * (h_i(x, 1) + h_i(x, 2));
	e[0] = h_i(x, 2);
	d[0] = 3 * (((y[2] - y[1]) / h_i(x, 2)) - ((y[1] - y[0]) / h_i(x, 1)));

	a[1] = h_i(x, 2);
	b[1] = 2 * (h_i(x, 2) + h_i(x, 3));
	e[1] = h_i(x, 3);
	d[1] = 3 * (((y[3] - y[2]) / h_i(x, 3)) - ((y[2] - y[1]) / h_i(x, 2)));
		 
	a[2] = h_i(x, 3);
	b[2] = 2 * (h_i(x, 3) + h_i(x,4));
	d[2] = 3 * (((y[4] - y[3]) / h_i(x, 4)) - ((y[3] - y[2]) / h_i(x, 3)));

	c[0] = get_c(0, 0, 0,k, a,b,d,e);
	cout << endl;
	for (int i = 0; i < k; ++i)
		cout << "c[" << i + 1 << "] = " << c[i] << endl;

	c_i[2] = c[0];
	c_i[3] = c[1];
	c_i[4] = c[2];
	
	Splaine(x, y, c_i, x_et, n);
}