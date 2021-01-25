#include <iostream>
#include <math.h>
#include <list>
#include <deque>

struct list_node {
    int               data;
    struct list_node *rand;
    struct list_node *next;
};

struct dlist_node {
    int               data;
    struct dlist_node *pre;
    struct dlist_node *next;
};

struct clist_node {
    int               data;
    struct clist_node *next;
};

void show_list_node(list_node *l)
{
    if (l == NULL) return;
    list_node *curr = l;
    while (curr != NULL) {
        std::cout << curr->data;
        curr = curr->next;
    }
    std::cout << std::endl;
}

void wnd_max()
{
    #define WIN_SIZE 3
    int arr[] = { 1, 9, 2, 8, 3, 8, 6, 5 };
    std::deque<int> max;
    std::deque<int> res;

    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        while (!max.empty() && arr[i] > arr[max.back()]) {
            max.pop_back();
        }

        max.push_back(i);

        if (i - max.front() > WIN_SIZE - 1) {
            max.pop_front();
        }

        if (i >= WIN_SIZE - 1) {
            int tmp = max.front();
            std::cout << arr[tmp] << " ";
        }
    }
}

void print_same()
{
    std::list<int> l1; // already ordered
    std::list<int> l2;
    
    l1.push_back(1); l1.push_back(2);
    l1.push_back(3); l1.push_back(4);
    l1.push_back(5);
    l2.push_back(3); l2.push_back(4);
    l2.push_back(5); l2.push_back(6);

    std::list<int>::iterator iter1 = l1.begin();
    std::list<int>::iterator iter2 = l2.begin();
    while (iter1 != l1.end() && iter2 != l2.end()) {
        if (*iter1 < *iter2) {
            iter1++;
        } else if (*iter1 > *iter2) {
            iter2++;
        } else {
            std::cout << *iter1 << " ";
            iter1++;
            iter2++;
        }
    }
}

void del_back(list_node *head)
{
    #define BACK_IDX 1
    // slist
    int        len = 0;
    list_node *curr = head;
    while (curr) {
        curr = curr->next;
        len++;
    }

    if (BACK_IDX > len) return;
    if (BACK_IDX == len) return;
    int del_idx_pre = len - BACK_IDX - 1;
    curr = head;
    int i = 0;
    while (curr) {
        if (i == del_idx_pre) {
            curr->next = curr->next->next; 
            break;
        }
        curr = curr->next;
        i++;
    }

    show_list_node(head);

    // dlist TODO
}

list_node *del_mid(list_node *head)
{
    if (!head || !head->next) return head;
#if 0
    list_node *mid = head;
    list_node *cur = head;
    while (cur->next != NULL &&
        cur->next->next != NULL) { // If two node. get the first as mid
        mid = mid->next;
        cur = cur->next->next;
    }
#elif 0
    if (!head->next) return head;
    if (!head->next->next) return head->next;
    list_node *pre_mid = head;
    list_node *cur = head->next->next;
    while (cur->next != NULL &&
          cur->next->next != NULL) {
        pre_mid = pre_mid->next;
        cur = cur->next->next;
    }
    pre_mid->next = pre_mid->next->next;
#elif 1
    if (!head->next) return head;
    int len = 0;
    list_node *cur = head;
    while (!cur) {
        cur = cur->next;
        len++;
    }

    int a = 4;
    int b = 9;
    int del_hidx = (int)ceil( ((double) (a*len)) / ((double) b) );
    if (del_hidx == 0) return head;
    if (del_hidx == 1) return head->next;
    int del_idx = del_hidx - 1;
    list_node *pre = head;
    while (del_idx > 1) {
        pre = pre->next; 
        del_idx--;
    }
    pre = pre->next->next;
#endif
}

//phn
list_node *reverse_list(list_node *head)
{
    if (head == NULL) return head;
    list_node *pre = NULL;
    list_node *next;
    while (head) {
        next = head->next;
        head->next = pre;

        pre = head;
        head = next;
    }
    return pre;
}

