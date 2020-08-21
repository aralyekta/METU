/*#include "loop.h"*/
#include <stdio.h>
#include <stdlib.h>

char array_var[100000];
int array_start[100000];
int array_stop[100000];
int array_step[100000];
int array_current_val[100000];
int level_max = 0;
int flag = 0;

int loop_variable_value(char c){
	int i;
	for (i = 0; i < level_max;i++){
		if (c == array_var[i]){
		break;
		}
	}
	return array_current_val[i];
}

void loop_continue(char c){
	int i,counter;
	for (i = 0; i < level_max;i++){
		if (c == array_var[i]){
		break;
		}
	}
	printf("Loop continue function used for level:%d\n", i);
	array_current_val[i] += array_step[i];
	for (counter = i+1; counter <= level_max; counter++){
		printf("Current value changed from %d to %d \n", array_current_val[counter], array_start[counter]);
		array_current_val[counter] = array_start[counter];
	}
	flag = 1;
}

void loop_execute(void){
	printf("X:%d r:%d Y:%d\n", loop_variable_value('X'),loop_variable_value('r'), loop_variable_value('Y'));
	if ((loop_variable_value('X')+loop_variable_value('r')+loop_variable_value('Y'))%5 == 0){
		printf("JUST MAGIC OF FIVE HAPPENED!... Continuing with next 'r' value.\n");
		loop_continue('r');
	}
}


void eval_func(int level){
	char var_curr;
	int start_curr;
	int stop_curr;
	int step_curr;
	int val_curr;
	var_curr = array_var[level];
	start_curr = array_start[level];
	val_curr = array_current_val[level];
	stop_curr = array_stop[level];
	step_curr = array_step[level];
	if (step_curr < 0){
		for (;val_curr >= stop_curr; val_curr += step_curr, array_current_val[level] = val_curr){
			if(flag == 1){
				printf("Flag is :%d\n", flag);
				val_curr = array_current_val[level];
			}
/*			printf("The current value for %c is: %d\n", var_curr, val_curr);*/
			if (level < level_max){
				eval_func(level+1);
			}
			else if (level == level_max){
				loop_execute();
			}
		}
		array_current_val[level] = start_curr;
	}
	else if (step_curr > 0){
		for (;val_curr <= stop_curr; val_curr += step_curr, array_current_val[level] = val_curr){
			if (flag == 1){
				printf("Flag is :%d\n", flag);
				val_curr = array_current_val[level];
			}
/*			printf("The current value for %c is: %d\n", var_curr, val_curr);*/
			if (level < level_max){
				eval_func(level+1);
			}
			else if (level == level_max){
				loop_execute();
			}
			val_curr = array_current_val[level];
		}
		array_current_val[level] = start_curr;
	}
}

int main(){
	FILE *fp;
	int i;
	int line = 0;
	fp = fopen("input.txt", "r");
	while(fscanf(fp, " %c %d %d %d", &array_var[line], &array_start[line], &array_stop[line], &array_step[line]) ==4){
		array_current_val[line] = array_start[line];
		line++;
	}
	fclose(fp);
	level_max = line-1;
	/*for (i=0;i < line;i++){
		printf("%c %d %d %d\n", array_var[i], array_start[i], array_stop[i], array_step[i]);
	}
	*/
	eval_func(0);
}
