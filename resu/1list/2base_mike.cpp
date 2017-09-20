#define  _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int id;		//������
	struct Node *next;	//ָ����
}SLIST;

//����ͷ�ڵ�
SLIST *SListCreat()
{
	SLIST *pCur = NULL;		//��ǰ�ڵ�
	SLIST *pHead = NULL;	//ͷ���
	SLIST *pNew = NULL;		//�½ڵ�

	//ͷ��㣬ֻ����Ϊ��־ʹ�ã���������Ч����
	pHead = (SLIST *)malloc(sizeof(SLIST));
	if (pHead == NULL)
	{
		return NULL;
	}

	//pHead��Ա������ֵ�����������⼴�ɣ������ò���
	pHead->id = -1;
	pHead->next = NULL;

	//���浱ǰ�ڵ�
	//ָ��ָ��˭���Ͱ�˭�ĵ�ַ��ֵ��ָ��
	pCur = pHead;

	int data;

	//ѭ��������㣬����������е���ֵ�Ӽ������룬��-1��Ϊ���������־
	while (1)//���±��һ��
	{
		printf("���������ݣ�");
		scanf("%d", &data);

		if (data == -1)
		{//����-1���˳�ѭ��
			break;
		}

		//�½ڵ����ռ�
		pNew = (SLIST *)malloc(sizeof(SLIST));
		if (pNew == NULL)
		{//���û�з���ɹ�����������ѭ��
			continue;
		}

		//pNew��Ա������ֵ
		pNew->id = data;

		//��ǰ�ڵ�nextָ���½ڵ�
		pCur->next = pNew;

		//�½ڵ��nextָ��NULL
		pNew->next = NULL;

		//��ǰ�ڵ��λ���ƶ����½ڵ��λ�ã�pCurָ��pNew��
		pCur = pNew;
	}


	//�����ͷ����ַ�ɺ���ֵ���ء�
	return pHead;
}

//�����ڵ�
//˳�������������������������е�����
int SListPrint(SLIST *pHead)
{
	if (pHead == NULL)
	{
		return -1;
	}

	//����ͷ������һ���ڵ�
	//��Ϊͷ��㲻����Ч���ݽڵ㣬��һ���ڵ������Ч���ݵĽ��
	SLIST *pCur = pHead->next;

	printf("head -> ");
	while (pCur != NULL)
	{
		printf("%d -> ", pCur->id);

		//�ڵ������ƶ�����ǰ�ڵ�ָ����һ���ڵ�
		pCur = pCur->next;
	}
	printf("NULL\n");

	return 0;
}

//��ֵΪx�Ľ��ǰ������ֵΪy�Ľ�㣻
//��ֵΪx�Ľ�㲻���ڣ�����ڱ�β
int SListNodeInsert(SLIST *pHead, int x, int y)
{
	if (pHead == NULL)
	{
		return -1;
	}

	SLIST *pPre = pHead;		//��һ���ڵ�
	SLIST *pCur = pHead->next;	//��ǰ�ڵ�
	SLIST *pNew = NULL;         //�½ڵ�

	while (pCur != NULL)
	{
		//�����ǰ�ڵ����������x������ѭ��
		if (pCur->id == x)
		{
			break;
		}

		//���浱ǰ�ڵ�
		//pPre = pCur;
		pPre = pPre->next;

		//��ǰ�ڵ������ƶ�����ǰ�ڵ�ָ����һ���ڵ�
		//pPre��pCur���һ���ڵ㣬pPreΪ��һ���ڵ㣬pCurΪ��ǰ�ڵ�
		pCur = pCur->next;
	}

	//����ִ�е��⣬���������
	//1. �ҵ�ֵΪx�Ľ�㣬pCurΪ��ǰƥ��ڵ㣬pPreΪ��һ���ڵ�
	//2. û���ҵ�x�Ľ�㣬�ڵ��ƶ�����β��pPreΪ���һ���ڵ㣬pCurΪNULL

	//��ֵΪx�Ľ��ǰ������ֵΪy�Ľ�㣻
	//��ֵΪx�Ľ�㲻���ڣ�����ڱ�β

	//�½ڵ����ռ�
	pNew = (SLIST *)malloc(sizeof(SLIST));
	if (pNew == NULL)
	{
		return -2;
	}

	//pNew��Ա������ֵ
	pNew->id = y;

	//pPre��nextָ��pNew
	pPre->next = pNew;

	//pNew��nextָ��pCur
	pNew->next = pCur;

	return 0;
}

