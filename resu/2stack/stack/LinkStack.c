#include"LinkStack.h"

//��ʼ��
LinkStack Init_LinkStack(){

	LStack* stack = (LStack*)malloc(sizeof(LStack));
	if (stack == NULL){
		return NULL;
	}

	stack->head = NULL;
	stack->size = 0;

	return stack;
}
//ѹջ
void Push_LinkStack(LinkStack stack, void* data){

	if (stack == NULL){
		return;
	}

	if (data == NULL){
		return;
	}

	StackNode*  node = (StackNode*)data;
	LStack* sstack = (LStack*)stack;

	node->next = sstack->head;
	sstack->head = node;

	sstack->size++;
}
//��ջ
void Pop_LinkStack(LinkStack stack){

	if (stack == NULL){
		return;
	}
	LStack* sstack = (LStack*)stack;
	if (sstack->size == 0){
		return;
	}

	//�����µ�һ���ڵ�
	StackNode* pFirst = sstack->head;
	sstack->head = pFirst->next;
	
	sstack->size--;
}
//���ջ��Ԫ��
void* Top_LinkStack(LinkStack stack){
	if (stack == NULL){
		return NULL;
	}
	LStack* sstack = (LStack*)stack;
	if (sstack->size == 0){
		return NULL;
	}

	return sstack->head;
}
//��С
int Size_LinkStack(LinkStack stack){
	if (stack == NULL){
		return -1;
	}
	LStack* sstack = (LStack*)stack;
	return sstack->size;
}
//����
void Destroy_LinkStack(LinkStack stack){
	if (stack == NULL){
		return;
	}

	free(stack);
}