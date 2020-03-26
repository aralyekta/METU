extern void loop_execute(void);{
void loop_execute(void){
	printf("X:%d r:%d Y:%d a:%d\n", loop_variable_value('X'),loop_variable_value('r'), loop_variable_value('Y'), loop_variable_value('a'));
	if ((loop_variable_value('X')+loop_variable_value('r')+loop_variable_value('Y')+loop_variable_value('a'))%5 == 0){
		printf("JUST MAGIC OF FIVE HAPPENED!... Continuing with next 'r' value.\n");
		loop_continue('Y');
	}
}

/*
void loop_execute(void){
	printf("X:%d r:%d Y:%d a:%d\n", loop_variable_value('X'), loop_variable_value('r'), loop_variable_value('Y'), loop_variable_value('a'));
}
*/
}
int loop_variable_value(char c);
void loop_continue(char c);
