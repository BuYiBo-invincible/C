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
#include <MALLOC.H>


typedef struct Stack{
	//ջ�ռ�Ԫ��
	void *elem;
	//ջԪ�ش�С
	int elemSize;
	//ջ��ָ��
	int top;
	//ջ����
	int stackSize;
}Stack,*pStack;

void initStackForStack(pStack stack,int elemSize){
	stack->top = 0;
	stack->elemSize = elemSize;
	stack->stackSize = 20;
	stack->elem = malloc(elemSize * stack->stackSize);
}

////��ջ
void pushForStack(pStack stack,void *elem){
	void *target;
	//ջ����
	if (stack->top == stack->stackSize) {
	//����ջ
		stack->stackSize *= 2;
		stack->elem = realloc(stack->elem,stack->stackSize * stack->elemSize);
	}

	target =(double*) (stack->elem) + stack->elemSize * stack->top;
	memcpy(target,elem,stack->elemSize);
	stack->top++;
}

////��ջ
void popForStack(pStack stack,void *result){
	void *elem = (double*)  (stack->elem) + (stack->top - 1)* stack->elemSize;
	memcpy(result,elem,stack->elemSize);
	stack->top--;
}
////��ջ�ÿ�
//int clerStack(seqStack stack){
//	if(stack->top == -1)
//			return ERROR;
//	stack->top = -1;
//	return OK;
//}
//
////�ж�ջ�Ƿ�Ϊ��
//int isEmpty(seqStack stack){
//	if(stack->top == -1)
//			return TRUE;
//	return FALSE;
//}
//
////isFull	�ж�ջ�Ƿ�����
int isFullForStack(pStack stack){
	if(stack->top == stack->stackSize)
			return TRUE;
	return FALSE;
}
//��ȡջ��Ԫ��
void* getTopForStack(pStack stack){
	void* result;
	void* elem =(char*)  (stack->elem) + (stack->top - 1 * stack->elemSize);
	memcpy(result,elem,stack->elemSize);
	return result;
}


