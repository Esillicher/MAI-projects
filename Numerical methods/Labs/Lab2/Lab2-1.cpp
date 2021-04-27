#include "libs.h";

/*
double get_f(vector <double> x, int k)
{
	double f = 0;
	f = pow(x[k], 3) - 2 * pow(x[k], 2) - 10 * x[k] + 15;
	return f;
}

double get_f_diff(vector <double> x, int k)
{
	double f_diff = 0;
	f_diff = 3 * pow(x[k], 2) - 4 * x[k] - 10;
	return f_diff;
}

bool errorPassed(vector<double> x, int k, double eps)
{
	double eps_k = abs(x[k] - x[k - 1]);
	cout << fixed << setprecision(5) << eps_k;
	if (eps_k <= eps)
		return true;
	else
		return false;
}

double Newton(vector <double> x, int k, double eps)
{
	if (k == 0)
	{
		x[k] = 1.6;
		return Newton(x, k + 1, eps);
	}
		
			
	x[k] = x[k-1] - (get_f(x, k-1) / get_f_diff(x, k-1));
	cout << "eps(" << k << ") = ";
	if (errorPassed(x, k, eps))
	{
		cout << " <= " << eps << endl << "Решение найдено на шаге " << k << '.' << endl << "X:" << x[k] << endl;
		return x[k];
	}
	else
	{
		cout << " > " << eps << endl;
		return Newton(x, k + 1, eps);
	}
}
*/
//____________________________________________________________________

double get_f(double &xk, int k)
{
	double f = 0;
	f = pow(2,xk) - pow(xk, 2) - 0.5 + 15;
	return f;
}

double get_f_diff(double &xk, int k)
{
	double f_diff = 0;
	f_diff = pow(2, xk)*0.693147180559945309417 - 2 * xk;
	return f_diff;
}

double errorPassed(double xk, double x_prev, int k, double eps)
{ 
	double eps_k = 0;
	eps_k = abs(xk - x_prev);
	//cout << fixed << setprecision(5) << eps_k;
	return eps_k;
	//if (eps_k <= eps)
	//	return true;
	//else
	//	return false;
}

double Newton( double x_prev, int k, double eps)
{
	double xk = 0;

	if (k == 0)
	{
		//xk = 1.6;
		x_prev = 1;
		return Newton(x_prev, k + 1, eps);
	}

	
	xk = x_prev - (get_f(x_prev, k - 1) / get_f_diff(x_prev, k - 1));
	//cout << "eps(" << k << ") = ";
	if (errorPassed(xk, x_prev, k, eps) <= eps)
	{
		cout << setw(3) << k << "|" << setw(9) << xk << "|"  << endl;
		cout << "eps(" << k << ") = " << fixed << setprecision(6) << errorPassed(xk, x_prev, k, eps);
		cout << " <= " << eps << endl << "Решение найдено на шаге " << k << '.' << endl << "X:" << xk << endl;
		return xk;
		x_prev = 0;
	}
	else
	{
		cout << setw(3) << k << "|" << setw(9) << xk << "|" << setw(12) << get_f(xk, k) << "|" << setw(12) << get_f_diff(xk, k) << "|" << setw(12) << -(get_f(xk, k) / get_f_diff(xk, k)) << endl;
		//cout << " > " << eps << endl;
		x_prev = xk;
		return Newton(x_prev, k + 1, eps);
	}
}

double errorPassedSI(double xk, double x_prev, int k, double eps)
{

	double q = 0.2;
	double eps_k = (q / (1 - q))*abs(xk - x_prev);
	return eps_k;
	//if (eps_k <= eps)
	//	return true;
	//else
	//	return false;
}

double get_phi(double x_prev, int k)
{
	double phi = 0;
	phi = (pow(x_prev, 3) - 2 * pow(x_prev, 2) + 15) / 10;
	return phi;
}

double get_phi_diff(double x_prev, int k)
{
	double phi_diff = 0;
	phi_diff = (3 * pow(x_prev, 2) - 4 * x_prev) / 10;
	return phi_diff;
}

void Theorem()
{
	double a = 1.3;
	double b = 1.5;

	double phi_a = 0;
	phi_a = (pow(a, 3) - 2 * pow(a, 2) + 15) / 10;
	
	double phi_b = 0;
	phi_b = (pow(b, 3) - 2 * pow(b, 2) + 15) / 10;
	
	cout << "phi(x) [0;" << phi_b << "] => phi(x) [1.3 ; 1.5] для любого х [1.3 ; 1.5]"<<endl;

	double phi_a_diff = 0;
	phi_a_diff = (3 * pow(a, 2) - 4 * a) / 10;

	double phi_b_diff = 0;
	phi_b_diff = (3 * pow(b, 2) - 4 * b) / 10;

	cout << "|phi_diff(x)| [" << abs(phi_a_diff) << ";" << abs(phi_b_diff) << "] => |phi_diff(x)| < 0.08 = q для любого х [1.3 ; 1.5]"<<endl; //интервал для проиводной должен начинаться с 0!!
	cout << "Условия теоремы выполнены"<<endl;

}

double SimpleIteration(double x_prev, int k, double eps)
{
	double xk = 0;

	if (k == 0)
	{
		x_prev = 1;
		return SimpleIteration(x_prev, k + 1, eps);
	}

	xk = get_phi(x_prev, k - 1);
	//cout << "eps(" << k << ") = ";
	if (errorPassedSI(xk, x_prev, k, eps)<=eps)
	{

		cout << setw(3) << k << "|" << setw(9) << xk << "|" << endl;
		cout << "eps(" << k << ") = " << errorPassedSI(xk, x_prev, k, eps);
		cout << " <= " << eps << endl << "Решение найдено на шаге " << k << '.' << endl << "X:" << xk << endl;
		return xk;
	}
	else
	{
		//cout << " > " << eps << endl;
		cout << setw(3) << k << "|" << setw(9) << xk << "|" << setw(12) << get_phi(xk, k) << endl;
		x_prev = xk;
		return SimpleIteration(x_prev, k + 1, eps);
	}
}


void u_main()
{
	
	double x_prev = -0.6;
	//setlocale(LC_ALL, "Russian");
	int k = 0;
	//int n = 15;
	double eps =0.001;
	cout << "Заданная точность: " << eps << endl;
	//vector<double> x;
	//x.resize(n,0);

	cout << setw(48) << "=====================================================================================" << endl;
	cout << "Метод Ньютона: " << endl;
	cout << setw(3) << "k" << "|" << setw(9) << "xk" << "|" << setw(12) << "f(xk)" << "|" << setw(12) << "df/dxk" << "|" << setw(12) << "-f(xk)/(df(xk)/dxk)" << endl;
	Newton(x_prev, k, eps);

	cout << setw(48) << "=====================================================================================" << endl;
	cout << "Метод простых итераций: " << endl;
	Theorem();
	cout << setw(3) << "k" << "|" << setw(9) << "xk" << "|" << setw(12) << "phi(xk)" << endl;
	SimpleIteration(x_prev, k, eps);

}