list_node *reverse_partion_list(list_node *head, 
      int from_hidx, int to_hidx) // 2 4
{
    list_node *cur = head; 
    list_node *pre = NULL; 
    list_node *after = NULL; 

    int i = 0;
    if (from_hidx == 1) pre = NULL;
    while (cur) {
        if (i == from_hidx - 2) {
            pre= cur; 
        } 
        if (i == to_hidx) {
            after = cur; 
        }
        cur = cur->next;
        i++;
    }
    if (from_hidx > to_hidx || from_hidx < 1 || to_hidx > i) {
        return head;
    }

    list_node *r_pre = after;
    list_node *r_head = pre == NULL ? head : pre->next;
    list_node *r_next;
    while (r_head != after) {
        r_next = r_head->next;
        r_head->next = r_pre;

        r_pre = r_head;
        r_head = r_next;
    }
    //show_list_node(r_pre);
    
    if (pre == NULL) 
        return r_pre; 
    else {
        pre->next = r_pre;
        return head;
    }
}

#if 0
list_node *reverse_every_partion_list(list_node *head, int len)
{
    if (head == NULL || len <= 1) return head;
    int i = 0;
    list_node *pre;
    list_node *cur = head;
    list_node *next;

    list_node *n_start = NULL;
    list_node *n_end = NULL;
    while (cur != NULL) {
        if (i == len - 1) {
            n_start = pre; 
            pre_end->next = pre;
            i = 0;
        }

        if (i == 0) {
            n_end = cur;
        }
        next = cur->next;
        cur->next = pre;

        pre = cur;
        cur = cur->next;
        i++;
    }
}
#endif

dlist_node *reverse_dlist(dlist_node *head)
{
    if (head == NULL) return head;
    dlist_node *pre = NULL;
    dlist_node *next;
    while (head) {
        next = head->next;
        head->next = pre;
        head->pre = next;

        pre = head;
        head = next;
    }
    return pre;
}

void joself_list(list_node *head)
{
    if (head == NULL) return;
    list_node *pre = head;
    while (pre->next != head) {
        pre = pre->next; 
    }
    #define DIE_IDX 3

    int i = 1;
    while (pre->next != pre) {
        if (i == DIE_IDX) {
            pre->next = pre->next->next;
            i = 1;
        } else {
            i++;
            pre = pre->next;
        }
    }
}

void palindrome_list(list_node *head)
{
    if (head == NULL) return;
    list_node *mid = head;
    list_node *cur = head;
    if (cur->next != NULL &&
          cur->next->next != NULL) {
        mid = mid->next;
        cur = cur->next->next;
    }
    if (!mid->next) return;

    list_node *r_head = mid->next;
    list_node *r_pre = NULL;
    list_node *r_next;
    while (r_head) {
        r_next = r_head->next;
        r_head->next = r_pre;

        r_pre = r_head;
        r_head = r_next;
    }

    while (r_pre != NULL && head != NULL) {
        if (r_pre->data != head->data) {
            std::cout << "false" << std::endl;
            return;
        }
        r_pre = r_pre->next;
        head = head->next;
    }
    std::cout << "true" << std::endl;
}

void quick_arr(int arr[], int len, int base)
{
    int i = 0;
    int j = len - 1;

    while (i < j) {
        while (i < j && arr[i] < base) {
            i++;
        }
        if (i < j) {
            int tmp = arr[j];
            arr[j] = arr[i]; 
            arr[i] = tmp;
            j--;
        }

        while (i < j && arr[j] > base) {
            j--;
        }
        if (i < j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
        }
    }
}

void list_add(list_node *l1, list_node *l2)
{
    if (l1 == NULL || l2 == NULL) return;
    // 0 <= l1->data <= 9
    int j_w = 0;
    int res = 0;
    while (l1 != NULL && l2 != NULL) {
        res = (l1->data + l2->data + j_w) % 10;
        j_w = (l1->data + l2->data + j_w) / 10;
        std::cout << res << " ";
        l1 = l1->next;
        l2 = l2->next;
    }

    while (l1) {
        res = (l1->data + j_w) % 10;
        j_w = (l1->data + j_w) / 10;
        std::cout << res << " ";
        l1 = l1->next;
    }

    while (l2) {
        res = (l2->data + j_w) % 10;
        j_w = (l2->data + j_w) / 10;
        std::cout << res << " ";
        l2 = l2->next;
    }
    if (j_w) {
        std::cout << "1";
    }
}

