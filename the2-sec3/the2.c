/* inputta whitespace yok, ama blanklere karsi yazabilirsin.
 * yeni string olusturmak icin malloc kullan, eski stringleri free'le.
 * maximum input 200 karakter
 * soldan saga cozecegiz, harf olusmadan virgulu gecmeyecegiz
 * r3'te ayri ayri cagirip ve'sini alip devam edicez. ve'si 0 gelirse bitiricez
 * -((P&Q)>(Q>P)),((A|Q)>(R&(P|B))),-R#-P,-(A&(P|B)),((P&B)|(Q>P))
 *  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_if_finished(char *);
int check_if_one_char(char *, char *);
char **solve(char *);
char *find_parenthesis_end(char *);
int randomfunc(int);
int solve_loop(char *);

int solve_loop(char *str)
{
	char *str1 = malloc(strlen(str) * sizeof(char));
	char *str2 = malloc(1);
	char ** result;
	int result_val, result_str2 = -1, i;
	strcpy(str1, str);
	str2[0] = '\0';
	for (result_val = check_if_finished(str1); !result_val; result_val = check_if_finished(str1))
	{
		printf("\nEntered THE SOLVE LOOP for %s\n", str1); 
		result = solve(str1);
		str1 = realloc(str1, strlen(result[0]) * sizeof(char));
		strcpy(str1, result[0]);
		if (result[1][0] != '\0')
		{
			str2 = realloc(str2, strlen(result[1]) * sizeof(char));
			strcpy(str2, result[1]);
			result_str2 = solve_loop(str2);
			if (result_str2)
			{
				printf("Right str passed, continuing \n");
				str2 = realloc(str2, 1);
				str2[0] = '\0';
				continue;
			}
			else
			{
				printf("Right str didn't pass, exiting \n");
				return 0;
			}
		}
		for (i = 0; i < 2; i++)
		{
			free(result[i]);
		}
		free(result);
		
	}
	if (result_val == -1)
	{
		return 0;
	}
	else if (result_val == 1)
	{
		return 1;
	}
}

int main()
{
	char a1[] = "(--(A&B)>-C),F#G,H";
	char a2[] = "A,B#-(-A>B),F,G";
	char a3[] = "A,B#(--B|C)";
	char a4[] = "A,B#(C|B)";
	char a5[] = "A,B#--C,(C&--A)";
	char a6[] = "A,B#B,(-C|A)";
	char a7[] = "A,B#";
	char a8[] = "A,B#C";
	char a10[] = "(P>Q),(Q>R),-R#-P";
	char a9[] = "((A|B)|(B|A))#F";
	int result;
	result = solve_loop(a10);
	if (result)
	{
		printf("T\n");
	}
	else
	{
		printf("F\n");
	}
	/*
	char *str1 = malloc(1);
	char *str2 = malloc(1);
	int i;
	
	char ** result;
	str1[0] = '\0';
	str2[0] = '\0';
	result = solve(a10);
	randomfunc(10);
	str1 = realloc(str1, strlen(result[0]) * sizeof(char));
	strcpy(str1, result[0]);
	if (result[1][0] != '\0')
	{
		str2 = realloc(str2, strlen(result[1]) * sizeof(char));
		strcpy(str2, result[1]);
	}
	for (i = 0; i < 2; i++)
	{
		free(result[i]);
	}
	free(result);
	printf("THE RESULT OF 1 FUNCTION IS %s %d\n", str1, strlen(str1));
	if (str2[0] != '\0')
	{
		printf("THE RESULT OF 1 FUNCTION IS %s %d\n", str2, strlen(str2));
	}
	printf("%d\n", check_if_finished(str1));
	result = solve(str1);
	randomfunc(10);
	str1 = realloc(str1, strlen(result[0]) * sizeof(char));
	strcpy(str1, result[0]);
	if (result[1][0] != '\0')
	{
		str2 = realloc(str2, strlen(result[1]) * sizeof(char));
		strcpy(str2, result[1]);
	}
	for (i = 0; i < 2; i++)
	{
		free(result[i]);
	}
	free(result);
	printf("THE RESULT OF 1 FUNCTION IS %s %d\n", str1, strlen(str1));
	if (str2[0] != '\0')
	{
		printf("THE RESULT OF 1 FUNCTION IS %s %d\n", str2, strlen(str2));
	}
	printf("%d\n", check_if_finished(str1));
	*/
	/*
	result = solve(a2);
	randomfunc(10);
	str1 = realloc(str1, strlen(result[0]) * sizeof(char));
	strcpy(str1, result[0]);
	if (result[1][0] != '\0')
	{
		str2 = realloc(str2, strlen(result[1]) * sizeof(char));
		strcpy(str2, result[1]);
	}
	for (i = 0; i < 2; i++)
	{
		free(result[i]);
	}
	free(result);
	printf("THE RESULT OF 1 FUNCTION IS %s %d\n", str1, strlen(str1));
	if (str2[0] != '\0')
	{
		printf("THE RESULT OF 1 FUNCTION IS %s %d\n", str2, strlen(str2));
	}
	printf("%d\n", check_if_finished(str1));
	*/
	/*
	result = solve(str2);
	randomfunc(10);
	str1 = realloc(str1, strlen(result[0]) * sizeof(char));
	strcpy(str1, result[0]);
	if (result[1][0] != '\0')
	{
		str2 = realloc(str2, strlen(result[1]) * sizeof(char));
		strcpy(str2, result[1]);
	}
	for (i = 0; i < 2; i++)
	{
		free(result[i]);
	}
	free(result);
	printf("THE RESULT OF 2 FUNCTION IS %s %d\n", str1, strlen(str1));
	if (str2[0] != '\0')
	{
		printf("THE RESULT OF 2 FUNCTION IS %s %d\n", str2, strlen(str2));
	}
	*/
	/*
	result = solve(str1);
	randomfunc(10);
	str1 = realloc(str1, strlen(result[0]) * sizeof(char));
	strcpy(str1, result[0]);
	if (result[1][0] != '\0')
	{
		str2 = realloc(str2, strlen(result[1]) * sizeof(char));
		strcpy(str2, result[1]);
	}
	for (i = 0; i < 2; i++)
	{
		free(result[i]);
	}
	free(result);
	printf("THE RESULT OF 3 FUNCTION IS %s %d\n", str1, strlen(str1));
	if (str2[0] != '\0')
	{
		printf("THE RESULT OF 3 FUNCTION IS %s %d\n", str2, strlen(str2));
	}
	*/
}


