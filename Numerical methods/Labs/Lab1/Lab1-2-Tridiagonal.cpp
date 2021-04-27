#include "libs.h"

vector <double> a, b, c, d, X;

double Q(int i, double P_prev, double Q_prev)
{
	if (i == 0)
		return d[0] / b[0];
	
	return
		(d[i] - a[i] * Q_prev) / (b[i] + a[i] * P_prev);
}

double P(int i, double P_prev)
{
	if (i == 0)
		return -c[0] / b[0];
	
	return
		-c[i] / (b[i] + a[i] * P_prev);
}

double get_X(int i, double P_prev, double Q_prev, int n)
{
	if (i == n - 1)
	{
		double Qfinal = Q(i, P_prev, Q_prev);
		cout << "P[" << i + 1 << "] = 0, Q[" << i + 1 << "] = " << Qfinal << endl;
		X[i] = Qfinal;
		return Qfinal;
	}

	double Ptec = P(i, P_prev);
	double Qtec = Q(i, P_prev, Q_prev);
	cout << "P[" << i + 1 << "] = " << Ptec;
	cout << ", Q[" << i + 1 << "] = " << Qtec << endl;

	X[i] = Ptec * get_X(i + 1, Ptec, Qtec, n) + Qtec;
	return X[i];
}

void Tridiagonal_main()
{
	int n;
	ifstream test("test2-Tridiagonal.txt");
	test >> n; 
	
	a.resize(n, 0);
	b.resize(n, 0);
	c.resize(n, 0);
	d.resize(n, 0);
	X.resize(n, 0);
	for (int i = 0; i < n; ++i)
	{
		test >> a[i];
		test >> b[i];
		test >> c[i];
		test >> d[i];
	}

	X[0] = get_X(0, 0, 0, n);
	cout << endl;
	for (int i = 0; i < n; ++i)
		cout << "X[" << i+1 << "] = " << X[i] << endl;
	
	cout << endl << endl;
	test.close();
}