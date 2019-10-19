/*
 * SeqStack.c
 *
 *  Created on: 2019��10��16��
 *      Author: ���ղ�
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
//��ջ
int push(seqStack stack,ElemType elem){
	stack->top++;
	stack->elem[stack->top] = elem;
}
//��ջ
ElemType pop(seqStack stack){
	ElemType elem;
	if(stack->top == -1)
			return ERROR;
	elem = stack->elem[stack->top];
	stack->top--;
	return elem;
}
//��ջ�ÿ�
int clerStack(seqStack stack){
	if(stack->top == -1)
			return ERROR;
	stack->top = -1;
	return OK;
}

//�ж�ջ�Ƿ�Ϊ��
int isEmpty(seqStack stack){
	if(stack->top == -1)
			return TRUE;
	return FALSE;
}

//isFull	�ж�ջ�Ƿ�����
int isFull(seqStack stack){
	if(stack->top < MaxSize-1)
			return FALSE;
	return TRUE;
}

//��ȡջ��Ԫ��
ElemType getTop(seqStack stack){
	if(stack->top == -1)
			return ERROR;
	return  stack->elem[stack->top];

}



