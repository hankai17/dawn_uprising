#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"LinkQueue.h"

struct Person{
	QueueNode node;
	int ID;
	int Age;
};

int main(){

	//������ʽ����
	LinkQueue queue = Init_LinkQueue();
	//��������
	struct Person p1 = {NULL, 10, 10 };
	struct Person p2 = {NULL, 20, 20 };
	struct Person p3 = {NULL, 30, 30 };
	struct Person p4 = {NULL, 40, 40 };
	struct Person p5 = {NULL, 50, 50 };
	struct Person p6 = {NULL, 60, 60 };
	//�������
	Push_LinkQueue(queue, &p1);
	Push_LinkQueue(queue, &p2);
	Push_LinkQueue(queue, &p3);
	Push_LinkQueue(queue, &p4);
	Push_LinkQueue(queue, &p5);
	Push_LinkQueue(queue, &p6);
	//�����ͷ�Ͷ�βԪ��
	struct Person* front = (struct Person*)Front_LinkQueue(queue);
	struct Person* back = (struct Person*)Back_LinkQueue(queue);
	cout << "Front:" << front->ID << ":" << front->Age << endl;
	cout << "Back:" << back->ID << ":" << back->Age << endl;
	cout << "Size:" << Size_LinkQueue(queue) << endl;

	cout << "----------------" << endl;

	//��������е�Ԫ��
	while (Size_LinkQueue(queue) > 0){
		//��ö�ͷԪ��
		front = (struct Person*)Front_LinkQueue(queue);
		cout << "Front:" << front->ID << ":" << front->Age << endl;
		Pop_LinkQueue(queue);
	}

	cout << "Size:" << Size_LinkQueue(queue) << endl;

	//���ٶ���
	Destroy_LinkQueue(queue);

	system("pause");
	return EXIT_SUCCESS;
}