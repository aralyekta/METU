#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#define ERROR 1000000
#define MAX(ptr) ((ptr)->max)
#define MAX_INT(ptr) ((ptr)->max_int)
#define MIN(ptr) ((ptr)->min)
#define MIN_INT(ptr) ((ptr)->min_int)
#define INT_DIFF(ptr) ((ptr)->interval_diff)
#define INT_DIFF_INT(ptr) ((ptr)->interval_diff_int)
#define VALUE(ptr) ((ptr)->val)
#define LETTER(ptr) ((ptr)->letter)
#define PROB(ptr) ((ptr).probability)
#define MOVE_AMOUNT(ptr) ((ptr)->move_amount)
#define POWER(ptr) ((ptr)->power)

#define MIN_STR(strct) (strct.min)
#define MAX_STR(strct) (strct.max)
#define INT_DIFF_STR(strct) (strct.interval_diff)
#define VAL_STR(strct) (strct.val)

typedef struct letter_struct
{
	char letter;
	double *probability;
	double val, max, min, interval_diff, move_amount;
	int max_int, min_int, power;
	long interval_diff_int;
} letter_struct;

typedef struct result_intervals
{
	double min, max;
	int counter;
} interval_struct;

char *in_to_post(char *str);
int how_many_chars(char *str);
int which_func(char *str);
int can_i_insert(char *temp, char *stack, char *stack_start);
double post_to_result(char *str, letter_struct *ptr_struct);
double find_val(letter_struct *ptr_struct, char letter);
double solve_func(char *str_post, letter_struct *ptr_struct, int letter_amount, int interval_amount);
/*double find_random(double min, double max);*/
double find_random(letter_struct *ptr_struct, int interval_num);
void set_intervals(letter_struct *ptr_struct, int interval_amount, int letter_amount);
void randomize_letter(letter_struct *ptr_struct, int interval_amount);

