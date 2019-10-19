/*
 * sum.c
 *
 *  Created on: 2019年10月17日
 *      Author: 布艺博
 */
#include "SeqStack.h"
#include "Stack.h"
#include <stdlib.h>
//extern struct stack tack;

//比较运算符优先级 8/2-3+2*5
char compareOperator(char a,char b){
	int c;
	int d;
	switch (a) {
		case '^':
			c = 3;
			break;
		case '*':
			c = 2;
			break;
		case '/':
			c = 2;
			break;
		case '+':
			c = 1;
			break;
		case '-':
			c = 1;
			break;
		default:
			c = 0;
			break;
	}
	switch (b) {
		case '^':
			d = 3;
			break;
		case '*':
			d = 2;
			break;
		case '/':
			d = 2;
			break;
		case '+':
			d = 1;
			break;
		case '-':
			d = 1;
			break;
		default:
			d = 0;
			break;
	}
	if(c < d)
		return '<';
	else if(c > d)
		return '>';
	else if(c == d)
		return '=';

}

//运算操作
double calculation(double a,double b,char operation){
	double numberA= a;
	double numberB = b;
	double optionResult;
	if(operation == '^'){
		optionResult = pow(numberA,numberB);
	}
	if(operation == '*'){
		optionResult = numberA * numberB;
	}
	if(operation == '/'){
		optionResult = numberA / numberB;
	}
	if(operation == '+'){
		optionResult = numberA + numberB;
	}
	if(operation == '-'){
		optionResult = numberA - numberB;
	}
	return optionResult;
}


double getSum(){
	stack operatorStack ;
	pStack numberStack = malloc(sizeof(Stack));
	char *input = (char *)malloc(sizeof(char));
	double *optionResult = (double*)malloc(sizeof(double));
	char compareResult;
	double *numberResulta = malloc(sizeof(double));
	double *numberResultb = malloc(sizeof(double));
	char *operatorResult = malloc(sizeof(char));
	double temp;
	char computedResult;
	int numberIndex = 0;
	char *number =(char*) malloc(sizeof(char)*10);
	int index = 0;
	initStack(&operatorStack);
	initStackForStack(numberStack,sizeof(double));
	printf("请输入运算表达式以#结束 \n");
	scanf("%s",input);
	while(input[index]){
		if(input[index] == '+' || input[index] == '-' || input[index] == '*' || input[index] == '/' || input[index]== '^'){
			temp = atof(number);
			pushForStack(numberStack,&temp);
			number = (char*)malloc(sizeof(char)*10);
			numberIndex = 0;
			if(isEmpty(&operatorStack) == -1){
				compareResult = compareOperator(input[index],getTop(&operatorStack));
				if(compareResult == '<' || compareResult == '='){
					popForStack(numberStack,numberResulta);
					popForStack(numberStack,numberResultb);
					*operatorResult = pop(&operatorStack);
					*optionResult = calculation(*numberResultb,*numberResulta,*operatorResult);
					pushForStack(numberStack,optionResult);
					push(&operatorStack,input[index]);
				}
				else if(compareResult == '>'){
					push(&operatorStack,input[index]);
				}
			}
			else
				push(&operatorStack,input[index]);
		}
		else if(input[index] == '#' || input[index] == '='){
			temp = atof(number);
			pushForStack(numberStack,&temp);
			numberIndex = 0;
			while(isEmpty(&operatorStack) == -1){
				*operatorResult = pop(&operatorStack);
				popForStack(numberStack,numberResulta);
				popForStack(numberStack,numberResultb);
				*optionResult = calculation(*numberResultb,*numberResulta,*operatorResult);
				pushForStack(numberStack,optionResult);
			}
		}

		else{
			number[numberIndex] = input[index];
			numberIndex++;
		}
		index++;
	}
	popForStack(numberStack,optionResult);
	return *optionResult;
}



int main(int argc, char **argv) {
	printf("计算结果%f",getSum());
	system("pause");
}