char ** solve(char *str)
{
	/* String manipulasyonunu 1 kere yapar.
	 * Yeni olusacak string icin yer malloc edip eskisini free eder. Yeni stringi doner. */
	char **result = malloc(2 * sizeof(char *));
	char *start = str;
	char *arrow = strchr(str, '#');
	char *end = strchr(str, ',');
	char *new_str_before;
	char *new_str_current;
	char *new_str_current2;
	char *new_str_after;
	char *new_str_after2;
	char *index_of_operation;
	int what_is_operation = 0, how_many_negations = 0;
	int length_string = strlen(str);
	long len_before, len_after, len_current, len_current2, len_after2;
	printf("Entered the function for string %s\n", str);
	result[0] = malloc(1 * sizeof(char));
	result[1] = malloc(1 * sizeof(char));
	result[0][0] = '\0';
	result[1][0] = '\0';
	if (start == arrow)
	{
		start++;
	}
	if (!end)
		{
/*			printf("No commas found\n");*/
			if (start < arrow)
			{
				end = arrow-1;
/*				printf("Start is before the arrow, the order of the new end value is %ld\n", end-str);*/
			}
			else if (start > arrow)
			{
				end = &str[length_string-1];
/*				printf("Start is after the arrow, the order of the new end value is %ld\n", end-str);*/
			}
		}
		else if (end > arrow && start < arrow)
		{
/*			printf("Commas found\n");*/
			end = arrow-1;
/*			printf("The order of the end value is %ld\n", end-str);*/
		}
		else 
		{
/*			printf("No problems at all\n");*/
			end--;
/*			printf("The order of the end value is %ld\n", end-str);*/
		}
	printf("Start and end address and value is %p,%p,%ld,%ld\n", start, end, start-str, end-str);
	while (end == start || start == arrow)
	{
		printf("Entered loop, start and end address and value is %p,%p,%ld,%ld\n", start, end, start-str, end-str);
		if (end == &str[length_string-1])
		{
			printf("Solve function called for non solvable string, exiting.\n");
			return result;
		}
		start += 2;
		end = strchr(start, ',');
		if (!end)
		{
			printf("No commas found\n");
			if (start < arrow)
			{
				end = arrow-1;
				printf("Start is before the arrow, the new end value is %ld\n", end-str);
			}
			else if (start > arrow)
			{
				end = &str[length_string-1];
				printf("Start is before the arrow, the new end value is %ld\n", end-str);
			}
		}
		else if (end > arrow && start < arrow)
		{
			printf("Commas found\n");
			end = arrow-1;
			printf("The order of the end value is %ld\n", end-str);
		}
		else 
		{
			printf("No problems at all\n");
			end--;
			printf("The order of the end value is %ld\n", end-str);
		}
	}
	printf("END OF LOOP, Start and end address and value is %ld %ld\n", start-str, end-str);
	
	if (*start == '-')
	{
		if (start < arrow)
		{
			printf("Operation R1 on the left side\n");
			len_before = start-str; 
			len_after = length_string-(end-str)+1;
			len_current = end-start+1;
			if (len_before > 1)
			{
				new_str_before = malloc(len_before * sizeof(char));
				strncpy(new_str_before, str, len_before-1);
				new_str_before[len_before-1] = '\0';
				printf("The string before the operation is: %s\n", new_str_before);
				if (arrow == &str[length_string-1])
				{
					len_after--;
					printf("Length1 is :%d %d %d\n", len_before, len_after, len_current);
					new_str_after = malloc(len_after * sizeof(char));
					strncpy(new_str_after, end+1, len_after);
					new_str_after[len_after+1] = '\0';
				}
				else
				{
					printf("Length2 is :%d %d %d\n", len_before, len_after, len_current);
					new_str_after = malloc(len_after * sizeof(char));
					strncpy(new_str_after, end+1, len_after-1);
					new_str_after = strcat(new_str_after, ",");
					new_str_after[len_after-1] = '\0';
				}
				printf("The string after the operation is: %s\n", new_str_after);
			}
			else
			{
				len_after--;
				if (start == str && end == arrow-1)
				{
					if (arrow == &str[length_string-1])
					{
						printf("Length3 is :%d %d %d\n", len_before, len_after, len_current);
						new_str_after = malloc(len_after * sizeof(char));
						new_str_after = strcat(new_str_after, "#");
						new_str_after = strcat(new_str_after, end+2);
						new_str_after[len_after-1] = '\0';
					}
					else 
					{
						len_after++;
						printf("Length4 is :%d %d %d\n", len_before, len_after, len_current);
						new_str_after = malloc(len_after * sizeof(char));
						new_str_after = strcat(new_str_after, "#");
						new_str_after = strcat(new_str_after, end+2);
						new_str_after = strcat(new_str_after, ",");
						new_str_after[len_after-1] = '\0';
					}
				}
				else if (arrow == &str[length_string-1])
				{
/*					printf("Arrow is the last element\n");*/
					len_after--;
					printf("Length5 is :%d %d %d\n", len_before, len_after, len_current);
					new_str_after = malloc(len_after * sizeof(char));
					strncpy(new_str_after, end+2, len_after-1);
					new_str_after[len_after-1] = '\0';
				}
				else 
				{
					printf("Length6 is :%d %d %d\n", len_before, len_after, len_current);
					new_str_after = malloc(len_after * sizeof(char));
					strncpy(new_str_after, end+2, len_after-1);
					new_str_after = strcat(new_str_after, ",");
					new_str_after[len_after-1] = '\0';
				}
				printf("The string after the operation is: %s\n", new_str_after);

			}
			new_str_current = malloc(len_current * sizeof(char));
			strncpy(new_str_current, start+1, len_current-1);
			new_str_current[len_current-1] = '\0';
			printf("The string at the operation is: %s\n", new_str_current);
			result[0] = realloc(result[0], (len_before+len_after+len_current-2) * sizeof(char));
			memset(result[0], '\0', (len_before+len_after+len_current-2) * sizeof(char));
			if (len_before > 1)
			{
				result[0] = strcat(result[0], new_str_before);
				free(new_str_before);
			}
			if (len_after > 1)
			{
				result[0] = strcat(result[0], new_str_after);
				free(new_str_after);
			}
			result[0] = strcat(result[0], new_str_current);
			free(new_str_current);
			printf("str to return is: %s\n", result[0]);
			return result;
		}
		else if (start == arrow)
		{
			printf("There is a problem, start is equal to arrow\n");
			return result;
		}
		else if (start > arrow)
		{ 
			printf("\nOperation R1 on the right side\n");
			len_before = arrow-str+2; /*We will append ',' to this*/
			len_after = start-arrow; /*No comma included*/
			len_after2 = length_string-(end-str); /*May be 0 */
			len_current = end-start+1;
			if (&str[0] == arrow)
			{
				len_before--;
			}
			printf("Length10 is :%d %d %d %d\n", len_before, len_after, len_after2, len_current);
			if (len_before > 1)
			{
				new_str_before = malloc(len_before * sizeof(char));
				strncpy(new_str_before, str, len_before-2);
				new_str_before[len_before-2] = ',';
				new_str_before[len_before-1] = '\0';
				printf("The string before the operation is: %s\n", new_str_before);
			}
			if (len_after > 1)
			{
				new_str_after = malloc(len_after * sizeof(char));
				strncpy(new_str_after, arrow, len_after-1);
				new_str_after[len_after-1] = '\0';
				printf("The string after the operation is: %s\n", new_str_after);
			}
			if (len_after2 > 1)
			{
				new_str_after2 = malloc(len_after2 * sizeof(char));
				strncpy(new_str_after2, end+1, len_after2-1);
				new_str_after2[len_after2-1] = '\0'; 
				printf("The string after2 the operation is: %s\n", new_str_after2);
			}
			new_str_current = malloc(len_current * sizeof(char));
			strncpy(new_str_current, start+1, len_current-1);
			new_str_current[len_current-1] = '\0';
			printf("The string at the operation is: %s\n", new_str_current);
			if (len_after <= 1 && len_after2 <= 1)
			{
		/*		printf("No len_after and len_after2, so appended # to the end\n");*/
				len_after++;
				new_str_after = malloc(2 * sizeof(char));
				new_str_after[0] = '#';
				new_str_after[1] = '\0';
			}
			else if (len_after <= 1)
			{
				printf("THIS PART IS IMPORTANT\n");
				new_str_after2[0] = '#';
			}
			result[0] = realloc(result[0], (len_before+len_after+len_after2+len_current-3) * sizeof(char));
			memset(result[0], '\0', (len_before+len_after+len_current-2) * sizeof(char));
			if (len_before > 1)
			{
				result[0] = strcat(result[0], new_str_before);
				free(new_str_before);
			}
			result[0] = strcat(result[0], new_str_current);
			free(new_str_current);
			if (len_after > 1)
			{
				result[0] = strcat(result[0], new_str_after);
				free(new_str_after);
			}
			if (len_after2 > 1)
			{
				result[0] = strcat(result[0], new_str_after2);
				free(new_str_after2);
			}
			printf("Str to return from R1 is %s\n", result[0]);
			return result;
		}
	}
	else if(*start == '(')
	{
		if (*(start+1) == '(') 
		{
			index_of_operation = find_parenthesis_end(start+1)+1;
		}
		else if(isalpha(*(start+1))) 
		{
			index_of_operation = start+2;
		}
		else 
		{
			for(; *(start+1+how_many_negations) == '-';how_many_negations++);
			if (*(start+1+how_many_negations) == '(')
			{
				index_of_operation = find_parenthesis_end(start+1+how_many_negations)+1;
			}
			else
			{
				index_of_operation = start+2+how_many_negations;
			}
		}

		if(*(index_of_operation) == '&')
		{
			what_is_operation = 1;
		}
		else if (*(index_of_operation) == '|')
		{
			what_is_operation = 2;
		}
		else if (*(index_of_operation) == '>')
		{
			what_is_operation = 3;
		}

		if ((what_is_operation == 1 && end < arrow) || (what_is_operation == 2 && start > arrow))
		{
			printf("R2 is called\n");
			/* Burası tek tip, dönülen operatör adresini düzenlemek olacak */
			*(index_of_operation) = ',';
			printf("& is changed to , New string is\n%s\n", str);
			len_before = start-str+1;
			len_current = end-start;
			len_after = &str[length_string-1]-end+1;
			if (len_before > 1)
			{
				new_str_before = malloc(len_before * sizeof(char));
				strncpy(new_str_before, str, len_before-1);
				new_str_before[len_before-1] = '\0';
				printf("New str before is %s\n", new_str_before);
			}
			if (len_after > 1)
			{
				new_str_after = malloc(len_after * sizeof(char));
				strncpy(new_str_after, end+1, len_after);
				printf("New str after is %s\n", new_str_after);
			}
			new_str_current = malloc(len_current * sizeof(char));
			strncpy(new_str_current, start+1, len_current-1);
			new_str_current[len_current-1] = '\0';
			printf("New str current is %s\n", new_str_current);
			result[0] = realloc(result[0], (len_before+len_after+len_current-2) * sizeof(char));
			memset(result[0], '\0', (len_before+len_after+len_current-2) * sizeof(char));
			if (len_before > 1)
			{
				printf("Before exists %s %d\n", new_str_before, strlen(new_str_before));
				result[0] = strcat(result[0], new_str_before);
				free(new_str_before);
			}
			if (len_current > 1)
			{
				printf("Current exists %s %d\n", new_str_current, strlen(new_str_current));
				result[0] = strcat(result[0], new_str_current);
				free(new_str_current);
			}
			if (len_after > 1)
			{
				printf("After exists %s %d\n", new_str_after, strlen(new_str_after));
				result[0] = strcat(result[0], new_str_after);
				free(new_str_after);
			}
			printf("String to return from R2 iso %s\n", result[0]);
			return result;
		}
		/* 1 &, 2 |, 3 > */
		else if (what_is_operation == 2 && end < arrow)
		{
			printf("R3 is called\n");
			len_before = (start-str)+1;
			len_current = index_of_operation-start;
			len_current2 = end-index_of_operation;
			len_after = length_string-(end-str);
			if (len_before > 1)
			{
				new_str_before = malloc(len_before * sizeof(char));
				strncpy(new_str_before, str, len_before-1);
				new_str_before[len_before-1] = '\0';
				printf("Str before is %s\n", new_str_before);
			}
			if (len_after > 1)
			{
				new_str_after = malloc(len_after * sizeof(char));
				strncpy(new_str_after, end+1, len_after-1);
				new_str_after[len_after-1] = '\0';
				printf("Str after is %s\n", new_str_after);
			}
			new_str_current = malloc(len_current * sizeof(char));
			strncpy(new_str_current, start+1, len_current-1);
			new_str_current[len_current-1] = '\0';
			printf("Str current1 is %s\n", new_str_current);
			new_str_current2 = malloc(len_current2 * sizeof(char));
			strncpy(new_str_current2, index_of_operation+1, len_current2-1);
			new_str_current2[len_current2-1] = '\0';
			printf("Str current2 is %s\n", new_str_current2);
			result[0] = realloc(result[0], (len_before + len_current + len_after - 2) * sizeof(char));
			result[1] = realloc(result[1], (len_before + len_current2 + len_after -2) * sizeof(char));
			memset(result[0], '\0', (len_before+len_after+len_current-2) * sizeof(char));
			memset(result[1], '\0', (len_before+len_after+len_current2-2) * sizeof(char));
			if (len_before > 1)
			{
				printf("Adding string before\n");
				result[0] = strcat(result[0], new_str_before);
				result[1] = strcat(result[1], new_str_before);
				free(new_str_before);
			}
			result[0] = strcat(result[0], new_str_current);
			free(new_str_current);
			result[1] = strcat(result[1], new_str_current2);
			free(new_str_current2);
			if (len_after > 1)
			{
				printf("Adding string after\n");
				result[0] = strcat(result[0], new_str_after);
				result[1] = strcat(result[1], new_str_after);
				free(new_str_after);
			}
			printf("The string 1 to return is %s\nThe string 2 to return is %s\n", result[0], result[1]);
			return result;
		}
		else if (what_is_operation == 1 && start > arrow)
		{
			printf("R4 is called\n");
			len_before = (start-str)+1;
			len_current = index_of_operation-start;
			len_current2 = end-index_of_operation;
			len_after = length_string-(end-str);
			if (len_before > 1)
			{
				new_str_before = malloc(len_before * sizeof(char));
				strncpy(new_str_before, str, len_before-1);
				new_str_before[len_before-1] = '\0';
				printf("Str before is %s\n", new_str_before);
			}
			if (len_after > 1)
			{
				new_str_after = malloc(len_after * sizeof(char));
				strncpy(new_str_after, end+1, len_after-1);
				new_str_after[len_after-1] = '\0';
				printf("Str after is %s\n", new_str_after);
			}
			new_str_current = malloc(len_current * sizeof(char));
			strncpy(new_str_current, start+1, len_current-1);
			new_str_current[len_current-1] = '\0';
			printf("Str current1 is %s\n", new_str_current);
			new_str_current2 = malloc(len_current2 * sizeof(char));
			strncpy(new_str_current2, index_of_operation+1, len_current2-1);
			new_str_current2[len_current2-1] = '\0';
			printf("Str current2 is %s\n", new_str_current2);
			result[0] = realloc(result[0], (len_before + len_current + len_after - 2) * sizeof(char));
			result[1] = realloc(result[1], (len_before + len_current2 + len_after -2) * sizeof(char));
			memset(result[0], '\0', (len_before+len_after+len_current-2) * sizeof(char));
			memset(result[1], '\0', (len_before+len_after+len_current2-2) * sizeof(char));
			if (len_before > 1)
			{
				printf("Adding string before\n");
				result[0] = strcat(result[0], new_str_before);
				result[1] = strcat(result[1], new_str_before);
				free(new_str_before);
			}
			result[0] = strcat(result[0], new_str_current);
			free(new_str_current);
			result[1] = strcat(result[1], new_str_current2);
			free(new_str_current2);
			if (len_after > 1)
			{
				printf("Adding string after\n");
				result[0] = strcat(result[0], new_str_after);
				result[1] = strcat(result[1], new_str_after);
				free(new_str_after);
			}
			printf("The string 1 to return is %s\nThe string 2 to return is %s\n", result[0], result[1]);
			return result;
		}
		else if (what_is_operation == 3)
		{
			printf("R5 is called\n");
			len_before = start-str+1;
			len_current = end-start+3;
			len_after = length_string-(end-str);
			*(index_of_operation) = '|';
			/* 
			char a2[] = "A,B#(-A>B),F,G";
			8 lazım
			start 4, end 9
			*/
			printf("String is %s\n", str);
			if (len_before > 1)
			{
				new_str_before = malloc(len_before * sizeof(char));
				strncpy(new_str_before, str, len_before-1);
				new_str_before[len_before-1] = '\0';
				printf("Str before is %s\n", new_str_before);
			}
			if (len_after > 1)
			{
				new_str_after = malloc(len_after * sizeof(char));
				strncpy(new_str_after, end+1, len_after-1);
				new_str_after[len_after-1] = '\0';
				printf("Str after is %s\n", new_str_after);
			}
			new_str_current = malloc(len_current * sizeof(char));
			new_str_current[0] = '(';
			new_str_current[1] = '-';
			strncpy(new_str_current+2, start+1, len_current-3);
			new_str_current[len_current-1] = '\0';
			printf("Str current is %s\n", new_str_current);
			result[0] = realloc(result[0], (len_before + len_current + len_after - 2) * sizeof(char));
			memset(result[0], '\0', (len_before+len_after+len_current-2) * sizeof(char));
			if (len_before > 1)
			{
				result[0] = strcat(result[0], new_str_before);
				free(new_str_before);
			}
			result[0] = strcat(result[0], new_str_current);
			free(new_str_current);
			if (len_after > 1)
			{
				result[0] = strcat(result[0], new_str_after);
				free(new_str_after);
			}
			return result;
		}
		else 
		{
			printf("Couldn't identify operation, exiting\n");
		}
	}
	else
	{
		printf("ERROR, Start is neither - nor (, exiting\n");
	}
}

