/*
 * SeqStack.c
 *
 *  Created on: 2019年10月16日
 *      Author: 布艺博
 */
#define ElemType char
#define MaxSize 100
#define ERROR -1
#define OK 0
#define TRUE 0
#define FALSE -1



typedef struct stack{
	ElemType elem[MaxSize];
	int top;
}stack,*seqStack;

void initStack(seqStack stack){
	stack->top = -1;
}
//入栈
int push(seqStack stack,ElemType elem){
	stack->top++;
	stack->elem[stack->top] = elem;
}
//出栈
ElemType pop(seqStack stack){
	ElemType elem;
	if(stack->top == -1)
			return ERROR;
	elem = stack->elem[stack->top];
	stack->top--;
	return elem;
}
//将栈置空
int clerStack(seqStack stack){
	if(stack->top == -1)
			return ERROR;
	stack->top = -1;
	return OK;
}

//判断栈是否为空
int isEmpty(seqStack stack){
	if(stack->top == -1)
			return TRUE;
	return FALSE;
}

//isFull	判断栈是否满了
int isFull(seqStack stack){
	if(stack->top < MaxSize-1)
			return FALSE;
	return TRUE;
}

//读取栈顶元素
ElemType getTop(seqStack stack){
	if(stack->top == -1)
			return ERROR;
	return  stack->elem[stack->top];

}



