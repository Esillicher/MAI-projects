#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	freopen ("../raw/ground.raw", "w", stdout);
	cout << fixed << setprecision (4);
	for (float i = -30.0; i < 30.0; ++i)
	{
		for (float j = -30.0; j < 30.0; ++j)
		{
			cout << i << " " << j << " " << fabs (sin (i + j)) - 2<< " ";
			cout << i + 1.0 << " " << j << " " << fabs (sin (i + 1.0 + j)) - 2<< " ";
			cout << i << " " << j + 1.0 << " " << fabs (sin (i + j + 1.0)) - 2<< " " << endl;
			
			cout << i << " " << j + 1.0 << " " << fabs (sin (i + j + 1.0)) - 2<< " ";
			cout << i + 1.0 << " " << j << " " << fabs (sin (i + 1.0 + j)) - 2<< " ";
			cout << i + 1.0 << " " << j + 1.0 << " " << fabs (sin (i + j + 2.0)) - 2<< " " << endl;
		}
	}
	return 0;
}
