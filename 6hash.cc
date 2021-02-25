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

    while (!pq.empty()) {
        ret.push_back(pq.top().first);
        pq.pop();
    }
    for (int i = 0; i < ret.size(); i++) {
        std::cout << ret[i] << " ";
    }
    return ret;
}

bool cmp(const vector<int>& a,const vector<int>& b){
        if(a[0] == b[0])
            return a[1]<b[1];
        return a[0]>b[0];
}

int test()
{
    std::vector<int> v = { 2, 2, 3, 3, 3, 1, 4, 4, 4, 4};
    topKFrequent(v, 2);
    return 0;
}

int main()
{
    test();
    return 0;
}
