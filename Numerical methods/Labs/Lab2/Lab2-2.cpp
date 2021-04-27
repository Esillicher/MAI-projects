#include "libs.h";

double errorPassed(double x1k, double x2k, double x1_prev, double x2_prev, int k, double eps)
{
	double eps1 = abs(x1k - x1_prev);
	double eps2 = abs(x2k - x2_prev);

	if (eps1 >= eps2)
	{
		double eps_k = eps1;
	}
	
	double eps_k = eps2;
	return eps_k;
}

double det(vector <vector <double>> &A1)
{
	double det = 1;
	for (int i = 0; i < 2; ++i)
		det *= A1[i][i];
	return det;
}

double Newton(double x1_prev, double x2_prev, int k, double eps)
{
	double x1k = 0;
	double x2k = 0;

	if (k == 0)
	{
		x1_prev = 0.8;
		x2_prev = 1.75;
		return Newton(x1_prev, x2_prev, k + 1, eps);
	}

	int n = 2;
	vector <vector<double>> A1, A2, Jac;
	A1.resize(n);
	A2.resize(n);
	Jac.resize(n);
	for (int i = 0; i < n; ++i)
	{
		A1[i].resize(n, 0);
		A2[i].resize(n, 0);
		Jac[i].resize(n, 0);
	}

	double f1 = x1_prev - cos(x2_prev) - 1;
	double f2 = x2_prev - sin(x1_prev) - 1;
	double f1_diff_x1 = 1;
	double f1_diff_x2 = sin(x2_prev);
	double f2_diff_x1 = -cos(x1_prev);
	double f2_diff_x2 = 1;
	
	A1[0][0] = f1;
	A1[1][0] = f2;
	A1[0][1] = f1_diff_x2;
	A1[1][1] = f2_diff_x2;
	
	A2[0][0] = 	f1_diff_x1; 
	A2[1][0] = f2_diff_x1; 
	A2[0][1] = f1;
	A2[1][1] = f2;

	Jac[0][0] = f1_diff_x1;
	Jac[0][1] = f1_diff_x2;
	Jac[1][0] = f2_diff_x1;
	Jac[1][1] = f2_diff_x2;

	x1k = x1_prev - (det(A1) / det(Jac));
	x2k = x2_prev - (det(A2) / det(Jac));

	//cout << "eps(" << k << ") = ";
	if (errorPassed(x1k, x2k, x1_prev, x2_prev, k, eps) <= eps)
	{
		cout << setw(3) << k << "|" << setw(8) << x1k << "," << setw(8) << x2k << "|" << endl;
		cout << "eps(" << k << ") = " << fixed << setprecision(8) << errorPassed(x1k, x2k, x1_prev, x2_prev, k, eps);
		cout << " <= " << eps << endl << "Решение найдено на шаге " << k << '.' << endl << "x1:" << x1k << "	x2:" << x2k << endl;
		return x1k, x2k;
		x1_prev = 0;
		x2_prev = 0;
	}
	else
	{
		cout << setw(3) << k << "|" << setw(8) << x1k << "," << setw(8) << x2k << "|" << setw(8) << f1_diff_x1 << "," << setw(9) << f2_diff_x1 << "|" << setw(8) << f1_diff_x2 << "," << setw(9) << f2_diff_x2 << "|" << setw(11) << det(A1) << "|" << setw(11) << det(A2) << "|" << setw(2) << det(Jac) << endl;
		x1_prev = x1k;
		x2_prev = x2k;
		return Newton(x1_prev, x2_prev, k + 1, eps);
	}
}

double errorPassedSI(double x1k, double x2k, double x1_prev, double x2_prev, int k, double eps, double q)
{

	double eps1 = abs(x1k - x1_prev);
	double eps2 = abs(x2k - x2_prev);

	if (eps1 >= eps2)
	{
		double ep = eps1;
	}


	double ep = eps2;

	double eps_k = (q / (1 - q))*ep;

	return eps_k;
		
}

double SimpleIteration(double x1_prev, double x2_prev, int k, double eps, double q)
{
	double x1k = 0;
	double x2k = 0;
	
	if (k == 0)
	{
		x1_prev = 0.8;
		x2_prev = 1.75;
		return SimpleIteration(x1_prev, x2_prev, k + 1, eps, q);
	}

	x1k = cos(x2_prev) + 1; //phi1
	x2k = sin(x1_prev) + 1; //phi2

	//cout << "eps(" << k << ") = ";
	if (errorPassedSI(x1k, x2k, x1_prev, x2_prev, k, eps, q) <= eps)
	{
		cout << setw(3) << k << "|" << setw(8) << x1k << "|" << setw(8) << x2k << "|" << endl;
		cout << "eps(" << k << ") = " << errorPassedSI(x1k, x2k, x1_prev, x2_prev, k, eps, q) << " <= " << eps << endl << "Решение найдено на шаге " << k << '.' << endl << "x1:" << x1k << "	x2:" << x2k << endl;
		return x1k, x2k;
	}
	else
	{
		cout << setw(3) << k << "|" << setw(9) << x1k << "|" << setw(9) << x2k << "|" << setw(16) << cos(x2_prev) + 1 <<  "|" << setw(16) << sin(x1_prev) + 1 << "|" << endl;
		//cout << " > " << eps << endl;
		x1_prev = x1k;
		x2_prev = x2k;
		return SimpleIteration(x1_prev, x2_prev, k + 1, eps, q);
	}


}

void su_main()
{
	int k = 0;
	double x1_prev = 0;
	double x2_prev = 0;
	double q = 0.9;
	double eps = 0.01;
	cout << "Заданная точность: " << eps << endl;

	cout << "Метод Ньютона: " << endl;
	cout << "===============================================================================================" << endl;
	cout << setw(3) << "k" << "|" << setw(9) << "x1k," << setw(8) << "x2k" << "|" << setw(18) << "df1/dx1, df1/dx2" << "|" << setw(18) << "df2/dx2, df2/dx2" << "|" << setw(11) << "detA1" << "|" << setw(11) << "detA2" << "|" << setw(3) << "detJ" << endl;
	
	Newton(x1_prev, x2_prev, k, eps);
	cout << endl;
	cout << "Метод простых итераций: " << endl;
	cout << "===============================================================================================" << endl;
	cout << setw(3) << "k" << "|" << setw(9) << "x1k" << "|" << setw(9) << "x2k" << "|" << setw(16) << "phi1( x1k, x2k )" << "|" << setw(16) << "phi2( x1k, x2k )" << "|" << endl;
	SimpleIteration(x1_prev, x2_prev, k, eps, q);

}

