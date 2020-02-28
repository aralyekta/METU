#include <stdio.h>

int main ()
{
    int task,task_amount, iterator;
    char operation, currency;
    double total_dollar, total_euro, currency_amount_per_op, euro_exc, dollar_exc;
    long double initial_balance;
    float penalty, type1_val, type2_val, type3_val, type4_val, point;
    char exam, ayt_type;
    int type1, type2, type3, type4;
    total_dollar = 0;
    total_euro = 0;


    scanf("%d", &task);

    if(task == 1) {
	    scanf("%Lf %lf %lf", &initial_balance, &euro_exc, &dollar_exc);
	    scanf("%d", &task_amount);
	    for (iterator=0;iterator < task_amount;iterator++){
		    scanf(" %c %c %lf", &operation, &currency, &currency_amount_per_op);
		    if (currency == 'D'){
			    if (operation == 'D'){
				    total_dollar += currency_amount_per_op;
			    }
			    else if (operation == 'W'){
				    total_dollar -=  currency_amount_per_op;
			    }
		    }
		    else if (currency == 'E'){
			    if (operation == 'D'){
				    total_euro += currency_amount_per_op;
			    }
			    else if (operation == 'W'){
				    total_euro -= currency_amount_per_op;
		    }
	    }
	    }
		    initial_balance += total_dollar * dollar_exc;
		    initial_balance += total_euro * euro_exc;
		    printf("Final balance: %.2Lf TL.", initial_balance);
        
        
    } else if(task == 2) {
	    scanf(" %c %c %f", &exam, &ayt_type, &penalty);
	    if (exam == 'T'){
		    scanf("%d %f %d %f %d %f %d %f", &type1, &type1_val, &type2, &type2_val, &type3, &type3_val, &type4, &type4_val);
		    point = type1*type1_val + type2*type2_val + type3*type3_val + type4*type4_val;
		    point -= ((40 - type1)*type1_val + (40 - type2)*type2_val + (40- type3)*type3_val + (40-type4)*type4_val) * penalty;
		    printf("T result: %.2f points.", point);
	    }
	    else if (exam == 'A'){
		    if (ayt_type == 'E'){
 		    scanf("%d %f %d %f %d %f %d %f", &type1, &type1_val, &type2, &type2_val, &type3, &type3_val, &type4, &type4_val);
		    point = type1*type1_val + type2*type2_val + type3*type3_val + type4*type4_val;
		    point -= ((30 - type1)*type1_val + (30 - type2)*type2_val + (30- type3)*type3_val + (30-type4)*type4_val) * penalty;
		    printf("A-E result: %.2f points.", point);

	    }
		    else {
			    if (ayt_type == 'C'){
 				scanf("%d %f %d %f", &type1, &type1_val, &type2, &type2_val);
		    		point = type1*type1_val + type2*type2_val;
		    		point -= ((30 - type1)*type1_val + (30 - type2)*type2_val) * penalty;
		    		printf("A-C result: %.2f points.", point);
			    }
			    else if (ayt_type == 'O'){
 				scanf("%d %f %d %f", &type1, &type1_val, &type2, &type2_val);
		    		point = type1*type1_val + type2*type2_val;
		    		point -= ((30 - type1)*type1_val + (30 - type2)*type2_val) * penalty;
		    		printf("A-O result: %.2f points.", point);
		    }
    }
	    }
    }

    return 0;
}
