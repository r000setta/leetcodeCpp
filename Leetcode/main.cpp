#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

inline int f(double num)
{
	return num > round(num) ? (int)num : (int)num + 1;
}

int main(void)
{
	int n;
	int a[100][100] = { {0} };
	double x, y;
	scanf("%d", &n);
	for (y = 0; y <= n; y += 0.01)
	{
		x = sqrt(n * n - (y - n) * (y - n)) + n;
		a[f(y)][f(x)] = 1;
		a[f(y)][f(2*n-x)] = 1;
		a[f(2*n-y)][f(x)] = 1;
		a[f(2*n-y)][f(2*n-x)] = 1;
	}
	for (int y = 0; y <= (2 * n); y++)
	{
		for (int x = 0; x <= (2 * n); x++)
		{
			if (a[y][x] == 0)
			{
				printf("@");
			}
			else
			{
				printf("*");
			}
		}
		printf("\n");
	}
}