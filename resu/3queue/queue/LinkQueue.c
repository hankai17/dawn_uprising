#include"LinkQueue.h"


//��ʼ��
LinkQueue Init_LinkQueue(){

	LQueue* queue = (LQueue*)malloc(sizeof(LQueue));
	if (queue == NULL){
		return NULL;
	}

	queue->header.next = NULL;
	queue->size = 0;

	return queue;
}
//���  ͷ��λ�� ���� ��β
void Push_LinkQueue(LinkQueue queue, void* data){

	if (queue == NULL){
		return;
	}

	if (data == NULL){
		return;
	}

	QueueNode* node = (QueueNode*)data;
	LQueue* lqueue = (LQueue*)queue;

	//�ڵ�������
	node->next = lqueue->header.next;
	lqueue->header.next = node;

	lqueue->size++;
}
//����  β��λ�õ���ͷ
void Pop_LinkQueue(LinkQueue queue){

	if (queue == NULL){
		return;
	}

	LQueue* lqueue = (LQueue*)queue;
	
	QueueNode* pCurrent = &(lqueue->header);
	for (int i = 0; i < lqueue->size - 1; i ++){
		pCurrent = pCurrent->next;
	}

	pCurrent->next = NULL;
	lqueue->size--;
}
//��ö�ͷԪ��
void* Front_LinkQueue(LinkQueue queue){
	if (queue == NULL){
		return NULL;
	}
	LQueue* lqueue = (LQueue*)queue;

	QueueNode* pCurrent = &(lqueue->header);
	for (int i = 0; i < lqueue->size; i++){
		pCurrent = pCurrent->next;
	}

	return pCurrent;
}
//��ö�βԪ��
void* Back_LinkQueue(LinkQueue queue){
	if (queue == NULL){
		return NULL;
	}
	LQueue* lqueue = (LQueue*)queue;
	return lqueue->header.next;
}
//��С
int Size_LinkQueue(LinkQueue queue){
	if (queue == NULL){
		return -1;
	}
	LQueue* lqueue = (LQueue*)queue;
	return lqueue->size;
}
//���١�
void Destroy_LinkQueue(LinkQueue queue){
	if (queue == NULL){
		return;
	}
	free(queue);
}