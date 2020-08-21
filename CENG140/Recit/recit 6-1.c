#include <stdio.h>
#include <stdlib.h>

/*TAMAM null verilmeyecek ama empty verilebilir
 *TAMAM \0 ile bittikleri garanti
 *TAMAM char ptr dönmelisin, döndüğün str \0 ile bitmeli
 *TAMAM strlerden birisi biterse digerini direkt yig (merge sort gibi bir sey olabilir)
 *TAMAM white space'leri ignore et*/
char* pile(char* str1, char* str2);

int main()
{
	char* str1 = "";
	char* str2 = " e fgx";
	printf("%s %s\n", str1, str2);
	pile(str1, str2);
	return 0;
}

char* pile(char* str1, char* str2)
{
	int c, i = 0, j = 0, len1_sum = 0, len1 = 0, len2_sum = 0, len2 = 0;
	char *result;
	for (c = 0; str1[c] != '\0' ; c++, len1_sum++)
	{
		if (str1[c] != ' ')
		{
			len1++;
		}
	}
	for (c = 0; str2[c] != '\0'; c++, len2_sum++)
	{
		if (str2[c] != ' ')
		{
			len2++;
		}
	}
	c = 0;
	result = malloc((len1+len2)*sizeof(char)+1);
	while(i < len1_sum && j < len2_sum)
	{
		while(str1[i] == ' ')
			{
			i++;
		}
		result[c] = str1[i];
		c++;
		i++;
		while(str2[j] == ' ')
		{
			j++;
		}
		result[c] = str2[j];
		c++;
		j++;
	}
	if (i >= len1_sum)
	{
		while (j < len2_sum)
		{
			while (str2[j] == ' ')
			{
				j++;
			}
			result[c] = str2[j];
			c++;
			j++;
		}
	}
	else if (j >= len2_sum)
	{
		while (i < len1_sum)
		{
			while (str1[i] == ' ')
			{
				i++;
			}
			result[c] = str1[i];
			i++;
			c++;
		}
	}
	result[c] = '\0';
	return result;
}
