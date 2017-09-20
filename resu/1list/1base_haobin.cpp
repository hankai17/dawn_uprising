#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <malloc.h>
#include <stdlib.h>


typedef struct Node
{
	int data;//������ 
	struct Node *pNext;//ָ���� 
}NODE,*PNODE;// node�ȼ��� struct node, pnode �ȼ���struct node *


PNODE create_list(void);
void traverse_list(PNODE pHead); 
bool is_empty(PNODE pHead);
int length_list(PNODE);
bool insert_list(PNODE,int,int);//ָ���ĸ����� λ�� ֵ 
bool delete_list(PNODE,int,int *);//       ..........ɾ���������
void sort_list(PNODE);
 
PNODE create_list(void)//�˺����ɶ�̬�ķ�����ڴ� ����ͷ���ĵ�ַ��phead���� pheadָ����һ�������� 
{
	int len;//�����Ч�ڵ���� 
	int i;
	int val;//��ʱ����û�����Ľڵ��ֵ 
	PNODE pHead = (PNODE)malloc(sizeof(NODE));//������һ���������Ч���ݵ�ͷ�ڵ� //pHead ��ͷָ�� 
	if(NULL==pHead)
	{
		printf("����ʧ��\n");
		exit(-1);
	}
	PNODE pTail= pHead;//PTailҲָ����ͷ��� pheadҲָ��ͷ��� һ���ڵ������ͷ�ڵ����Ϊ�ڵ� 
	pTail->pNext=NULL; 
	printf("���������=");scanf("%d",&len); 
	for(i=0;i<len;++i)
	{
		printf("�����%d���ڵ��ֵ��",i+1); 
		scanf("%d",&val); 
		PNODE pNew = (PNODE)malloc(sizeof(NODE));//ÿѭ��һ��pnew���һ���µĽڵ� 
	if(NULL==pNew)
	{
		printf("����ʧ��\n");
		exit(-1);
	}
	pNew->data=val;	//PNEW������ʱ�Ľڵ㣬�����ݸ���ʱ�ڵ��������              
    pTail->pNext=pNew;//����һ��ָ����Զָ�����һ���ڵ� 
    pNew->pNext=NULL;
    pTail=pNew;
	}
	return pHead; 
}

void traverse_list(PNODE pHead)//�������˼ ���践��ֵ ��Ҫ���������ĸ��ط��ı����� 
{
	PNODE p = pHead->pNext;//pָ���һ����Ч�ڵ� 
	while(NULL!=p)//ָ���򲻿� 
	{
		printf("%d ",p->data);
		p=p->pNext;
	}
	printf("\n");
	return;//����ִ����� 
} 

bool is_empty(PNODE pHead)
{
	if(NULL==pHead->pNext)//ͷ����ָ����Ϊ��
	 return true;
	 else
	 return false; 
}

int length_list(PNODE pHead)
{
	PNODE p=pHead->pNext;
	int len=0;
	while(NULL!=p)
	{
		++len;
		p=p->pNext;
	}
	return len;
}

void sort_list(PNODE pHead)//����Ҫ//�ᱳ 
{	
	int i,j,t;
	PNODE p,q;
	int len=length_list(pHead);
	
	for(i=0,p=pHead->pNext;i<len-1;++i,p=p->pNext)//i�ǵ�һ����ЧԪ�ص��±�p��һ����ЧԪ�صĵ�ַ 
	{
		for(j=i+1,q=p->pNext;j<len;++j,q=q->pNext)
		{
			if(p->data>q->data)
			{
				t=p->data;//a[i]>a[j]
				p->data=q->data;//t=a[i]
				q->data=t;//�ﵽ�˷��� a[j]=t
			}
		}
	}
	return; 
}

//��pHead��ָ������ĵ�pos���ڵ��ǰ�����һ���µĽڵ㣬�ýڵ��ֵ��val,����pos��ֵ��1��ʼ 
bool insert_list(PNODE pHead,int pos,int val)
{//�������� ������ 
	int i=0;
	PNODE p=pHead;
	
	while(NULL!=p&&i<pos-1)
	{
		p=p->pNext;
		++i;
	}
	if(i>pos-1||NULL==p)
	return false;
	
	PNODE pNew=(PNODE)malloc(sizeof(NODE));
	if(NULL==pNew)
	{
		printf("��̬�����ڴ�ʧ��\n");
		exit(-1); 
	}
	pNew->data=val;
	PNODE q=p->pNext;
	p->pNext=pNew;
	pNew->pNext=q;
	
	return true;
}

bool delete_list(PNODE pHead,int pos,int * pVal/*in out*/)
{
	int i=0;
	PNODE p=pHead;
	
	while(NULL!=p->pNext&&i<pos-1)
	{
		p=p->pNext;
		++i;
	}
	if(i>pos-1||NULL==p->pNext)
	return false;
	PNODE q=p->pNext;
	*pVal=q->data;
	
	p->pNext=p->pNext->pNext;
	free(q);
	q=NULL;
	system("pause");
	return true;
}
//����	1	error C4996: 'scanf': This function or variable may be unsafe. Consider using scanf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.	i:\c++\����ģ��\����ģ��\����ģ��\1���ֻ�������\δ����1.cpp	78	1	����ģ��

//��û�з����ڴ� 
int main(void)
{
	PNODE pHead = NULL;//�ȼ��� struct node *pHead 
	pHead = create_list();//����һ����ѭ�������� �����������ͷ���ĵ�ַ��phead//��ʵ���� һ��������������ڴ� �����ڴ���׵�ַ��phead 
	traverse_list(pHead);//���� һ��һ����� 
	int val;

	int len = length_list(pHead);
	printf("��������%d\n", len);

	if (is_empty(pHead))
		printf("�����\n");
	else
		printf("������\n");


	sort_list(pHead);
	traverse_list(pHead);//���� һ��һ����� 

	insert_list(pHead, 3, 22);
	traverse_list(pHead);//���� һ��һ����� 

	if (delete_list(pHead, 4, &val))
	{
		printf("ɾ���ɹ�,ɾ����Ԫ���ǣ�%d\n", val);
	}
	else
	{
		printf("ɾ��ʧ��");
	}
	traverse_list(pHead);//���� һ��һ����� 	
	return 0;
}