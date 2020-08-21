#include <stdio.h>

void main(){
	int task, trans_amount, i, type1, type2, type3, type4, type1_val, type2_val, type3_val, type4_val;
	char type_money, type_trans, type_exam, type_ayt;
	long double initial_money;
	float rate_eur, rate_doll, money_amount, dollar, euro, penalty, result;
	dollar = 0;
	euro = 0;

	scanf("%d", &task);
	if (task == 1){
		scanf("%Lf %f %f", &initial_money, &rate_eur, &rate_doll);
		scanf("%d", &trans_amount);
		for(i=0;i<trans_amount;i++){
			scanf(" %c %c %f", &type_trans, &type_money, &money_amount);
			if (type_trans == 'D'){
				if (type_money == 'D'){
					dollar += money_amount;			
				}
				else if (type_money == 'E'){
					euro += money_amount;
				}
			}
			else if (type_trans == 'W'){
				if (type_money == 'D'){
					dollar -= money_amount;
				}
				else if (type_money == 'E'){
					euro -= money_amount;
				}
			}
		}
		initial_money += dollar * rate_doll + euro * rate_eur;
		printf("Final balance: %Lf", initial_money);
	}
	else if (task == 2){
		scanf (" %c", &type_exam);
		if (type_exam == 'T'){
			scanf("%f", &penalty)
			scanf("%d %f %d %f %d %f %d %f", &type1, &type1_val, &type2, &type2_val, &type3, &type3_val, &type4, &type4_val);
			result = type1 * type1_val + type2 * type2_val + type3 * type3_val + type4 * type4_val - ((40-type1)* type1_val + (40-type2)*type2_val + (40-type3)*type3_val + (40-type4)*type4_val)*;
			printf("T result: %f", result);
		}
		else if (type_exam == 'A'){
			if (type_ayt == 'E'){
			scanf()	
			}
		}
	}
}
