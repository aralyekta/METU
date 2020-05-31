#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX(ptr) ((ptr)->max)
#define MIN(ptr) ((ptr)->min)
#define VALUE(ptr) ((ptr)->val)
#define LETTER(ptr) ((ptr)->letter)
#define CTR(ptr) ((ptr)->counter)

typedef struct letter_struct
{
	char letter;
	int counter;
	float *probability;
	double val, max, min;
} letter_struct;

char *in_to_post(char *str);
char *removespaces(char *str, int *letter_amount);
int how_many_chars(char *str);
int which_func(char *str);
char *find_parenthesis_end(char *str);
int can_i_insert(char *temp, char *stack, char *stack_start);
double post_to_result(char *str, letter_struct *ptr_struct);
double find_val(letter_struct *ptr_struct, char letter);
double solve_func(char *str, letter_struct *ptr_struct);

double solve_func(char *str, letter_struct *ptr_struct)
{
	char *str_post;
	double val_return;
	str_post = in_to_post(str);
	printf("Str after post is %s\n", str_post);
	val_return = post_to_result(str_post, ptr_struct);
	free(str_post);
	return val_return;
}

double find_val(letter_struct *ptr_struct, char letter)
{
	for(; LETTER(ptr_struct) != letter; ptr_struct++);
	return VALUE(ptr_struct);
}

double post_to_result(char *str, letter_struct *ptr_struct)
{
	double stack[200];
	char *temp;
	int i, c;
	for (temp = str, i = 0; *temp; temp = strchr(temp, ' '), temp++)
	{
		printf("Entered the loop for: ");
		for (c = 0; c < i; c++)
		{
			printf("%f ", stack[c]);
		}
		printf("\n");
		/* *temp can be
		 * number
		 * Uppercase letter (variable)
		 * lowercase letter (func)
		 * operator */
		if (isdigit(*temp))
		{
			stack[i] = atof(temp);
			i++;
		}
		else if (*temp >= 'A' && *temp <= 'Z')
		{
			stack[i] = find_val(ptr_struct, *temp);
			i++;
		}
		else if (*temp == 's')
		{
			stack[i-1] = sin(stack[i-1]);
		}
		else if (*temp == 'c')
		{
			stack[i-1] = cos(stack[i-1]);
		}
		else if (*temp == 'l')
		{
			stack[i-1] = log(stack[i-1]);
		}
		else if (*temp == 'q')
		{
			stack[i-1] = sqrt(stack[i-1]);
		}
		else if (*temp == '~')
		{
			stack[i-1] *= (-1);
		}
		else if (*temp == '+')
		{
			stack[i-2] += stack[i-1];
			i--;
		}
		else if (*temp == '-')
		{
			stack[i-2] -= stack[i-1];
			i--;
		}
		else if (*temp == '/')
		{
			stack[i-2] /= stack[i-1];
			i--;
		}
		else if (*temp == '*')
		{
			stack[i-2] *= stack[i-1];
			i--;
		}
		else if (*temp == '^')
		{
			stack[i-2] = pow(stack[i-2], stack[i-1]);
			i--;
		}
	}
	return stack[0];
}

int main()
{
	/*
	char *func = malloc(201 * sizeof(char));
	scanf("%s", func);
	*/
	int i;
	int *letter_amount = malloc(sizeof(int));
	letter_struct *ptr_struct;
	/* Dont forget that you will be using a ptr for the string, so free that */
	char array[201] = "    sqrt(2 - sin(3*A/B)^2.5)+ 0.5*(C*~(D) + 3.11 +B)";
	char array2[201] = " sin (15)*co s( 2 0)/ln(15)        ^sqrt(4 ) ";
	char array3[201] = "A-B^C^D*(E-(F-G-H))/K";
	char array4[201] = "sin(1.5*ln(20+cos(15)) - 25*12^(2))";
	char array5[201] = "sin(1.5)+15-2^2";
	char *str;
	str = removespaces(array, letter_amount);
	ptr_struct = malloc((*letter_amount) * sizeof(letter_struct));
	for (i = 0; i < *letter_amount; i++)
	{
		LETTER(ptr_struct+i)= 'A'+i;
		VALUE(ptr_struct+i)= 1+i;
	}
	for (i = 0; i < *letter_amount; i++)
	{
		printf("%c %f\n", LETTER(ptr_struct+i), VALUE(ptr_struct+i));
	}
	printf("%f\n", solve_func(str, ptr_struct));
	free(letter_amount);
	free(ptr_struct);
	return 0;
}

int how_many_chars(char *str)
{
	int result = 0, i = 0;
	int array[26];
	for (; i < 26; i++)
	{
		array[i] = 0;
	}
	for (; *str; str++)
	{
		if (*str >= 'A' && *str <= 'Z' && array[((*str)-'A')] != 1) /* Checks if the current char is a letter and if it wasn't found before */
		{
			result++;
			array[((*str)-'A')] = 1;
		}
	}
	return result;
}

char *removespaces(char *str, int *letter_amount)
{
	/* This function removes the spaces on the string and also finds strlen */
	int last_was_blank = 0, was_blank_before;
	char *i = NULL;
	char *j = str;
	for (was_blank_before = 0; *j; j++)
	{
		if (*j == ' ')
		{
			last_was_blank = 1;
			if (was_blank_before == 0)
			{
				was_blank_before = 1;
				i = j;
			}
		}
		else
		{
			if (last_was_blank)
			{
				last_was_blank = 0;
			}
			if (i)
			{
				*i = *j;
				i++;
			}
		}
	}
	if (i)
	{
		*i = '\0';
	}
	*letter_amount = how_many_chars(str);
	printf("%d\n", *letter_amount);
	return str;
}

