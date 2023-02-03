#include <iostream>
#include <math.h>
#include <list>
#include <deque>
#include <stack>

struct list_node {
    int data;
    struct list_node *rand;
    struct list_node *next;
};

struct dlist_node {
    int data;
    struct dlist_node *pre;
    struct dlist_node *next;
};

struct clist_node {
    int data;
    struct list_node *next;
};

void show_list_node(list_node *l)
{
    if (l == NULL) return;
    list_node *cur = l;
    while (cur) {
        std::cout << cur->data << " ";
        cur = cur->next; 
    }
    std::cout << std::endl;
}

list_node* del_back(list_node *l, int b)
{
    return NULL;
}

list_node* del_mid(list_node *l)
{
}

int palindrome_list(list_node* l)
{
}

list_node *merge_lr_list(list_node *head)
{
}

list_node *list_del_dup(list_node *l)
{
}

list_node *list_del_val(list_node *l1, int val)
{
}

list_node* reverse(list_node *l)
{
}

list_node* resign(list_node *left, list_node* start, 
        list_node* end, list_node* right)
{
}

void joself_list()
{
}

void list_copy(list_node *l)
{
}

list_node *select_order(list_node *head)
{
}

list_node *merge_ordered_list(list_node *l1, list_node* l2)
{
}

list_node *reverse_every_partion_list(list_node *head, int k)
{
}

int main()
{
    list_node l1; l1.data = 1;
    list_node l2; l2.data = 3;
    list_node l3; l3.data = 5;
    list_node l4; l4.data = 7;
    list_node l5; l5.data = 9;
    list_node l6; l6.data = 10;

    l1.next = &l2; l2.next = &l3;
    l3.next = &l4; l4.next = &l5;
    l5.next = &l6; l6.next = NULL;

    show_list_node(&l1);
    show_list_node(&l1);

    return 0;
}
