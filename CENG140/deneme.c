#include <stdio.h>
int array[10];
int func()
{
	int i;
	for (i = 0 ; i < 10; i++)
	{
		array[i] = i;
		printf("%d\n", array[i]);
	}
}
int main()
{
	int i;
	func();
	for ( i = 0 ; i < 10 ; i++)
	{
		printf("%d\n",array[i]);
	}
	return 0;
}

