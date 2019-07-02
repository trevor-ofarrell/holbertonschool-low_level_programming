#include "holberton.h"

/**
 * print_array - print n elements of array.
 * @a: int
 * @n: int
 * Return: Always 0.
 */
void print_array(int *a, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (i == 0)
		printf("%d", a[i]);
		else
			printf(", %d", a[i]);
	}
	printf("\n");
}