void list_copy(list_node *l1)
{
    if (l1 == NULL) return;
    list_node *cur = l1;
    list_node *n_node = NULL;
    while (cur) {
        n_node = new list_node; 
        n_node->data = cur->data;
        n_node->rand = NULL;

        n_node->next = cur->next;
        cur->next = n_node;

        cur = n_node->next;
    }

    cur = l1;
    while (cur) {
        if (cur->rand) {
            cur->next->rand = cur->rand->next;
        }
        cur = cur->next->next;
    }

    cur = l1;
    list_node *tmp = l1->next;
    list_node *o_next;
    while (cur) {
        o_next = cur->next->next; 
        n_node = cur->next;
        cur->next = o_next;

        if (o_next) {
            n_node->next = o_next->next; 
        }
        cur = o_next; 
    }
}

void list_cycle(list_node *l1)
{
    if (l1 == NULL) return;
    list_node *walker = l1;
    list_node *runner = l1;

    while (runner && runner->next) {
        walker = walker->next;
        runner = runner->next->next;
        if (walker == runner) {
            std::cout << "true" << std::endl;
            break;
        } 
    }
#if 0
    if (!runner || !runner->next) return;
    runner = l1;
    while (runner != walker) {
        runner = runner->next;
        walker = walker->next;
    }
    std::cout << "cross: " << runner << td::endl;
#endif
}

list_node *list_del_val(list_node *l1, int val)
{
    if (l1 == NULL) return l1;
    while (l1 != NULL && l1->data == val) {
        l1 = l1->next;
    }
    if (l1 == NULL) return l1;
    list_node *pre = l1;
    list_node *cur = l1->next;
    while (cur) {
        if (cur->data == val) {
            pre->next = cur->next;
        } else {
            pre = cur;
        }
        cur = cur->next;
    }
    return l1;
}

void list_del_dup(list_node *l1)
{
    if (l1 == NULL) return;
    list_node *pre;
    list_node *cur = l1;
    list_node *next;
    while (cur) {
        next = cur->next;
        pre = cur;
        while (next) {
            if (next->data == cur->data) {
                pre->next = next->next;
            } else {
                pre = next;
            }
            next = next->next;
        }
        cur = cur->next;
    }
}

list_node *list_select_order(list_node *head)
{
#if 0
    if (head == NULL || head->next == NULL) return head;
    list_node *cur_pre = NULL;
    list_node *cur = head;
    list_node *n_node = NULL;
    list_node *select;
    list_node *select_pre;
    while (cur) {
        select = cur->next;
        select_pre = cur;
        while (select) {
            if (cur->data > select->data) {
                if (cur_pre == NULL) {
                    list_node *tmp = cur->next;
                    cur->next = select->next;
                    select_pre->next = cur;

                    select->next = tmp;
                } else {
                    if (cur->next != select) {
                        list_node *tmp = cur->next;
                        cur->next = select->next; 
                        select_pre->next = cur;

                        select->next = tmp;
                        cur_pre->next = select;
                    } else {
                        cur->next = select->next;
                        cur_pre->next = select;
                        select->next = cur;
                    }
                }
                list_node *tmp1 = cur;
                cur = select;
                select = tmp1;

                select_pre = select;
                select = select->next;
            } else {
                select_pre = select;
                select = select->next;
            }
        }

        show_list_node(cur);
        if (n_node == NULL) {
            n_node = cur;
        }
        cur_pre = cur;
        cur = cur->next; 
    }
    return n_node;
#elif (1 == 0)
    if (head == NULL || head->next == NULL) return head;

    list_node *cur = head;
    list_node *pre_min = NULL;
    list_node *pre_select = NULL;
    list_node *n_node = head;

    while (cur) {
        list_node *select = cur;  
        list_node *min = cur;
        while (select) {
            if (select->data < min->data) {
                min = select;
                pre_min = pre_select;
            }
            pre_select = select;
            select = select->next;
        }

        if (min == cur) {
            cur = cur->next;
            if (cur == NULL) {
                std::cout << "cur: " << pre_select->data << std::endl;
            }
        } else {
            pre_min->next = pre_min->next->next;            
            min->next = n_node;
            n_node = min;
        }
    }
    return n_node;
#elif ( 1 == 1)
    if (head == NULL || head->next == NULL) return head;
    list_node *n_node = NULL;
    list_node *pre_min;
    list_node *min;
    list_node *pre_select;
    list_node *select;
    while (head) {
        min = head; 
        pre_min = NULL;
        pre_select = head;
        select = head->next;

        while (select) {
            if (select->data < min->data) {
                min = select;
                pre_min = pre_select;
            }
            pre_select = select;
            select = select->next;
        }
        if (min == head) {
            head = head->next;
        } else {
            pre_min->next = pre_min->next->next;
        }

        min->next = n_node;
        n_node = min;
    }

#endif
}