//ɾ����һ��ֵΪx�Ľ��
int SListNodeDel(SLIST *pHead, int x)
{
	if (pHead == NULL)
	{
		return -1;
	}

	SLIST *pPre = pHead;		//��һ���ڵ�
	SLIST *pCur = pHead->next;	//��ǰ�ڵ�
	int flag = 0; //��־λ��0����û��ֵΪx�Ľ�㣬1������


	while (pCur != NULL)
	{
		if (pCur->id == x)
		{
			//��һ���ڵ�ָ��ǰ�ڵ����һ���ڵ�
			pPre->next = pCur->next;

			//��ʱ�ͷŽڵ�
			free(pCur);
			pCur = NULL;

			//��־λ��0����û��ֵΪx�Ľ�㣬1������
			flag = 1;

			//����ѭ��
			break;
		}

		//���浱ǰ�ڵ�
		pPre = pCur;

		//��ǰ�ڵ������ƶ�����ǰ�ڵ�ָ����һ���ڵ�
		//pPre��pCur���һ���ڵ㣬pPreΪ��һ���ڵ㣬pCurΪ��ǰ�ڵ�
		pCur = pCur->next;
	}


	if (flag == 0)
	{ //��־λ��0����û��ֵΪx�Ľ�㣬1������
		printf("û��ֵΪ%d�Ľ��\n", x);
		return -2;
	}

	return 0;
}

//ɾ��ֵΪx�����н��
int SListNodeDelPro(SLIST *pHead, int x)
{
	if (pHead == NULL)
	{
		return -1;
	}

	SLIST *pPre = pHead;		//��һ���ڵ�
	SLIST *pCur = pHead->next;	//��ǰ�ڵ�
	int flag = 0; //��־λ��0����û��ֵΪx�Ľ�㣬1������


	while (pCur != NULL)
	{
		if (pCur->id == x)
		{
			//��һ���ڵ�ָ��ǰ�ڵ����һ���ڵ�
			pPre->next = pCur->next;

			free(pCur);


			//��ǰ�ڵ������ƶ�����ǰ�ڵ�ָ����һ���ڵ�
			//pPre��pCur���һ���ڵ㣬pPreΪ��һ���ڵ㣬pCurΪ��ǰ�ڵ�
			pCur = pPre->next;

			//��־λ��0����û��ֵΪx�Ľ�㣬1������
			flag = 1;

			//��������ѭ����û������ѭ�������Ƿ����ظ�ֵΪx�Ľ��
			continue;
		}

		//���浱ǰ�ڵ�
		pPre = pCur;

		//��ǰ�ڵ������ƶ�����ǰ�ڵ�ָ����һ���ڵ�
		//pPre��pCur���һ���ڵ㣬pPreΪ��һ���ڵ㣬pCurΪ��ǰ�ڵ�
		pCur = pCur->next;
	}


	if (flag == 0)
	{ //��־λ��0����û��ֵΪx�Ľ�㣬1������
		printf("û��ֵΪ%d�Ľ��\n", x);
		return -2;
	}

	return 0;
}

//����ڵ�����
int SListNodeSort(SLIST *pHead)
{
	if (pHead == NULL || pHead->next == NULL)
	{
		return -1;
	}

	SLIST *pPre = NULL;
	SLIST *pCur = NULL;
	SLIST tmp; //��ʱ��������

	//ѡ������
	for (pPre = pHead->next; pPre->next != NULL; pPre = pPre->next)
	{
		for (pCur = pPre->next; pCur != NULL; pCur = pCur->next)
		{
			if (pPre->id > pCur->id) //����
			{
				//����������
				tmp = *pCur;
				*pCur = *pPre;
				*pPre = tmp;

				//����ָ������Ҫ��
				tmp.next = pCur->next;
				pCur->next = pPre->next;
				pPre->next = tmp.next;

			}
		}
	}

	return 0;
}

