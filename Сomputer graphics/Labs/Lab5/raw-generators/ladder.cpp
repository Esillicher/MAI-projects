#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

void PrintC(float i, float j, float z, bool end)
{
	cout << i << " " << j << " " << z << " ";
	if (end) cout << endl;
}

void TopSurfCoords(float i, float j, float z)
{
	PrintC(i, j, z, 0);
	PrintC(i, j + 8.0, z, 0);
	PrintC(i - 8.0, j, z, 1);

	PrintC(i - 8.0, j, z, 0);
	PrintC(i, j + 8.0, z, 0);
	PrintC(i - 8.0, j + 8.0, z, 1);
}

void BottomSurfCoords(float i, float j, float z)
{
	PrintC(i, j + 8.0, z, 0);
	PrintC(i, j, z, 0);
	PrintC(i - 8.0, j, z, 1);

	PrintC(i, j + 8.0, z, 0);
	PrintC(i - 8.0, j, z, 0);
	PrintC(i - 8.0, j + 8.0, z, 1);
}

void SideSurfCoords(float i, float j, float z, float height)
{
	// back
	PrintC(i, j, z - height, 0);
	PrintC(i, j, z, 0);
	PrintC(i - 8.0, j, z, 1);

	PrintC(i, j, z - height, 0);
	PrintC(i - 8.0, j, z, 0);
	PrintC(i - 8.0, j, z - height, 1);

	// front
	PrintC(i, j + 8.0, z, 0);
	PrintC(i, j + 8.0, z - height, 0);
	PrintC(i - 8.0, j + 8.0, z, 1);

	PrintC(i - 8.0, j + 8.0, z, 0);
	PrintC(i, j + 8.0, z - height, 0);
	PrintC(i - 8.0, j + 8.0, z - height, 1);

	// left
	PrintC(i, j, z, 0);
	PrintC(i, j, z - height, 0);
	PrintC(i, j + 8.0, z, 1);

	PrintC(i, j + 8.0, z, 0);
	PrintC(i, j, z - height, 0);
	PrintC(i, j + 8.0, z - height, 1);

	// right
	PrintC(i - 8.0, j, z, 0);
	PrintC(i - 8.0, j, z - height, 0);
	PrintC(i - 8.0, j + 8.0, z, 1);

	PrintC(i - 8.0, j + 8.0, z, 0);
	PrintC(i - 8.0, j, z - height, 0);
	PrintC(i - 8.0, j + 8.0, z - height, 1);
}

int main()
{
	freopen ("../raw/ladder.raw", "w", stdout);
	cout << fixed << setprecision (4);

	float i = 32.0, j = 16.0, z = 2.0;
	float height = 2.0;

	while (j > -24.0)
	{
		TopSurfCoords(i, j, z);
		BottomSurfCoords(i, j, z - height);
		SideSurfCoords(i, j, z, height);
		j -= 8.0;
		z += height;
	}

	while (i > -24.0)
	{
		TopSurfCoords(i, j, z);
		BottomSurfCoords(i, j, z - height);
		SideSurfCoords(i, j, z, height);
		i -= 8.0;
		if (i > 0.0) z += height;
		else if (i < 0.0) z -= height;
	}

	while (j < 24.0)
	{
		TopSurfCoords(i, j, z);
		BottomSurfCoords(i, j, z - height);
		SideSurfCoords(i, j, z, height);
		j += 8;
		z -= height;
	}

	return 0;
}
