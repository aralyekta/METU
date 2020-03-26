/*#include "loop.h"*/
#include <stdio.h>
#include <stdlib.h>

char array_var[500];
int array_start[500];
int array_stop[500];
int array_step[500];
int array_current_val[500];
int *pointer_current_val = array_current_val;
int level_max = 0;
int flag = 0;

int loop_variable_value(char c){
	int i;
	for (i = 0; i < level_max;i++){
		if (c == array_var[i]){
		break;
		}
	}
	return pointer_current_val[i]; 
}

void loop_execute(void){
	printf("X:%d r:%d Y:%d\n",loop_variable_value('X'), loop_variable_value('r'), loop_variable_value('Y'));
}

void loop_continue(char c){
	int i,counter;
	for (i = 0; i < level_max;i++){
		if (c == array_var[i]){
		break;
		}
	}
	if (array_step[i] > 0 && pointer_current_val[i] >= array_stop[i]){
		pointer_current_val[i] = array_start[i];
		pointer_current_val[i-1] += array_step[i-1];
	}
	else if (array_step[i] < 0 && pointer_current_val[i] <= array_stop[i]){
		pointer_current_val[i] = array_start[i];
		pointer_current_val[i-1] += array_step[i-1];
	}
	else {
	pointer_current_val[i] += array_step[i];
	}
	for (counter = i+1; counter <= level_max; counter++){
		pointer_current_val[counter] = array_start[counter];
	}
	flag = 1;
}

void eval_func(int level){
	char var_curr;
	int start_curr;
	int stop_curr;
	int step_curr;
	int *val_curr;
	var_curr = array_var[level];
	start_curr = array_start[level];
	stop_curr = array_stop[level];
	step_curr = array_step[level];
	pointer_current_val[level] = array_start[level];
	if (step_curr < 0){
		while(pointer_current_val[level]>= stop_curr){
			if (level < level_max){
				eval_func(level+1);
			}
			else if (level == level_max){
				loop_execute();
			}
			if (flag == 1){
				flag = 0;
				continue;
			}
			pointer_current_val[level]+= step_curr;
		}
		pointer_current_val[level] = array_start[level];
	}
	else if (step_curr > 0){
		while(pointer_current_val[level]<= stop_curr){
			if (level < level_max){
				eval_func(level+1);
			}
			else if (level == level_max){
				loop_execute();
			}
			if (flag == 1){
				flag = 0;
				continue;
			}
			pointer_current_val[level]+= step_curr;
		}
		pointer_current_val[level] = array_start[level];
	}
}

int main(){
	int line = 0, counter = 0;
	char ch;
	while(scanf("%c",&ch)!=EOF){
		if ((int)ch == 10)
			continue;
		array_var[line] = ch;
		scanf(" %d %d %d", &array_start[line], &array_stop[line], &array_step[line]);
		line++;
	}
	while (counter < line){
	printf("The value for %c are %d %d %d\n", array_var[counter], array_start[counter], array_stop[counter], array_step[counter]);
	counter++;
	}
	level_max = line-1;
	eval_func(0);
}
