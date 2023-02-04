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
    list_node *slow = l;
    list_node *fast = l->next->next;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    std::cout << "pre mid: " << slow->data << std::endl;
    slow->next = slow->next->next;
    return l;
}

int palindrome_list(list_node* l)
{
    list_node *slow = l;
    list_node *fast = l;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    std::cout << "mid: " << slow->data << std::endl;

    list_node *rh = slow->next;
    slow->next = NULL;

    list_node *pre = NULL;
    list_node *next;
    while (rh) {
        next = rh->next;
        rh->next = pre;

        pre = rh;
        rh = next;
    }

    while (l && pre) {
        if (l->data != pre->data) {
            return 0;
        }
        l = l->next;
        pre = pre->next;
    }
    return 1;
}

list_node *merge_lr_list(list_node *head)
{
    list_node *slow = head;
    list_node *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    std::cout << "mid: " << slow->data << std::endl;

    list_node *rh = slow->next;
    slow->next = NULL;

    list_node n;
    list_node *tmp = &n;
    while (head && rh) {
        tmp->next = head;
        tmp = head;
        head = head->next;

        tmp->next = rh;
        tmp = rh;
        rh = rh->next;
    }
    tmp->next = rh ? rh : head;
    return n.next;
}

list_node *list_del_dup(list_node *l)
{
    if (l == NULL || l->next == NULL) return l;
    l->next = list_del_dup(l->next);
    return l->data == l->next->data ? l->next : l;
}

list_node *list_del_val(list_node *l1, int val)
{
    while (l1->data == val) {
        l1 = l1->next;
    }
    list_node *h = l1;
    list_node *pre = l1;
    list_node *cur = l1->next;
    while (cur) {
        if (cur->data != val) {
            pre = cur;
        } else {
            pre->next = cur->next;
        }
        cur = cur->next;
    }
    return h;
}

list_node* resign(list_node *left, list_node* start, 
        list_node* end, list_node* right)
{
    list_node *pre = NULL;
    list_node *next;
    list_node *h = start;
    while (h != right) {
        next = h->next;
        h->next = pre;
        pre = h;
        h = next;
    }
    if (left) left->next = pre;
    start->next = right;
    return left ? left : pre;
}

void joself_list()
{
}

list_node* list_copy(list_node *l)
{
    list_node *cur = l;
    while (cur) {
        list_node* n = new list_node;
        n->data = cur->data;

        list_node* next = cur->next;
        cur->next = n;
        n->next = next;
        cur = next;
    }
    cur = l;
    while (cur) {
        list_node *n = cur->next;
        if (cur->rand) {
            n->rand = cur->rand->next;
        }
        cur = n->next;
    }
    cur = l;
    show_list_node(l);
    list_node node;
    list_node *tmp = &node;
    while (cur) {
        list_node *n = cur->next;
        tmp->next = n;
        tmp = n;

        cur->next = n->next;
        cur = cur->next;
    }
    return node.next;
}

list_node *select_order(list_node *head)
{
}

list_node *merge_ordered_list(list_node *l1, list_node* l2)
{
}

list_node *reverse_every_partion_list(list_node *head, int k)
{
    list_node *left = NULL;
    list_node *start = NULL;
    list_node *cur = head;
    list_node *next;
    list_node *n_h = NULL;
    int i = 1;
    while (cur) {
        next = cur->next;
        if (i == k) {
            n_h = n_h ? n_h : cur;
            start = start ? left->next : head; 
            resign(left, start, cur, next);
            left = start; 
            i = 0;
        }
        i++;
        cur = next;
    }
    return n_h;
}

int main()
{
    list_node l1; l1.data = 1;
    list_node l2; l2.data = 3;
    list_node l3; l3.data = 5;
    list_node l4; l4.data = 3;
    list_node l5; l5.data = 1;
    list_node l6; l6.data = 1;

    l1.next = &l2; l2.next = &l3;
    l3.next = &l4; l4.next = &l5;
    l5.next = NULL; //&l6; l6.next = NULL;
    list_node* tmp;

    show_list_node(&l1);
    //tmp = del_mid(&l1);
    //int ret = palindrome_list(&l1);
    //std::cout << "ret: " << ret << std::endl;
    //tmp = merge_lr_list(&l1);
    //tmp = list_del_val(&l1, 1);
    //tmp = list_copy(&l1); ///////////////////////////
    tmp = reverse_every_partion_list(&l1, 2);
    show_list_node(tmp);

    return 0;
}

// TIME ELAPSE: 20230204 48min 
