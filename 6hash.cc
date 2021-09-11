#include <iostream>
#include <vector>
#include <map>
//#include <hash_map>
#include <queue> // pq default big heap

struct cmp {
    bool operator()(const std::pair<int, int> &lhs, 
            const std::pair<int, int> &rhs) {
        return lhs.second > rhs.second;
    }                          
};                          

// https://blog.csdn.net/lijiang1991/article/details/52727478?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-4.no_search_link&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-4.no_search_link
//priority_queue <int,vector<int>,greater<int> > q; //升序队列，小顶堆
//priority_queue <int,vector<int>,less<int> >q; //降序队列，大顶堆
//greater和less是std实现的两个仿函数

std::vector<int> topKFrequent(std::vector<int> &nums, int k) 
{
    std::vector<int> ret;
    if (k < 1 || nums.size() < k) return ret;

    std::map<int, int> m;
    for (int i = 0; i < nums.size(); i++) {
        if (m.find(nums[i]) == m.end()) {
            m[nums[i]] = 1;
        } else {
            m[nums[i]]++;
        }
    }

    std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>, cmp> pq;

    for (auto iter = m.begin(); iter != m.end(); iter++) {
        if (pq.size() < k) {
            pq.push(*iter); // <1, 1> <2, 2>
            std::cout << "push it->first: " << iter->first << ", " 
                    << iter->second << std::endl;
        } else {
            std::pair<int, int> tmp = pq.top(); // <1, 1> <2, 2>
            if (iter->second > tmp.second) {
                pq.pop();
                pq.push(*iter);         
            }
        }
    }

    if (pq.size() < k) {
        return ret;
    }

    ret.resize(pq.size());
    while (!pq.empty()) {
        ret[--k] = pq.top().first;
        //ret.push_back(pq.top().first);
        //// 2,2   1,3
        //std::cout << "pq.top: " << pq.top().first << ", " << pq.top().second << std::endl;
        pq.pop();
    }
    for (int i = 0; i < ret.size(); i++) {
        std::cout << ret[i] << " ";
    }
    return ret;
}

int merge(std::map<int, int>& m, int less, int more) {
    int left = less - m[less] + 1;
    int right = more + m[more] - 1;
    int len = right - left + 1;
    m[left] = len;
    m[right] = len;
    return len;
}

#if 0
int longestConsecutive(std::vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int ret = 1;
    std::map<int, int> m;
    for (int i = 0; i < nums.size(); i++) {
        if (!m[nums[i]]) {
            m[nums[i]] = 1;
            if (m[nums[i] - 1]) {
                ret = std::max(ret, merge(m, nums[i] - 1, nums[i]));
            }
            if (m[nums[i] + 1]) {
                ret = std::max(ret, merge(m, nums[i], nums[i] + 1));
            }
        }
    }
    return ret;
}
#else 
int longestConsecutive(std::vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int ret = 1;
    std::map<int, int> m;
    for (int i = 0; i < nums.size(); i++) {
        if (!m.count(nums[i])) {
            m[nums[i]] = 1;
            if (m.count(nums[i] - 1)) {
                ret = std::max(ret, merge(m, nums[i] - 1, nums[i]));
            }
            if (m.count(nums[i] + 1)) {
                ret = std::max(ret, merge(m, nums[i], nums[i] + 1));
            }
        }
    }
    return ret;
}
#endif

#if 0
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
#endif

int test()
{
    //std::vector<int> v = { 2, 2, 3, 3, 3, 1, 4, 4, 4, 4};
    //std::vector<int> v = { 1,1,1,2,2,3};
    std::vector<int> v = { 100,4,200,1,3,2};
    //topKFrequent(v, 2);
	std::cout << longestConsecutive(v) << std::endl;
    return 0;
}

int main()
{
    test();
    return 0;
}

/*
topk （前k大）用小根堆，维护堆大小不超过 k 即可。每次压入堆前和堆顶元素比较，如果比堆顶元素还小，直接扔掉，否则压入堆。检查堆大小是否超过 k，如果超过，弹出堆顶。复杂度是 nlogk
避免使用大根堆，因为你得把所有元素压入堆，复杂度是 nlogn，而且还浪费内存。如果是海量元素，那就挂了。
[注意]

求前 k 大，用小根堆，求前 k 小，用大根堆。 
 
 */
