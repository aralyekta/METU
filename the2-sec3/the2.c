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
char *solve(char *);
char *find_parenthesis_end(char *);

int main()
{
	char arr1[] = "(A&B),B#D,E,C";
	char *ptr1 = arr1;
	char arr2[] = "-A#F";
	char *ptr2 = arr2;
	char arr3[] = "-A,C#B";
	char *ptr3 = arr3;
	char arr4[] = "(A|B)#C,A";
	char *ptr4 = arr4;
	char arr5[] = "(A&B),((C|D)>(A|B))#(C&D),(A&B)";
	char *ptr5 = arr5;
	char arr6[] = "B,C,D,(A|B)#F";
	char *ptr6 = arr6;
	char arr7[] = "B#F,D,-A";
	char *ptr7 = arr7;
	char arr8[] = "B#(F&D),-A";
	char *ptr8 = arr8;
	char arr9[] = "B,D,-((A|B)>D)#C,E";
	char *ptr9 = arr9;
	char arr10[] = "B,D#C,E,-((A|B)>D),F";
	char *ptr10 = arr10;
	char arr11[] = "B,-((A|B)>D),D#C,E";
	char *ptr11 = arr11;
/*
	while (!check_if_finished(ptr))
	{
	
	}
	*/
	solve(ptr10);
	return 0;
}

char *find_parenthesis_end(char *str)
{
	int amount = 0;
	while (1)
	{
		if (*str == '(')
		{
			amount++;
		}
		else if (*str == ')')
		{
			amount--;
		}
		if (amount == 0)
		{
			return str;
		}
		str++;
	}
}

char *solve(char *str)
{
	/* String manipulasyonunu 1 kere yapar.
	 * Yeni olusacak string icin yer malloc edip eskisini free eder. Yeni stringi doner. */
	char *start = str;
	char *arrow = strchr(str, '#');
	char *end = strchr(str, ',');
	char *operator;
	char *new_str_before;
	char *new_str_current;
	char *new_str_after;
	char *new_str_after2;
	char *str_to_return;
	int length_string = strlen(str);
	long len_before, len_after, len_current, len_after2;
	/*printf("Entered the loop for string %s\n", str);*/
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
/*	printf("Start and end address and value is %p,%p,%ld,%ld\n", start, end, start-str, end-str);*/
	while (end == start)
	{
/*		printf("Start and end address and value is %p,%p,%ld,%ld\n", start, end, start-str, end-str);*/
		if (*end == str[length_string-1])
		{
/*			printf("Solve function called for non solvable string, exiting.\n");*/
			return str;
		}
		start += 2;
		end = strchr(start, ',');
		if (!end)
		{
/*			printf("No commas found\n");*/
			if (start < arrow)
			{
				end = arrow-1;
/*				printf("Start is before the arrow, the new end value is %ld\n", end-str);*/
			}
			else if (start > arrow)
			{
				end = &str[length_string-1];
				/*printf("Start is before the arrow, the new end value is %ld\n", end-str);*/
			}
		}
		else if (end > arrow && start < arrow)
		{
			/*printf("Commas found\n");*/
			end = arrow-1;
/*			printf("The order of the end value is %ld\n", end-str);*/
		}
		else 
		{
			/*printf("No problems at all\n");*/
			end--;
/*			printf("The order of the end value is %ld\n", end-str);*/
		}
	}
	printf("END OF LOOP, Start and end address and value is %ld %ld\n", start-str, end-str);
	/* "B,D,-((A|B)>D)#C,E" */
	if (*start == '-')
	{
		if (start < arrow)
		{
			printf("Operation R1 on the left side\n");
			len_before = start-str-1; 
			len_after = length_string-1-(end-str)+1;
			len_current = end-start;
			str_to_return = malloc((len_before+len_after+len_current) * sizeof(char));
			new_str_before = malloc(len_before * sizeof(char));
			new_str_before = memcpy(new_str_before, str, len_before);
			printf("The string before the operation is: %s\n", new_str_before);
			new_str_after = malloc(len_after * sizeof(char));
			new_str_after = memcpy(new_str_after, end+1, len_after);
			new_str_after = strcat(new_str_after, ",");
			printf("The string after the operation is: %s\n", new_str_after);
			new_str_current = malloc(len_current * sizeof(char));
			new_str_current = memcpy(new_str_current, start+1, len_current);
			printf("The string at the operation is: %s\n", new_str_current);
			str_to_return = strcat(str_to_return, new_str_before);
			str_to_return = strcat(str_to_return, new_str_after);
			str_to_return = strcat(str_to_return, new_str_current);
			printf("str to return is: %s\n", str_to_return);
		}
		else if (start == arrow)
		{
			printf("There is a problem, start is equal to arrow\n");
		}
		else if (start > arrow)
		{
			/* "B,D#C,E,-((A|B)>D),F" */
			printf("Operation R1 on the right side\n");
			len_before = arrow-str+1; /*We will append ',' to this*/
			len_after = start-arrow-1; /*No comma included*/
			len_after2 = length_string-(end-str)-1; /*May be 0 */
			len_current = end-start;
			str_to_return = malloc((len_before+len_after+len_after2+len_current) * sizeof(char));
			new_str_before = malloc(len_before * sizeof(char));
			new_str_before = memcpy(new_str_before, str, len_before-1);
			new_str_before = strcat(new_str_before, ",");
			printf("The string before the operation is: %s\n", new_str_before);
			new_str_after = malloc(len_after * sizeof(char));
			new_str_after = memcpy(new_str_after, arrow, len_after);
			printf("The string after the operation is: %s\n", new_str_after);
			if (len_after2)
			{
				new_str_after2 = malloc(len_after2 * sizeof(char));
				new_str_after2 = memcpy(new_str_after2, end+1, len_after2);
				printf("The string after2 the operation is: %s\n", new_str_after2);
			}
			new_str_current = malloc(len_current * sizeof(char));
			new_str_current = memcpy(new_str_current, start+1, len_current);
			printf("The string at the operation is: %s\n", new_str_current);
			str_to_return = strcat(str_to_return, new_str_before);
			str_to_return = strcat(str_to_return, new_str_current);
			str_to_return = strcat(str_to_return, new_str_after);
			if (len_after2)
			{
				str_to_return = strcat(str_to_return, new_str_after2);
			}
			printf("Str to return is %s\n", str_to_return);
		}
	}
}

int check_if_finished(char *str)
{
	char *arrow_index = strchr(str, '#');
	char *char_index;
	int flag = 0;
	char *ptr_forw = str;
	char *ptr_back;
	while (ptr_forw < arrow_index)
	{
		/*printf("Entered the loop\n");*/
		ptr_back = ptr_forw;
		ptr_forw = strchr(ptr_forw+1, ',');
		/*printf("New orders back and forward are %d %d\n", ptr_back-str, ptr_forw-str);*/
		if (ptr_forw > arrow_index)
		{
			/*printf("# asildi\n");*/
			ptr_forw = arrow_index;
		}
		if (ptr_forw - ptr_back > 2)
		{
			/*printf("Longer than a character, incrementing flag\n");*/
			flag++;
			continue;
		}
		char_index = strchr(arrow_index+1, *(ptr_forw-1));
		if (char_index)
		{
			/*printf("Found the char %c\n", *char_index);*/
			return 1;
		}
	}
	if (flag == 0)
	{
		/*printf("Flag is 0 and returning -1\n");*/
		return -1;
	}
	else
	{
		/*printf("There are changes to be made, returning 0\n");*/
		return 0;
	}
}
