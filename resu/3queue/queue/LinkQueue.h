#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include<stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif



	typedef void* LinkQueue;

	//�ڵ㶨��
	typedef struct _QUEUENODE{
		struct _QUEUENODE* next;
	}QueueNode;


	//����ṹ��
	typedef struct _LINKQUEUE{
		QueueNode header; //ͷ���
		int size; //�ڵ�ĸ���
	}LQueue;


	//��ʼ��
	LinkQueue Init_LinkQueue();
	//���
	void Push_LinkQueue(LinkQueue queue,void* data);
	//����
	void Pop_LinkQueue(LinkQueue queue);
	//��ö�ͷԪ��
	void* Front_LinkQueue(LinkQueue queue);
	//��ö�βԪ��
	void* Back_LinkQueue(LinkQueue queue);
	//��С
	int Size_LinkQueue(LinkQueue queue);
	//���١�
	void Destroy_LinkQueue(LinkQueue queue);


#ifdef __cplusplus
	}
#endif





#endif