// 95. 不同的二叉搜索树 II
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n) return generate(1, n);
        else return vector<TreeNode*> {};
    }

    vector<TreeNode*> generate(int left, int right) {
        vector<TreeNode*> res;
        if (left > right) {
            res.push_back(nullptr);
            return res;
        }

        for (int i = left; i <= right; i++) {
            vector<TreeNode*> left_nodes = generate(left, i - 1);
            vector<TreeNode*> right_nodes = generate(i + 1, right);
            for (TreeNode *left_node : left_nodes) {
                for (TreeNode *right_node : right_nodes) {
                    TreeNode *t = new TreeNode(i);
                    t->left = left_node;
                    t->right = right_node;
                    res.push_back(t);
                }
            }
        }
        return res;
    }
};

// 96. 不同的二叉搜索树
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};

// 98. 验证二叉搜索树
class Solution {
public:
    int* last = NULL;
    bool isValidBST(TreeNode* root) {
        if (root != NULL) {
        if(!isValidBST(root->left)) return false;
        if (last && *last >= root->val) return false;
        last = &root->val;
        if(!isValidBST(root->right)) return false;
        return true;
        } else {
             return true;
        }
    }
};

// 100. 相同的树
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == NULL && q == NULL) {
            return true;
        }
        if (p == NULL || q == NULL) {
            return false;
        }
        if (p->val != q->val) {
            return false;
        }
         return
                isSameTree(p->left, q->left) && 
                isSameTree(p->right, q->right);
    }
};

// 101. 对称二叉树
class Solution {
public:
    bool is_sym(TreeNode* root1, TreeNode* root2) {
        if (root1 == NULL && root2 == NULL) return true;
        if (root1 == NULL || root2 == NULL) return false;
        if (root1->val == root2->val) 
            return is_sym(root1->left, root2->right) &&
                is_sym(root1->right, root2->left);
        return false;
    }

    bool isSymmetric(TreeNode* root) {
        return is_sym(root, root);
    }
};

// 102. 二叉树的层序遍历
class Solution {
public:
#if 0
    void pre(TreeNode* root, int l, vector<vector<int>>& res) {
        if (root == NULL) {
            return;
        }
        if (l >= res.size()) {
            res.push_back(vector<int>{});
        }
        res[l].push_back(root->val);
        pre(root->left, l + 1, res);
        pre(root->right, l + 1, res);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        pre(root, 0, res);
        return res;
    }
    #endif
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL) return res;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            vector<int> t;
            int s = q.size();
            for (int i = 0; i < s; i++) {
                auto tmp = q.front();
                q.pop();
                t.push_back(tmp->val);
                if (tmp->left) {
                    q.push(tmp->left);
                }
                if (tmp->right) {
                    q.push(tmp->right);
                }
            }
            res.push_back(t);
        }
        return res;
    }
};

// 103. 二叉树的锯齿形层序遍历
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> ret;
        int f = 0;
        if (root == NULL) return ret;
        q.push(root);

        while (!q.empty()) {
            vector<int> res;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto tmp = q.front();
                q.pop();
                res.push_back(tmp->val);
                if (tmp->left) {
                    q.push(tmp->left);
                }
                if (tmp->right) {
                    q.push(tmp->right);
                }
            }

            if (f % 2 == 1) {
                reverse(res.begin(), res.end());
            }
            ret.push_back(res);
            f++;
        }
        return ret;
    }
};

// 104. 二叉树的最大深度
class Solution {
public:
    int max_dep(TreeNode* root, int l) {
        if (root == NULL) return l;
        return max(max_dep(root->left, l + 1),
                max_dep(root->right, l + 1));
    }

    int maxDepth(TreeNode* root) {
        int l = 0;
        return max_dep(root, l);
    }
};

// 105. 从前序与中序遍历序列构造二叉树
class Solution {
public:
    TreeNode* pre_in(vector<int>& pre, int pi, int pj, vector<int>& in, int ni, int nj, map<int,int> &in_map) {
        if (pi > pj || ni > nj) return NULL;
        TreeNode* root = new TreeNode;
        root->val = pre[pi];

        auto it = in_map.find(root->val);
        int idx = it->second;

        root->left = pre_in(pre, pi + 1, idx - ni + pi, in, ni, idx - 1, in_map);
        root->right = pre_in(pre, pi + idx - ni + 1, pj, in, idx + 1, nj, in_map);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0 || inorder.size() == 0) return nullptr;
        map<int, int> in_map;
        for (int i = 0; i < inorder.size(); i++) {
            in_map.insert(make_pair(inorder[i], i));
        }
        return pre_in(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, in_map);
    }
};

// 106. 从中序与后序遍历序列构造二叉树
class Solution {
public:
    TreeNode* compose_tree(vector<int>& in, int ni, int nj, vector<int>& po, int pi, int pj, map<int, int>& in_map) {
        if (ni > nj || pi > pj) return nullptr;
        TreeNode* new_node = new TreeNode;
        new_node->val = po[pj];

        auto iter = in_map.find(new_node->val);
        int idx = iter->second; 

        new_node->left = compose_tree(in, ni, idx - 1, po, pi, pi + (idx - ni) - 1, in_map);
        new_node->right = compose_tree(in, idx + 1, nj, po, pi + (idx - ni), pj - 1, in_map);
        return new_node;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0 || postorder.size() == 0) return nullptr;
        map<int, int> in_map;
        for (int i = 0; i < inorder.size(); i++) {
            in_map.insert(make_pair(inorder[i], i));
        }
        return compose_tree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1, in_map);
    }
};