//����ԭ�������������,��������½ڵ�
//���ܲ���ڵ������������������½ڵ�x
int SListNodeInsertPro(SLIST *pHead, int x)
{
	//�����򣬱�֤ԭ�������������
	int ret = SListNodeSort(pHead);
	if (ret != 0)
	{
		return ret;
	}

	SLIST *pPre = pHead;		//��һ���ڵ�
	SLIST *pCur = pHead->next;	//��ǰ�ڵ�

	while (pCur != NULL)
	{
		//�ҵ����ʽڵ㣬����x = 3
		//����Ϊ��1 2 4 5
		//��ô 4 �ڵ�Ϊ���ʽڵ�
		if (pCur->id >= x)
		{
			break;
		}

		//���浱ǰ�ڵ�
		pPre = pCur;

		//��ǰ�ڵ������ƶ�����ǰ�ڵ�ָ����һ���ڵ�
		//pPre��pCur���һ���ڵ㣬pPreΪ��һ���ڵ㣬pCurΪ��ǰ�ڵ�
		pCur = pCur->next;
	}

	//����ִ�е��⣬��2�����
	//1. �ҵ�ƥ��ڵ㣬pCurΪ��ǰƥ��ڵ㣬pPreΪ��һ���ڵ�
	//2. û���ҵ�ƥ��ڵ㣬�ڵ��ƶ�����β��pPreΪ���һ���ڵ㣬pCurΪNULL


	//�½ڵ����ռ�
	SLIST *pNew = (SLIST *)malloc(sizeof(SLIST));
	if (pNew == NULL)
	{
		return -2;
	}

	//pNew��Ա������ֵ
	pNew->id = x;

	//pPre��nextָ��pNew
	pPre->next = pNew;

	//pNew��nextָ��pCur
	pNew->next = pCur;

	return 0;
}

//��ת����Ľڵ㣨���������Ƿ�ת��
int SListNodeReverse(SLIST *pHead)
{
	if (pHead == NULL || pHead->next == NULL || pHead->next->next == NULL)
	{
		return -1;
	}

	//��һ���ڵ�
	SLIST *pPre = pHead->next;

	//��ǰ�ڵ㣬pCur��pPre���һ���ڵ�
	SLIST *pCur = pPre->next; //pHead->next->next

	SLIST *pTmp = NULL; //��ʱ�ڵ�

	while (pCur != NULL)
	{
		//�ȱ���pCur����һ���ڵ�
		pTmp = pCur->next;

		//ԭ���� pPre->next = pCur
		//��ת�� pCur->next = pPre
		//pCur��nextָ��pPre
		pCur->next = pPre;

		//pPre�����ƶ�һ���ڵ㣬pPreָ��pCur
		pPre = pCur;

		//pCur�����ƶ�һ���ڵ㣬pCurָ��pTmp
		pCur = pTmp;
	}

	//ȷ��ͷ����β���
	//����ִ�е��⣬˵��pCurΪNULL��pPreΪ���һ����Ч�ڵ�
	//����ת��pPreΪͷ���ָ��ĵ�һ����Ч�ڵ�

	//��ȷ����ת���β���
	pHead->next->next = NULL;

	//��ȷ��ͷ���
	pHead->next = pPre;

	return 0;
}

//�ͷ����нڵ�
int SListDestroy(SLIST *pHead)
{
	if (pHead == NULL)
	{
		return -1;
	}

	SLIST *pTmp = NULL;	//��ʱ�ͷŽڵ�

	while (pHead != NULL)
	{
		//��ʱ�ͷŽڵ�
		pTmp = pHead;

		//ͷ���ָ��ͷ���next�ڵ�
		pHead = pHead->next;

		free(pTmp);
		pTmp = NULL;

	}

	return 0;
}

int main()
{
	SLIST *pHead = NULL;

	pHead = SListCreat(); //����ͷ���
	printf("\n����ͷ����\n");
	SListPrint(pHead); //�������нڵ�

	SListNodeDelPro(pHead, 4);//ɾ������ֵΪ4�Ľ��
	printf("\nɾ������ֵΪ4�Ľ��\n");
	SListPrint(pHead); //�������нڵ�

	SListNodeSort(pHead);//����ڵ�����
	printf("\n����ڵ�����\n");
	SListPrint(pHead); //�������нڵ�

	SListNodeInsertPro(pHead, 5);//�������5
	printf("\n�������5��\n");
	SListPrint(pHead); //�������нڵ�

	//��ת����Ľڵ㣨���������Ƿ�ת��
	SListNodeReverse(pHead);
	printf("\n��ת����Ľڵ�\n");
	SListPrint(pHead); //�������нڵ�

	SListDestroy(pHead);//�ͷ����нڵ�
	pHead = NULL;

	printf("\n");
	system("pause");
	return 0;
}