int main()
{
	char *func = malloc(201 * sizeof(char));
	int interval_amount, i, j, letter_amount, temp, flag, read_counter = 0;
	long int experiment_amount, total_experiment_amount;
	letter_struct *ptr_struct;
	char *str_post;
	char temp_char;
	interval_struct * int_struct;
	int *probabilities = malloc(20 * sizeof(int));
	double abs_max, abs_min, temp1, temp2, temp_def, interval_diff;
	srand(time(0));
	for (scanf("%c", &temp_char); temp_char != '\n'; scanf("%c", &temp_char))
	{
		if ((temp_char != ' ') && (temp_char != '\t'))
		{
			func[read_counter] = temp_char;
			read_counter++;
		}
	}
	func[read_counter] = '\0';
	letter_amount = how_many_chars(func);
	ptr_struct = malloc(letter_amount * sizeof(letter_struct));
	scanf("%d %ld", &interval_amount, &experiment_amount);
	for (i = 0; i < letter_amount; i++)
	{
		(ptr_struct+i)->probability = malloc(interval_amount * sizeof(double));
		(ptr_struct+i)->interval_diff = ((double)MAX(ptr_struct+i) - MIN(ptr_struct+i)) / interval_amount;
	}
	for (i = 0; i < letter_amount; i++)
	{
		scanf(" %c %lf %lf", &LETTER(ptr_struct+i), &MIN(ptr_struct+i), &MAX(ptr_struct+i));
		INT_DIFF(ptr_struct+i) = (MAX(ptr_struct+i)-MIN(ptr_struct+i))/interval_amount;
		for (j = 0; j < interval_amount; j++)
		{
			scanf(" %lf", (((ptr_struct+i)->probability) + j));
		}
	}
	set_intervals(ptr_struct, interval_amount, letter_amount);
	int_struct = malloc(interval_amount * sizeof(interval_struct));
	str_post = in_to_post(func);
	solve_func(str_post, ptr_struct, letter_amount, interval_amount);
	/*
	for (i = 0; i < letter_amount; i++)
	{
		printf("Min is %d, max is %d, power is %d and int diff is %d\n", MIN_INT(ptr_struct+i), MAX_INT(ptr_struct+i), POWER(ptr_struct+i),  INT_DIFF_INT(ptr_struct+i));
	}
	*/
	
	temp1 = solve_func(str_post, ptr_struct, letter_amount, interval_amount);
	temp2 = solve_func(str_post, ptr_struct, letter_amount, interval_amount);
	abs_max = (temp1 > temp2) ? temp1 : temp2;
	abs_min = (temp2 < temp1) ? temp2 : temp1;
	for (i = 2; i < experiment_amount; i++)
	{
		temp_def = solve_func(str_post, ptr_struct, letter_amount, interval_amount);
		if (temp_def < abs_min)
		{
			abs_min = temp_def;
		}
		else if (temp_def > abs_max)
		{
			abs_max = temp_def;
		}
	}
	printf("Min and max values are %.4f %.4f \n", abs_min, abs_max);
	interval_diff = (abs_max-abs_min)/interval_amount;
	for (i = 0; i < interval_amount; i++)
	{
		(int_struct+i)->min = abs_min+i*interval_diff;
		(int_struct+i)->max = abs_min+(i+1)*interval_diff;
		(int_struct+i)->counter = 0;
	}
	total_experiment_amount = experiment_amount;
	for (i = 0, flag = 0; i < experiment_amount; i++, flag = 0)
	{
		temp_def = solve_func(str_post, ptr_struct, letter_amount, interval_amount);
		if (temp_def < abs_min)
		{
			abs_min = temp_def;
		}
		if (temp_def > abs_max)
		{
			abs_max = temp_def;
		}
		for (j = 0; j < interval_amount; j++)
		{
			if ((temp_def < (int_struct+j)->max) && (temp_def >= (int_struct+j)->min))
			{
				/*printf("This value is in %dth interval, counter is %d\n", j, (int_struct+j)->counter);*/
				((int_struct+j)->counter)++;
				flag = 1;
				break;
			}
		}
		if (flag != 1)
		{
			total_experiment_amount--;
		}
	}
	printf("Min and max values are %.4f %.4f \n", abs_min, abs_max);
	printf("%.3f %.3f ", abs_min, abs_max);
	for (i = 0; i < interval_amount; i++)
	{
		printf("%.3f ", ((int_struct+i)->counter)/(double)total_experiment_amount);
	}
	printf("\n");
	/*
	for (i = 0; i < letter_amount; i++)
	{
		randomize_letter(ptr_struct+i, interval_amount);
	}
	printf("Values are\n");
	for (i = 0; i < letter_amount; i++)
	{
		printf("%2.6f ", VALUE(ptr_struct+i));
	}
	printf("\n%f\n", solve_func(func, ptr_struct));
	*/
	/*
	for (i = 0; i < interval_amount; i++)
	{
		probabilities[i] = 0;
	}
	for (i = 0; i < 10000; i++)
	{
		temp = randomize_letter(ptr_struct[0], interval_amount, probabilities);
		probabilities[temp]++;
	}
	for (i = 0; i < interval_amount; i++)
	{
		printf("Probability for %dth interval: %.3f\n", i+1, probabilities[i]/(double)10000);
	}
	*/
	/*find_random(1.5, 2.5);*/
	free(int_struct);
	for (i = 0; i < letter_amount; free((ptr_struct+i)->probability),i++);
	free(ptr_struct);
	free(func);
	free(probabilities);
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

double solve_func(char *str_post, letter_struct *ptr_struct, int letter_amount, int interval_amount)
{
	double val_return;
	int i;
	for (i = 0; i < letter_amount; i++)
	{
		randomize_letter(ptr_struct+i, interval_amount);
	}
	/*
	printf("The values for this call are:");
	for (i = 0; i < letter_amount; i++)
	{
		printf("%.5f ", VALUE(ptr_struct+i));
	}
	printf("\n");
	*/
	val_return = post_to_result(str_post, ptr_struct);
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
	int i;
	for (temp = str, i = 0; *temp; temp = strchr(temp, ' '), temp++)
	{
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

void set_intervals(letter_struct *ptr_struct, int interval_amount, int letter_amount)
{
	int i, max_power, min_power, j;
	double max_multiplied, min_multiplied, int_diff;
	for (i = 0, max_power = 0, min_power = 0; i < letter_amount; i++, max_power = 0, min_power = 0)
	{
		min_multiplied = MIN(ptr_struct+i);
		max_multiplied = MAX(ptr_struct+i);
		if ((MIN(ptr_struct+i) < 0) && (MAX(ptr_struct+i) < 0))
		{
			MOVE_AMOUNT(ptr_struct+i) = (-1) * min_multiplied;
			min_multiplied += MOVE_AMOUNT(ptr_struct+i);
			max_multiplied += MOVE_AMOUNT(ptr_struct+i);
		}
		else if ((MIN(ptr_struct+i) < 0) && (MAX(ptr_struct+i) == 0))
		{
			MOVE_AMOUNT(ptr_struct+i) = (-1) * min_multiplied;
			min_multiplied += MOVE_AMOUNT(ptr_struct+i);
			max_multiplied += MOVE_AMOUNT(ptr_struct+i);
		}
		else if ((MIN(ptr_struct+i) < 0) && (MAX(ptr_struct+i) > 0))
		{
			MOVE_AMOUNT(ptr_struct+i) = (-1) * min_multiplied;
			min_multiplied += MOVE_AMOUNT(ptr_struct+i);
			max_multiplied += MOVE_AMOUNT(ptr_struct+i);
		}
		if (min_multiplied != 0)
		{
			while (min_multiplied - (int)min_multiplied >= ((double)1/(ERROR * pow(10, min_power))))
			{
				min_multiplied *= 10;
				min_power++;
			}
			if (min_power < 4)
			{
				for (; min_power < 4; min_multiplied *= 10, min_power++);
			}
		}
		while (max_multiplied - (int)max_multiplied >= ((double)1/(ERROR * pow(10, max_power))))
		{
			max_multiplied *= 10;
			max_power++;
		}
		if (max_power < 4)
		{
			for (; max_power < 4; max_multiplied *= 10, max_power++);
		}
		if (min_power > max_power)
		{
			POWER(ptr_struct+i) = min_power;
			for (j = 0; j < (min_power - max_power); j++, max_multiplied *= 10);
		}
		else if (max_power > min_power)
		{
			POWER(ptr_struct+i) = max_power;
			for (j = 0; j < (max_power - min_power); j++, min_multiplied *= 10);
		}
		else 
		{
			POWER(ptr_struct+i) = max_power;
		}
		MAX_INT(ptr_struct+i) = (int)max_multiplied;
		MIN_INT(ptr_struct+i) = (int)min_multiplied;
		int_diff = (((int)max_multiplied-(int)min_multiplied) / interval_amount);
		for (j = 0; j < 4; j++, POWER(ptr_struct+i)++, int_diff *= 10);
		INT_DIFF_INT(ptr_struct+i) = (long)int_diff;
	}
}

void randomize_letter(letter_struct *ptr_struct, int interval_amount)
{
	double *probability = malloc(interval_amount * sizeof(double));
	double result, min_last, max_last, upper_end = 0;
	int *power = malloc(interval_amount * sizeof(int));
	int i, max_power = 0, rand_val, interval_num, lower_end = 0;
	for (i = 0; i < interval_amount; i++)
	{
		probability[i] = PROB(*ptr_struct)[i];
		power[i] = 0;
		while (probability[i] - (int)probability[i] > ((double)1/ERROR*(pow(10, power[i]))))
		{
			probability[i] *= 10;
			power[i]++;
		}
		if (power[i] > max_power)
		{
			max_power = power[i];
		}
	}
	for (i = 0; i < interval_amount; i++)
	{
		if (power[i] < max_power)
		{
			for (;power[i] < max_power; probability[i] *= 10, power[i]++);
		}
		upper_end += probability[i];
	}
	rand_val = rand()%(int)upper_end;
	for (interval_num = -1, i = 0, lower_end += (int)probability[0]; i-1 < interval_amount; lower_end += (int)probability[i+1], i++)
	{
		if (rand_val <= lower_end)
		{
			/*printf("Aha! exiting for %dth interval\n", i+1);*/
			interval_num = i;
			break;
		}
	}
	free(probability);
	free(power);
	if (interval_num == -1)
	{
		interval_num = interval_amount;
	}
	/*printf("Calling the func for %2.6f %d and %2.6f %d\n", min_last, (int)min_last, max_last, (int)max_last);*/
	/*printf("Calling find random for interval %d\n", interval_num);*/
	result = find_random(ptr_struct, interval_num);
	/*printf("Result is %2.6f for interval num %d \n", result, interval_num);*/
	VALUE(ptr_struct) = result;
}

double find_random(letter_struct *ptr_struct, int interval_num)
{
	double result = MIN(ptr_struct), randomized_val;
	long integer_randomized_val;
	if (interval_num > 0)
	{
		result += (interval_num) * INT_DIFF(ptr_struct);
	}
	integer_randomized_val = rand()%INT_DIFF_INT(ptr_struct);
	randomized_val =  (double)integer_randomized_val / pow(10, POWER(ptr_struct));
	result += randomized_val;
	return result;
}