// 107. 二叉树的层序遍历 II
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL) return res;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            vector<int> t;
            int s = q.size();
            for (int i = 0; i < s; i++) {
                auto tmp = q.front();
                q.pop();
                t.push_back(tmp->val);
                if (tmp->left) {
                    q.push(tmp->left);
                }
                if (tmp->right) {
                    q.push(tmp->right);
                }
            }
            res.push_back(t);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

// 108. 将有序数组转换为二叉搜索树
class Solution {
public:
    TreeNode* compose_tree(vector<int> &nums, int l, int r) {
        if (l > r) return NULL;
        int mid = l + (r - l) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = compose_tree(nums, l, mid - 1);
        root->right = compose_tree(nums, mid + 1, r);
        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return compose_tree(nums, 0, nums.size() - 1);
    }
};

// 109. 有序链表转换二叉搜索树
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        #if 0
        if (head == NULL) return NULL;
        TreeNode* root;
        if (head->next == NULL) {
            root = new TreeNode(head->val);
            return root;
        }
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* r_head = slow->next->next;
        ListNode* mid = slow->next;
        slow->next = NULL;
        root = new TreeNode(mid->val);
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(r_head);
        return root;
        #else


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
        #endif
    }
};

// 110. 平衡二叉树
class Solution {
public:
    int get_height(TreeNode* root, int l) {
        if (root == NULL) return l;
        return max(get_height(root->left, l + 1),
            get_height(root->right, l + 1));
    }

    bool isBalanced(TreeNode* root) {
        if (root == NULL) return true;
        int l_h = get_height(root->left, 0);
        int r_h = get_height(root->right, 0);

        if (abs(l_h - r_h) > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
};

// 111. 二叉树的最小深度
class Solution {
public:
    int get_heigh(TreeNode* root, int l) {
        if (root == NULL) return l;
        if (root->left == NULL && root->right != NULL) {
            return get_heigh(root->right, l + 1);
        }
        if (root->left != NULL && root->right == NULL) {
            return get_heigh(root->left, l + 1);
        }
        return min(get_heigh(root->left, l + 1),
            get_heigh(root->right, l + 1));
    }
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        return get_heigh(root, 0);
    }
};

// 112. 路径总和
class Solution {
public:
    #if 0
    void get_path_sum(TreeNode* root, map<int, int>& m, int pre_sum, int targetSum, int& num) {
        if (root == nullptr) {
            return;
        }
        int cur_sum = pre_sum + root->val;
        if (cur_sum == targetSum) {
            num++;
        } else {
            auto it = m.find(targetSum - cur_sum);
            if (it != m.end()) {
                num += it->second;
            }
        }
        auto it = m.find(cur_sum);
        if (it != m.end()) {
            it->second++;
        } else {
            m.insert(make_pair(cur_sum, 1));
        }

        get_path_sum(root->left, m, cur_sum, targetSum, num);
        get_path_sum(root->right, m, cur_sum, targetSum, num);
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            if (targetSum == 0) {
                return true;
            } else {
                return false;
            }
        }
        map<int, int> sum_map;
        int pre_sum = 0;
        int num = 0;
        get_path_sum(root, sum_map, pre_sum, targetSum, num);
        return num ? true : false;
    }
    #else 
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return false;
        if (root->left == nullptr && root->right == nullptr) {
            return targetSum - root->val == 0;
        }
        return hasPathSum(root->left, targetSum - root->val) ||
            hasPathSum(root->right, targetSum - root->val);
    }
    #endif
};

// 113. 路径总和 II
class Solution {
public:
    vector<vector<int>> res;

    void dfs(TreeNode* root, vector<int>& track, int targetSum) {
        if (root == nullptr) return;
        track.push_back(root->val);

        if (root->left == NULL && root->right == NULL) {
            if (targetSum - root->val == 0) {
                res.push_back(track);
            }
            //return;
        }
        dfs(root->left, track, targetSum - root->val);
        dfs(root->right, track, targetSum - root->val);
        track.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> track;
        dfs(root, track, targetSum);
        return res;
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

// 116. 填充每个节点的下一个右侧节点指针
class Solution {
public:
    Node* connect(Node* root) {
        if (root == NULL) return NULL;
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int s = q.size();
            for (int i = 0; i < s; i++) {
                auto tmp = q.front();
                q.pop();
                if (i == s - 1) {
                    tmp->next = NULL;
                } else {
                    tmp->next = q.front();
                }

                if (tmp->left) {
                    q.push(tmp->left);
                }
                if (tmp->right) {
                    q.push(tmp->right);
                }
            }
        }
        return root;
    }
};

// 226. 翻转二叉树
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;
        TreeNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

// 236. 二叉树的最近公共祖先
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) return NULL;
        if (root->val == p->val || root->val == q->val) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left && right) {
            return root;
        }
        return left ? left : right;
    }
};

// 337. 打家劫舍 III
class Solution {
public:
    int try_rob(TreeNode* root) {
        if (!root) return 0;
        int res1 = 0;
        res1 += root->val;
        if (root->left) {
            res1 += (try_rob(root->left->right) + try_rob(root->left->left));
        }
        if (root->right) {
            res1 += (try_rob(root->right->left) + try_rob(root->right->right));
        }

        int res2 = 0;
        res2 += (try_rob(root->left) + try_rob(root->right));
        
        int res = max(res1, res2);
        return res; 
    }

    int rob(TreeNode* root) {
        return try_rob(root);
    }
};

// 437. 路径总和 III
class Solution {
public:
    int path_num;

    void get_sum(TreeNode* root, int s) {
        if (root == NULL) return;
        s -= root->val;
        if (s == 0) {
            path_num++;
        }
        get_sum(root->left, s);
        get_sum(root->right, s);
    }
    int pathSum(TreeNode* root, int sum) {
        if (root == NULL) return 0;
        get_sum(root, sum);
        pathSum(root->left, sum);
        pathSum(root->right, sum);
        return path_num;
    }
};