void insert_ordered_clist(clist_node *head, int num)
{
    if (head == NULL) return;
    clist_node *pre = head;
    clist_node *cur = pre->next;;
    clist_node n_node;
    n_node.data = num;
    while (cur != head) {
        if (pre->data <= num && cur->data > num) {
            break;
        }
        pre = cur;
        cur = cur->next;
    }
    pre->next = &n_node; 
    n_node.next = cur;
}

list_node *merge_ordered_list(list_node *l1, list_node *l2)
{
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    list_node *cur1 = l1;
    list_node *cur2 = l2;
    list_node *n_tmp;
    list_node *new_head;
    if (cur1->data <= cur2->data) {
        n_tmp = cur1; 
        cur1 = cur1->next;
    } else {
        n_tmp = cur2; 
        cur2 = cur2->next;
    }
    new_head = n_tmp;

    while (cur1 != NULL && cur2 != NULL) {
        if (cur1->data <= cur2->data) {
            n_tmp->next = cur1; 
            cur1 = cur1->next;
        } else {
            n_tmp->next = cur2; 
            cur2 = cur2->next;
        }
        n_tmp = n_tmp->next;
    }

    if (cur1) {
        n_tmp->next = cur1;
    }
    if (cur2) {
        n_tmp->next = cur2;
    }
    return new_head;
}

list_node *merge_lr_list(list_node* head)
{
    if (head == NULL) return NULL;
    list_node *mid = head;
    list_node *cur = head->next;
    while (cur->next != NULL && 
          cur->next->next != NULL) {
        mid = mid->next;
        cur = cur->next->next;
    }
    list_node *right = mid->next;
    mid->next = NULL;

    list_node *new_head = head; // head: 1 3
    list_node *tmp = head;      // right: 5 7 9
    head = head->next;

    while (head != NULL && right != NULL) {
        tmp->next = right; 
        right = right->next;

        tmp = tmp->next;

        tmp->next = head;
        head = head->next;
        tmp = tmp->next;
    }

    if (head) {
        tmp->next = head;
    }
    if (right) {
        tmp->next = right;
    }
    return new_head;
}

void list_node_test()
{
    list_node l1; l1.data = 1;
    list_node l2; l2.data = 3;
    list_node l3; l3.data = 5;
    list_node l4; l4.data = 7;
    list_node l5; l5.data = 9;

    l1.next = &l2; l2.next = &l3;
    l3.next = &l4; l4.next = &l5;
    l5.next = NULL;

    list_node ll1; ll1.data = 2;
    list_node ll2; ll2.data = 4;
    list_node ll3; ll3.data = 6;
    list_node ll4; ll4.data = 8;
    list_node ll5; ll5.data = 10;

    ll1.next = &ll2; ll2.next = &ll3;
    ll3.next = &ll4; ll4.next = &ll5;
    ll5.next = NULL;

    //del_back(&l1);
    //del_mid(&l1);
    //list_node *tmp = reverse_list(&l1);
    //list_node *tmp = reverse_partion_list(&l1, 1, 2);
    //palindrome_list(&l1);
    //show_list_node(&l1);

    /*
    int arr[] = { 1, 9, 2, 4, 0 , 0, 0, 0};
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    quick_arr(arr, sizeof(arr)/sizeof(arr[0]), 3);
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        std::cout << arr[i] << " ";
    }
    */
    //list_add(&l1, &l1);
    //list_del_dup(&l1);
    //list_node *tmp = list_del_val(&l1, 4);
    //list_node *tmp = list_select_order(&l1);
    //list_node *tmp = merge_ordered_list(&l1, &ll1);
    list_node *tmp = merge_lr_list(&l1);
    show_list_node(tmp);
}

int main() 
{
    //wnd_max();
    //print_same();
    list_node_test();
    return 0;
}





