char *find_parenthesis_end(char *str)
{
	int amount = 0;
	while (*str)
	{
		if (*str == '(')
		{
			amount++;
		}
		else if (*str == ')')
		{
			amount--;
			if (!amount)
			{
				return str;
			}
		}
		str++;
	}
	return str;
}

int which_func(char *str)
{
	/* There are 6 cases 
	 * ~ returns 1
	 * sin returns 2
	 * cos returns 3
	 * sqrt returns 4
	 * ln returns 5
	 * no func returns 0 */
	if (*str == '~')
	{
		return 1;
	}
	else if ((*str == 's') && (*(str+1) == 'i') && (*(str+2) == 'n'))
	{
		return 2;
	}
	else if((*str == 'c') && (*(str+1) == 'o') && (*(str+2) == 's'))
	{
		return 3;
	}
	else if((*str == 's') && (*(str+1) == 'q') && (*(str+2) == 'r') && (*(str+3) =='t'))
	{
		return 4;
	}
	else if((*str == 'l') && (*(str+1) == 'n'))
	{
		return 5;
	}
	else
	{
		return 0;
	}
}

int can_i_insert(char *temp, char *stack, char *stack_start)
{
	int prec_current = 0, prec_before = 0, func_flag = 0;
	if (*temp == '+' || *temp == '-')
	{
		prec_current = 1;
	}
	else if (*temp == '*' || *temp == '/')
	{
		prec_current = 2;
	}
	else if (*temp == '^')
	{
		prec_current = 3;
	}
	else
	{
		func_flag = 1;
		prec_current = 4;
	}
	
	if (stack == stack_start)
	{
		if (func_flag == 1)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}

	if (*(stack-1) == '+' || *(stack-1) == '-')
	{
		prec_before = 1;
	}
	else if (*(stack-1) == '*' || *(stack-1) == '/')
	{
		prec_before = 2;
	}
	else if (*(stack-1) == '^')
	{
		prec_before = 3;
	}
	else if (*(stack-1) == '(')
	{
		if (func_flag == 1)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		prec_before = 4;
	}

	if ((prec_current == 3 && prec_before <= 3) || (prec_current > prec_before))
	{
		if (func_flag == 1)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}	
}

char *in_to_post(char *str)
{
	/* This function transforms infix to postfix.*/
	char *result = malloc(400 * sizeof(char));
	char *stack = malloc(200 * sizeof(char));
	char *temp;
	int i, j, temp_return;
	memset(result, '\0', 400);
	memset(stack, '\0', 200);
	for (temp = str, i = 0, j = 0; *temp; temp++)
	{
		if (isdigit(*temp) || *temp == '.')
		{
			for(; (isdigit(*temp)) || *temp == '.'; temp++, i++)
			{
				result[i] = *temp;
			}
			temp--;
			result[i] = ' ';
			i++;
		}
		else if ((*temp >= 'A') && (*temp <= 'Z'))
		{
			result[i] = *temp;
			i++;
			result[i] = ' ';
			i++;
		}
		else if (*temp != '(' && *temp != ')')
		{
			if ((temp_return = can_i_insert(temp, stack+j, stack)))
			{
				if (temp_return == 1)
				{
					stack[j] = *temp;
					j++;
				}
				else if (temp_return == 2)
				{
					temp_return = which_func(temp);
					if (temp_return == 1)
					{
						stack[j] = '~';
						j++;
					}
					else if (temp_return == 2)
					{
						stack[j] = 's';
						j++;
						temp += 2;
					}
					else if (temp_return == 3)
					{
						stack[j] = 'c';
						j++;
						temp += 2;
					}
					else if (temp_return == 4)
					{
						stack[j] = 'q';
						j++;
						temp += 3;
					}
					else if (temp_return == 5)
					{
						stack[j] = 'l';
						j++;
						temp++;
					}
				}
			}
			else
			{
				while ((temp_return = can_i_insert(temp, stack+j, stack)) == 0)
				{
					result[i] = stack[j-1];
					i++;
					result[i] = ' ';
					i++;
					j--;
				}
				if (temp_return == 1)
				{
					stack[j] = *temp;
					j++;
				}
				else if (temp_return == 2)
				{
					temp_return = which_func(temp);
					if (temp_return == 1)
					{
						stack[j] = '~';
						j++;
					}
					else if (temp_return == 2)
					{
						stack[j] = 's';
						j++;
						temp += 2;
					}
					else if (temp_return == 3)
					{
						stack[j] = 'c';
						j++;
						temp += 2;
					}
					else if (temp_return == 4)
					{
						stack[j] = 'q';
						j++;
						temp += 3;
					}
					else if (temp_return == 5)
					{
						stack[j] = 'l';
						j++;
						temp++;
					}
				}
			}
		}
		else if (*temp == '(')
		{
			stack[j] = *temp;
			j++;
		}
		else if (*temp == ')')
		{
			while (stack[j-1] != '(')
			{
				result[i] = stack[j-1];
				i++;
				result[i] = ' ';
				i++;
				j--;
			}
			j--;
		}
	}
	while (j > 0)
	{
		result[i] = stack[j-1];
		i++;
		result[i] = ' ';
		i++;
		j--;
	}
	result[i] = '\0';
	free(stack);
	return result;
}
