#include<iostream>
#include<stdlib.h>
#include<stack>

struct list_node {
  int data;
  struct list_node* next;
  //struct list_node* pre;
};

void showlist_node(list_node* head) {
  if (head == NULL) {
    return;
  }
  list_node* pCurrent = head; //链表从第0个开始
  //list_node* pCurrent = head->next; //当面试写复杂的 翻转等操作时候 链表设计别从第一个开始 
  while (pCurrent != NULL) {
    std::cout << pCurrent->data << " ";
    pCurrent = pCurrent->next;
  }
}

//phn模型
list_node* rever(list_node* head) {
  if (head == NULL) {
    return NULL;
  }
  list_node* pre = NULL;
  list_node* next;
  while (head!= NULL) {
    next = head->next;

    head->next = pre;
    //head->pre = next;

    pre = head;
    head = next;
  }
  return pre;
}

void* middle(list_node* head) {
  if(head == NULL) {
    return NULL;
  }
  list_node* mid = head;
  list_node* cur = head;
  while(cur->next != NULL && cur->next->next != NULL) {
    mid = mid->next;
    cur = cur->next->next;
  }
  return mid;
}

bool is_palindrome(list_node* head) {
  if(head == NULL) {
    return true;
  }
  list_node* mid = (list_node*)middle(head);
  list_node* right = mid->next;
  std::stack<list_node*> s;
  while(right != NULL) {
    s.push(right);
    right = right->next;
  }
  while(!s.empty()) {
    list_node* tmp = s.top();
    s.pop();
    if(tmp->data != head->data) {
      return false;
    }
    head = head->next;
  }
  return true;
}

void* add_list(list_node* l1, list_node* l2) {
  if(l1 == NULL || l2 == NULL) {
    return 0; //不恰当
  }
  list_node* h1 = rever(l1);
  list_node* h2 = rever(l2);
  int ca = 0;
  list_node* n1 = h1;
  list_node* n2 = h2;
  list_node* node = NULL;
  list_node* pre = NULL; //链表从后往前 也符合相加规律
  int no1 = 0;
  int no2 = 0;
  int no = 0;
  while(n1 != NULL || n2 != NULL) {
    no1 = n1 != NULL ? n1->data : 0;
    no2 = n2 != NULL ? n2->data : 0;
    no = no1 + no2 + ca;

    node = new list_node;
    node->data = no % 10;
    ca = no / 10;

    node->next = pre;
    pre = node; 

    n1 = n1 != NULL ? n1->next : NULL;
    n2 = n2 != NULL ? n2->next : NULL;
  }

  if (ca == 1) {
    node = new list_node;
    node->data = 1;
    node->next = pre;
    pre = node;
  }
  //rever(l1);
  //rever(l2);
  return pre;
}

int main()
{
  list_node head, node1, node2;
  head.data = 9;
  node1.data = 3;
  node2.data = 7;

  head.next = &node1;
  node1.next = &node2;
  node2.next = NULL;

  list_node head1, node11;
  head1.data = 6;
  node11.data = 2;

  head1.next = &node11;
  node11.next = NULL;

  list_node* tmp = (list_node*)add_list(&head, &head1);
  showlist_node(tmp);
  return 0;
}

int main1()
{
  list_node head;
  list_node node1, node2, node3, node4, node5;
  head.data = 1;
  node1.data = 2;
  node2.data = 3;
  node3.data = 4;
  node4.data = 5;
  node5.data = 6;

  head.next = &node1;
  //head.pre = NULL;

  node1.next = &node2;
  //node1.pre = &head;

  node2.next = &node3;
  //node2.pre = &node1;

  node3.next = &node4;
  //node3.pre = &node2;

  node4.next = &node5;
  //node4.pre = &node3;
  //node5.next = &node6;
  node5.next = NULL;

  showlist_node(&head);
  std::cout<<std::endl;
  /*
  //std::cout<<((list_node*)middle(&head))->data<<std::endl; 
  //std::cout<<is_palindrome(&head)<<std::endl;
  list_node* tmp = rever(&head);
  showlist_node(tmp);
  std::cout<<std::endl;

  list_node* head1 = rever(tmp);
  showlist_node(head1);
  */

  return 0;
}
