#include "libs.h"

double f(double x, double y, double z)
{
	return z;
}
double g(double x, double y, double z)
{
	return (-2 * (x + 1)*z + 2 * y) / (x*(2 * x + 1));
}

double p(double x)
{
	return 2 * (x + 1) / (x*(2 * x + 1));
}

double q(double x)
{
	return - 2 / (x*(2 * x + 1));
}

vector <double> RR(vector <double> y, vector <double> y2, vector <double> y_ist, vector <double> R)
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


vector<double> gauss(vector<vector<double>> a, vector<double> y, int n)
{
	vector <double> x;
	double max;
	int k, index;
	const double eps = 0.00001;  // точность
	x.resize(n, 0);
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			cout << "Решение получить невозможно из-за нулевого столбца ";
			cout << index << " матрицы A" << endl;
			//return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}


vector <double> RK_n(vector<double> y, vector<double> x, double nu, double h, double y0, int n)
{

	double y1 = 0;
	vector<double> K, L, Fi;
	K.resize(4, 0);
	L.resize(4, 0);
	Fi.resize(n, 0);
	
	for (int i = 0; i < n; ++i)
	{
		K[0] = h*f(x[i], y0, nu);
		L[0] = h*g(x[i], y0, nu);
		K[1] = h*f(x[i] + h / 2, y0 + K[0] / 2, nu + L[0] / 2);
		L[1] = h*g(x[i] + h / 2, y0 + K[0] / 2, nu + L[0] / 2);
		K[2] = h*f(x[i] + h / 2, y0 + K[1] / 2, nu + L[1] / 2);
		L[2] = h*g(x[i] + h / 2, y0 + K[1] / 2, nu + L[1] / 2);
		K[3] = h*f(x[i] + h, y0 + K[2], nu + L[2]);
		L[3] = h*g(x[i] + h, y0 + K[2], nu + L[2]);

		y0 = y0 + (K[0] + 2 * K[1] + 2 * K[2] + K[3]) / 6;
		nu = nu + (L[0] + 2 * L[1] + 2 * L[2] + L[3]) / 6;
		y[i] = y0;
						
	}
	
	return y;
}

vector<double> Shooting(vector<double> y, vector<double> y_ist, vector<double> x, vector<double> nu, double h, double y0, int n, int m)
{
	vector<double> Fi, y_RR;
	Fi.resize(n, 0);
	y_RR.resize(n, 0);

	y_RR = RK_n(y, x, nu[0], h, y0, n);
	y[0] = y_RR[n-1];
	Fi[0] = fabs(y[0] - y_ist[n - 1]);
			
	for (int i = 1; i < n; ++i)
	{
		y_RR = RK_n(y, x, nu[i], h, y0, n);
		y[i] = y_RR[n-1];
		Fi[i] = fabs(y[i] - y_ist[n - 1]);
		nu[i + 1] = nu[i] - (((nu[i] - nu[i - 1]) / (y[i] - y[i - 1])) * (y[i] - y_ist[n - 1]));
		if (Fi[i] < 0.0001 && m==1)
		{
			cout << "Метод стрельбы:" << endl;

			cout << setw(3) << "j" << "|" << setw(14) << "nu" << "|" << setw(14) << "y_k" << "|" << setw(14) << "y_ist" << "|" << setw(14) << "Fi" << "|" << endl;
			for (int j = 0; j <= i; ++j)
			{
				cout << setw(3) << j << "|" << setw(14) << nu[j] << "|" << setw(14) << y[j] << "|" << setw(14) << y_ist[n-1] << "|" << setw(14) << fixed << setprecision(12) << Fi[j] << "|" << endl;
			}
			cout << endl;
			cout << setw(3) << "i" << "|" << setw(14) << "x" << "|" << setw(14) << "y_k" << "|" << setw(14) << "y_ist" << "|" << setw(14) << "Eps" << "|" << endl;
			for (int i = 0; i <n; ++i)
			{
				cout << setw(3) << i << "|" << setw(14) << x[i] << "|" << setw(14) << y_RR[i] << "|" << setw(14) << y_ist[i] << "|" << setw(14) << fixed << setprecision(12) << y_RR[i]-y_ist[i] << "|" << endl;
			}
			for (int i = 0; i < n; ++i)
				y[i] = 0;
			break;
		}
	}
	
	
	return y_RR;
}


void PartII_main()
{
	
	int n = 11;
	int k = 10;
	vector<double> y, y_ist, x, z, z2, nu, b, b2, y2, R;
	vector <vector <double>> A, A2;

	A.resize(k);
	b.resize(k,0);
	A2.resize(5);
	b2.resize(5, 0);
	for (int i = 0; i < k; ++i)
	{
		A[i].resize(k, 0);
	}
	for (int i = 0; i < 5; ++i)
	{
		A2[i].resize(k, 0);
	}

	y.resize(n, 0);
	y_ist.resize(n, 0);
	x.resize(n, 0);
	z.resize(n, 0);
	z2.resize(n, 0);
	nu.resize(n, 0);
	y2.resize(6, 0);
	R.resize(6, 0);

	double h = 0.2;
	double z0 = 0;
	double y0 = 3;
	double x0 = 1;

	x[0] = x0;
	y[0] = y0;
	y2[0] = y0;
	y_ist[0] = y0;
	nu[0] = 0.3;
	nu[1] = 0.4;
	for (int i = 1; i < n; ++i)
	{
		x[i] = x[i-1] + h;
		y_ist[i] = 1/x[i] + 1+x[i];
	}
	
	y = Shooting(y, y_ist, x, nu, h, y0, n,1);
	y2 = Shooting(y2, y_ist, x, nu, 2*h, y0, 6,0);
	R = RR(y, y2, y_ist, R);
	cout << endl;

	A[0][0] = -2 + q(x[1])*h*h;
	A[0][1] = p(x[1])*h/2 + 1;

	A[k-1][k-2] = 1;
	A[k-1][k-1] = - 0.8;

	for (int i = 1; i < k-1 ; ++i)
	{
		A[i][i-1] = 1 - (p(x[i + 1])*h/2);
		A[i][i] = -2 + q(x[i+1])*h*h;
		A[i][i+1] = 1 + (p(x[i + 1])*h/2);
	}
	
	b[0] = y0*(p(x[1])*h/2 - 1);
	b[k-1] = 31 * 0.2 / 9;
		
	z = gauss(A, b, k);
	for (int i = 0; i < k; ++i)
	{
		y[i + 1] = z[i];
	}

	cout << "Конечно-разностный метод:" << endl;
	cout << setw(3) << "i" << "|" << setw(14) << "x" << "|" << setw(14) << "y_k" << "|" << setw(14) << "y_ist" << "|" << setw(14) << "Eps" << "|" << endl;
	for (int i = 0; i <n; ++i)
	{
		cout << setw(3) << i << "|" << setw(14) << x[i] << "|" << setw(14) << y[i] << "|" << setw(14) << y_ist[i] << "|" << setw(14) << fixed << setprecision(12) << y_ist[i]- y[i] << "|" << endl;
	}

	A2[0][0] = -2 + q(x[1]) * 4 * h * h;
	A2[0][1] = p(x[1])*2*h / 2 + 1;

	A2[4][3] = 1;
	A2[4][4] = -0.8;

	for (int i = 1; i < 4; ++i)
	{
		A2[i][i - 1] = 1 - (p(x[i + 1])*2*h / 2);
		A2[i][i] = -2 + q(x[i + 1]) * 4*h * h;
		A2[i][i + 1] = 1 + (p(x[i + 1])*2*h / 2);
	}

	b2[0] = y0*(p(x[1])*2*h / 2 - 1);
	b2[4] = 31 * 0.2 / 9;

	z2 = gauss(A2, b2, 5);
	for (int i = 0; i < 5; ++i)
	{
		y2[i + 1] = z2[i];
	}
	R = RR(y, y2, y_ist, R);
}