int randomfunc(int a)
{
	return a+5;
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
}

int check_if_one_char(char *str, char *index)
{
	int length_string = strlen(str), left = -1, right = -1, has_right_element = -1;
	if (index == &str[length_string-1])
	{
		has_right_element = 0;
	}
	else 
	{
		has_right_element = 1;
	}
	if (*(index-1) == ',' || *(index-1) == '#')
	{
		left = 1;
	}
	else 
	{
		left = 0;
	}
	if (has_right_element)
	{
		if (*(index+1) == ',')
		{
			right = 1;
		}
		else
		{
			right = 0;
		}
	}
	return (right && left);
}

int check_if_finished(char *str)
{
	char *arrow_index = strchr(str, '#');
	char *char_index;
	int flag = 0, length_string = strlen(str);
	char *ptr_forw = str;
	char *ptr_back;
	printf("\n");
	if (arrow_index == &str[length_string-1])
	{
		printf("No element after #, exiting");
		return -1;
	}
	/* 
	char a6[] = "A,B#B,(-C|A)";
	char a7[] = "A,B#";
	char a3[] = "A,B#(--B|C)";
	*/
	while (ptr_forw < arrow_index) /* This loop ends as ptr_forw = arrow_index */
	{
		ptr_back = ptr_forw;
		ptr_forw = strchr(ptr_forw+1, ',');
		if (!ptr_forw)
		{
			printf("No commas found, I'm at the left side\n");
			ptr_forw = arrow_index;
		}
		printf("New orders back and forward are %d %d\n", ptr_back-str, ptr_forw-str);
		if (ptr_forw > arrow_index)
		{
			printf("# asildi\n");
			ptr_forw = arrow_index;
		}
		if (ptr_forw - ptr_back > 2)
		{
			printf("Longer than a character, incrementing flag\n");
			flag++;
			continue;
		}
		char_index = strchr(arrow_index+1, *(ptr_forw-1));
		if (char_index > arrow_index && check_if_one_char(str, char_index))
		{
			printf("Found the char %c\n", *char_index);
			return 1;
		}
	}
	while (ptr_forw >= arrow_index)
	{
		ptr_back = ptr_forw;
		ptr_forw = strchr(ptr_forw+1, ',');
		if (!ptr_forw)
		{
			printf("Finished all commas, looking at the last element\n");
			ptr_forw = &str[length_string-1];
			if (ptr_forw - ptr_back > 1)
			{
				printf("Longer than a character, incrementing flag\n");
				flag++;
			}
			break;
		}
		printf("New orders back and forward are %d %d\n", ptr_back-str, ptr_forw-str);
		if (ptr_forw - ptr_back > 2)
		{
			printf("Longer than a character, incrementing flag\n");
			flag++;
			continue;
		}
	}
	if (flag == 0)
	{
		printf("Flag is 0 and returning -1\n");
		return -1;
	}
	else
	{
		printf("There are changes to be made, returning 0\n");
		return 0;
	}
}

