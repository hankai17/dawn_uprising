// 2. 两数相加
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode head;
        ListNode* tmp = &head;
        int ac = 0;
        while (l1 != NULL || l2 != NULL || ac != 0) {
            int val1 = l1 != nullptr ? l1->val : 0;
            int val2 = l2 != nullptr ? l2->val : 0;
            int sum = val1 + val2 + ac;
            ac = sum / 10;

            ListNode* node = new ListNode;
            node->val = sum % 10;

            tmp->next = node;
            tmp = node;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        return head.next;
    }

// 19. 删除链表的倒数第 N 个结点
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL || head->next == NULL) return NULL;
        ListNode* slow = head;
        ListNode* fast = head;
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        if (!fast) return head->next;
        while (fast->next != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return head;
    }
};

// 21. 合并两个有序链表
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode head;
        ListNode* tmp = &head;
        while (l1 != NULL && l2 != NULL) {
            if (l1->val < l2->val) {
                tmp->next = l1;
                tmp = tmp->next;

                l1 = l1->next;
            } else {
                tmp->next = l2;
                tmp = tmp->next;

                l2 = l2->next;
            }
        }

        if (l1 == NULL) {
            tmp->next = l2;
        }
        if (l2 == NULL) {
            tmp->next = l1;
        }
        return head.next;
    }
};

// 23. 合并K个升序链表
class Solution {
public:
    struct cmp {
        bool operator() (const ListNode* l, const ListNode *r) {
            return l->val > r->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode head;
        head.next = NULL;
        ListNode *tmp = &head;

        priority_queue<ListNode*, vector<ListNode*>, cmp> pq;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != NULL) {
                pq.push(lists[i]);
            } 
        }
        while (!pq.empty()) {
            tmp->next = pq.top();
            tmp = tmp->next;
            pq.pop();
            if (tmp->next != NULL) {
                pq.push(tmp->next);
            }
        }
        return head.next;
    }
};

// 24. 两两交换链表中的节点
class Solution {
public:
    void resign_list1(ListNode* left, ListNode* start,
        ListNode* end, ListNode* right) {
    ListNode* pre = NULL;
    ListNode* h = start;
    ListNode* next;
    while (h != right) {
        next = h->next;
        h->next = pre;
    
        pre = h;
        h = next;
    }
    if (left) {
        left->next = pre;
    }
    start->next = right;
    }

    ListNode* swap_pair1(ListNode *head, int k)
{
    if (head == NULL) return NULL;
    if (k <= 1) return head;
    int i = 1;
    ListNode *cur = head;
    ListNode *next;
    ListNode *n_h = NULL;
    ListNode *left = NULL;
    ListNode *start = head;

    while (cur) {
        next = cur->next;
        if (i == k) {
            n_h = n_h == NULL ? cur : n_h;
            start = left == NULL ? head : left->next;
            resign_list1(left, start, cur, next);
            left = start;
            i = 0;
        }
        i++;
        cur = next;
    }
    return n_h ? n_h : head;
}

    ListNode* swapPairs(ListNode* head) {
        return swap_pair1(head, 2);
    }
};

// 25. K 个一组翻转链表
class Solution {
public:
     void resign_list1(ListNode* left, ListNode* start,
        ListNode* end, ListNode* right) {
    ListNode* pre = NULL;
    ListNode* h = start;
    ListNode* next;
    while (h != right) {
        next = h->next;
        h->next = pre;
    
        pre = h;
        h = next;
    }
    if (left) {
        left->next = pre;
    }
    start->next = right;
    }

    ListNode* swap_pair1(ListNode *head, int k)
{
    if (head == NULL) return NULL;
    if (k <= 1) return head;
    int i = 1;
    ListNode *cur = head;
    ListNode *next;
    ListNode *n_h = NULL;
    ListNode *left = NULL;
    ListNode *start = head;

    while (cur) {
        next = cur->next;
        if (i == k) {
            n_h = n_h == NULL ? cur : n_h;
            start = left == NULL ? head : left->next;
            resign_list1(left, start, cur, next);
            left = start;
            i = 0;
        }
        i++;
        cur = next;
    }
    return n_h ? n_h : head;
}

    ListNode* reverseKGroup(ListNode* head, int k) {
        return swap_pair1(head, k);
    }
};

// 61. 旋转链表
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (k == 0 || head == NULL) return head;
        int len = 1;

        ListNode* tmp = head;
        while (tmp->next) {
            len++;
            tmp = tmp->next;
        }
        k = k % len;
        if (k == 0) return head;

        tmp->next = head;

        for (int i = 0; i < len - k; i++) {
            tmp = tmp->next;
        }

        ListNode* n_h = tmp->next;
        tmp->next = NULL;
        return n_h;
    }
};

// 82. 删除排序链表中的重复元素 II
ListNode* deleteDuplicates(ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    ListNode* next = head->next;

    if (head->val == next->val) {
        while (next && head->val == next->val) {
            next = next->next;
        }
        head = deleteDuplicates(next);
    } else {
        head->next = deleteDuplicates(next);
    }
    return head;
}

// 83. 删除排序链表中的重复元素
ListNode* deleteDuplicates(ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    ListNode* next = head->next;

    //head->next = deleteDuplicates(head->next);
    head->next = deleteDuplicates(next); // 一样

    return head->val == head->next->val ? head->next : head;
}

