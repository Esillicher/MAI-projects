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
	for (float i = 40.0; i > -40.0; i -= 8)
	{
		for (float j = -40.0; j < 40.0; j += 8)
		{
			cout << i << " " << j << " " << '0' << " ";
			cout << i << " " << j + 8.0 << " " << '0' << " ";
			cout << i - 8.0 << " " << j << " " << '0' << " " << endl;
			
			cout << i - 8.0 << " " << j << " " << '0' << " ";
			cout << i << " " << j + 8.0 << " " << '0' << " ";
			cout << i - 8.0 << " " << j + 8.0 << " " << '0' << " " << endl;
		}
	}
	return 0;
}
