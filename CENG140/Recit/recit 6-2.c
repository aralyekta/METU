#include <stdlib.h>
#include <stdio.h>

/* String null olmayacak, en az 1 char olacak ve \0 ile bitecek.
 * Delimeter bos olmayacak
 * Delimeter ardisik bulunmayacak stringde
 * 2D array donecek, her row bir partition ve \0 ile bitecek, delimeter olmayacak partitionlarda
 * Delimeter yoksa tek parca donecek
 * Delimeter stringin en basinda veya sonundaysa uclardaki bos stringleri de doneceksin partition olarak
 * 2D arrayin en son elemani (rowu) \0 olacak. */

/*TAMAM Toplam delimeteri ve maks uzunlugu say.
 *TAMAM Rowu delimeter sayisi+1 ve colu maks uzunluk+1 olan bir array malloc et
 *TAMAM Delimeter gorene kadar elemanlari ekle, en sona \0 koy
 *TAMAM En son rowa da \0 ekle*/

char** split(char *str, char delimeter);

int main()
{	
	char* str = "You either die a hero, or you live long enough to see yourself become the villain.";
	char delimeter = ' ';
	split(str, delimeter);
	return 0;
}

char** split(char *str, char delimeter)
{
	int delim = 0, max = 0, current = 0, i, j= 0, c= 0;
	char ** matrix;
	for (i = 0; str[i] != '\0'; i++)
	{
		printf("Currently looking for elem %c\n", str[i]);
		if (str[i] == delimeter)
		{
			delim++;
			if (current > max)
			{
				max = current;
			}
			current = 0;
		}
		else 
		{
			current++;
		}
	}
	if (current > max)
		max = current;
	/* Finds row and col numbers.
	 * row = delim+2
	 * col = max+1 */
	matrix = malloc((delim+2) * sizeof(char *));
	for (i = 0; i < delim+2; i++)
	{
		matrix[i] = malloc((max+1)*sizeof(char));
	}
	for (i = 0, c = 0; i < delim+1; i++, c++)
	{
		for (j = 0; (i != delim && str[c] != delimeter) || (i == delim && str[c] != '\0') ; c++, j++)
		{
			matrix[i][j] = str[c];
		}
		matrix[i][j] = '\0';
	}
	matrix[delim+1][0] = '\0';
	for (i = 0; i < delim+1; i++)
	{
		printf("%s\n", matrix[i]);
	}
	return matrix;
}
