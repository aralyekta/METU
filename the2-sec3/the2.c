/* inputta whitespace yok, ama blanklere karsi yazabilirsin.
 * yeni string olusturmak icin malloc kullan, eski stringleri free'le.
 * maximum input 200 karakter
 * struct yok
 * operatoru tespit et, operator oncesini oldugu gibi koy. o operatorde yapacagin islemi yap, o operatorden sonraki virgulden sonrasını da fonksiyona sal
 * Recursion bitirme sarti da r6 ya da r7
 * soldan saga cozecegiz, harf olusmadan virgulu gecmeyecegiz
 * r3'te ayri ayri cagirip ve'sini alip devam edicez. ve'si 0 gelirse bitiricez
 * -((P&Q)>(Q>P)),((A|Q)>(R&(P|B))),-R#-P,-(A&(P|B)),((P&B)|(Q>P))
 *  string vs deger donmeyi farklilastir
 *  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_if_finished(char *);
char *solve(char *);
char *find_parenthesis_end(char *);

int main()
{
	char arr[] = "(A&B),B#D,E,C";
	char *ptr = arr;
	while (!check_if_finished(ptr))
	{
	
	}
	return check_if_finished(ptr);
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
	char *end = strchr(str, ',')-1;
	char *operator;
	char *new_str;
	int length_string = strlen(str);
	long len_before, len_after;
	while (end == start)
	{
		if (end == str[length_string-1])
		{
			printf("Solve function called for non solvable string, exiting.\n");
			return str;
		}
		start += 2;
		end = strchr(start, ',')-1;
		if (!end && start >= arrow)
		{
			printf("Solvable part is the last one, right side\n");
			end = str[length_string-1];
		}
		else if (end > arrow)
		{
			printf("Solvable part is the last one, left side\n");
			end = arrow-1;
		}
	}
	printf("Loop ended for characters %c %c and orders %ld %ld\n", *start, *end, start-str, end-str);
	if (*(start+1) == '-')
	{
		new_str = malloc((length_string-1)*sizeof(char));
		len_after = start-str;
		len_before = length_string-
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
