#include <stdio.h>

int main(){
	int count, count_in;
	char ch;
	char array_var[255];
	int array_start[255], array_stop[255], array_step[255];
	count = 0, count_in = 0;
	while(scanf("%c",&ch)!= EOF){
		if ((int)ch == 10){
			continue;
		}
		array_var[count_in] = ch;
		scanf(" %d %d %d", &array_start[count_in], &array_stop[count_in], &array_step[count_in]);
		printf("Scanned %c %d %d %d\n", array_var[count_in], array_start[count_in], array_stop[count_in], array_step[count_in]);
		count_in++;
	}
	while (count < count_in){
		printf("Count: %d\n", count);
		printf("The values of %c are %d %d %d\n", array_var[count], array_start[count], array_stop[count], array_step[count]);
		count++;
	}
	return 0;
}
