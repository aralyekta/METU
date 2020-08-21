#include <stdio.h>

int solve(int Q[], int row, int n);
int check(int Q[], int j, int row);

int main()
{
	int Q[5]= {0};
	solve(Q, 0, 5);
	return 0;
}

int check(int Q[], int j, int row)
{
	int i, state = 1;
/*	printf("Checking for row %d and column %d\n", row, j);*/
	for (i = 0; i < row; i++)
	{
/*		printf("The value from list is %d\n",Q[i]);*/
		if (Q[i] == j)
		{
			state = 0;
			break;
		}
	}
/*	printf("Return value from check is:%d\n",state);*/
	return state;
}

int solve(int Q[], int row, int n)
{
	int flag = 0, j, val = -2, i;

	for (j = 0; j < n ; j++)
	{

		if (row == 0 || (check(Q, j, row) && j != Q[row-1]+1 && j != Q[row-1]-1))
		{
/*			printf("Able to enter the big if for row %d and column %d\n", row, j);*/
			Q[row] = j;
			if (row == n-1)
			{
				return 0;
			}
			else
			{
				val = solve(Q, row+1, n);
/*				printf("Current row and col are: %d %d, the val from smaller part is: %d\n", row, j, val);*/
			}
			if (val == -1)
				continue;
			else 
			{
				flag = 1;
				if (row == n-2)
				{
					printf("Printing a solution for the %dth row: \n", row);
					for (i = 0 ; i < n ; i++)
					{
						printf("%d\n", Q[i]);
					}
				}
			}
		}
	}
	if (flag == 0)
	{
		return -1;
	}
	else
		return 0;
}

