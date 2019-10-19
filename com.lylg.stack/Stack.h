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
#include <MALLOC.H>


typedef struct Stack{
	//栈空间元素
	void *elem;
	//栈元素大小
	int elemSize;
	//栈顶指针
	int top;
	//栈长度
	int stackSize;
}Stack,*pStack;

void initStackForStack(pStack stack,int elemSize){
	stack->top = 0;
	stack->elemSize = elemSize;
	stack->stackSize = 20;
	stack->elem = malloc(elemSize * stack->stackSize);
}

////入栈
void pushForStack(pStack stack,void *elem){
	void *target;
	//栈满了
	if (stack->top == stack->stackSize) {
	//扩充栈
		stack->stackSize *= 2;
		stack->elem = realloc(stack->elem,stack->stackSize * stack->elemSize);
	}

	target =(double*) (stack->elem) + stack->elemSize * stack->top;
	memcpy(target,elem,stack->elemSize);
	stack->top++;
}

////出栈
void popForStack(pStack stack,void *result){
	void *elem = (double*)  (stack->elem) + (stack->top - 1)* stack->elemSize;
	memcpy(result,elem,stack->elemSize);
	stack->top--;
}
////将栈置空
//int clerStack(seqStack stack){
//	if(stack->top == -1)
//			return ERROR;
//	stack->top = -1;
//	return OK;
//}
//
////判断栈是否为空
//int isEmpty(seqStack stack){
//	if(stack->top == -1)
//			return TRUE;
//	return FALSE;
//}
//
////isFull	判断栈是否满了
int isFullForStack(pStack stack){
	if(stack->top == stack->stackSize)
			return TRUE;
	return FALSE;
}
//读取栈顶元素
void* getTopForStack(pStack stack){
	void* result;
	void* elem =(char*)  (stack->elem) + (stack->top - 1 * stack->elemSize);
	memcpy(result,elem,stack->elemSize);
	return result;
}