// 86. 分隔链表
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode less_node;
        ListNode* less = &less_node;
        ListNode great_node;
        ListNode* great = &great_node;

        while (head) {
            if (head->val < x) {
                less->next = head;
                less = less->next;
            } else {
                great->next = head;
                great = great->next;
            }
            head = head->next;
        }
        great->next = NULL;
        less->next = great_node.next;
        return less_node.next;
    }
};

// 92. 反转链表 II
class Solution {
public:
    ListNode* reverse(ListNode* left, ListNode* start,
    ListNode* end, ListNode* right)
{
    ListNode* pre = right;
    ListNode* next;
    while (start != right) {
        next = start->next;
        start->next = pre;

        pre = start;
        start = next;
    }
    if (left != NULL) {
        left->next = end;
    }
    return left == NULL ? end : left;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (head == NULL || left == right) return head;
    int len = 0;
    int i = 1;
    ListNode* cur = head;
    while (cur) {
        cur = cur->next;
        len++;
    }
  
    cur = head;
    ListNode* pre = NULL;
    ListNode* start = NULL;
    ListNode* start_pre = NULL;

    ListNode* end = NULL;
    ListNode* end_after = NULL;

    while (cur) {
        if (i == left) {
            start = cur;
            start_pre = pre;
        }
        if (i == right) {
            end = cur;
        }
        if (i == right + 1) {
            end_after = cur;
        }
        pre = cur;
        cur = cur->next;
        i++;
    }
    ListNode* n_head = reverse(start_pre, start, end, end_after);
    return start_pre == NULL ? n_head : head;
}
};

// 109. 有序链表转换二叉搜索树
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        TreeNode* root;       
        if(!head) return nullptr;
        
        if(!head->next){
            root = new TreeNode(head->val);
            return root;
        }        
        
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *prev = head;
        
        while(fast != NULL && fast->next != NULL){
            fast = fast->next->next;
            slow = slow->next;
        }
        
        while(prev->next != slow)
            prev = prev->next;      
        root = new TreeNode(slow->val);
        ListNode* headRight = slow->next;
        prev->next = nullptr;
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(headRight);
        
        return root;
    }
};

// 141. 环形链表
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL) {
            return false;
        }

        ListNode *walk = head;
        ListNode *run = head;
        while (run != NULL && run->next != NULL) {
            walk = walk->next;
            run = run->next->next;
            if (walk == run) return true;
        }
        return false;
    }
};

// 142. 环形链表 II
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL) {
            return NULL;
        }

        ListNode *walk = head;
        ListNode *run = head;
        while (run != NULL && run->next != NULL) {
            walk = walk->next;
            run = run->next->next;
            if (walk == run) break;
        }
        if (walk != run) return NULL; 
        
        if (!run || !run->next) {
            return NULL;
        }
        run = head;
        while (run != walk) {
            run = run->next;
            walk = walk->next;
        }
        if (run == walk) return run;
        return NULL;
    }
};

// 146. LRU 缓存机制
class LRUCache {
public:
    typedef pair<int, int> item_type;

    list<item_type> m_l;
    unordered_map<int, list<item_type>::iterator> m_map;
    int m_cap;

    LRUCache(int capacity) {
        m_cap = capacity;
    }

    void update(int key) {
        auto it = m_map.find(key);
        if (it != m_map.end()) {
            m_l.splice(m_l.begin(), m_l, it->second);
        }
    }
    
    int get(int key) {
        auto it = m_map.find(key);
        if (it == m_map.end()) {
            return -1;
        }
        update(key);
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = m_map.find(key);
        if (it != m_map.end()) {
            it->second->second = value;
            update(key);
            return;
        } else {
            if (m_l.size() == m_cap) {
                m_map.erase(m_l.back().first);
                m_l.pop_back();
            }
            m_l.push_front(pair(key, value));
            m_map.insert(make_pair(key, m_l.begin()));
        }
    }
};

// 114. 二叉树展开为链表
class Solution {
public:

    void flatten(TreeNode* root) {
        if (root == NULL) return;
        flatten(root->left);
        flatten(root->right);
        TreeNode * tmp = nullptr;
        
        tmp = root->right;
        
        root->right = root->left;
        root->left = nullptr;
        while (root->right) {
            root = root->right;
        }
        root->right = tmp;
    }
};

// 160. 相交链表
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL) return NULL;
        ListNode *h1 = headA;
        ListNode *h2 = headB;
        while (h1 != h2) {
            h1 = h1 == NULL ? headB : h1->next;
            h2 = h2 == NULL ? headA : h2->next;
        }
        return h1;
    }
};

// 206. 反转链表
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = NULL;
        ListNode *next;
        while (head) {
            next = head->next;
            head->next = pre;

            pre = head;
            head = next;
        }
        return pre;
    }
};

// 234. 回文链表
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == NULL) return true;
        ListNode *walk = head;
        ListNode *run = head;
        while (run && run->next && run->next->next) {
            walk = walk->next;
            run = run->next->next;
        }
        ListNode *right = walk->next;

        ListNode *pre = NULL;
        ListNode *next;
        while (right) {
            next = right->next;
            right->next = pre;

            pre = right;
            right = next;
        }

        while (head && pre) {
            if (head->val != pre->val) {
                return false;
            }
            head = head->next;
            pre = pre->next;
        }
        return true;
    }
};
