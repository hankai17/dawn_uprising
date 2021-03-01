#include <iostream>
#include <stack>
#include <string>
#include <list>
#include <map>

struct tree_node {
    int                 data;
    struct tree_node   *left;
    struct tree_node   *right;
    struct tree_node   *parent;
};

std::string compose_blank(int num)
{
    std::string str;
    for (int i = 0; i < num; i++) {
        str += " ";
    }
    return str;
}

// TREE NUM1: recur print
void pre_order_recur(tree_node *root)
{
    if (root == NULL) return;
    std::cout << root->data << " ";
    pre_order_recur(root->left);
    pre_order_recur(root->right);
}

void in_order_recur(tree_node *root)
{
    if (root == NULL) return;
    in_order_recur(root->left);
    std::cout << root->data << " ";
    in_order_recur(root->right);
}

void pos_order_recur(tree_node *root)
{
    if (root == NULL) return;
    pos_order_recur(root->left);
    pos_order_recur(root->right);
    std::cout << root->data << " ";
}

// TREE NUM2: nono-recur print
void pre_order(tree_node *root)
{
    if (root == NULL) return;
    std::stack<tree_node*> s;
    s.push(root);

    while (!s.empty()) {
        tree_node* tmp = s.top();
        s.pop();
        std::cout << tmp->data << " ";
        
        if (tmp->right) {
            s.push(tmp->right);
        }
        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}

void in_order(tree_node *root)
{
    if (root == NULL) return;
    std::stack<tree_node*> s;
    tree_node *tmp = root;

    while (!s.empty() || tmp) {
        if (tmp) {
            s.push(tmp);
            tmp = tmp->left;
        } else {
            tmp = s.top();
            s.pop();
            std::cout << tmp->data << " ";
            tmp = tmp->right;
        }
    }
}

void pos_order(tree_node *root)
{
    if (root == NULL) return;
    std::stack<tree_node*> s1;
    std::stack<tree_node*> s2;
    tree_node *tmp = root;
    s1.push(root);

    while (!s1.empty()) {
        tmp = s1.top();
        s1.pop();

        s2.push(tmp);
        if (tmp->left) {
            s1.push(tmp->left);
        }
        if (tmp->right) {
            s1.push(tmp->right);
        }
    }
    while (!s2.empty()) {
        tmp = s2.top();
        s2.pop();
        std::cout << tmp->data << " ";
    }
}

// TREE NUM3: print tree struct
#define VAL_MAX_LEN 17
void print_struct(tree_node *root, int h, std::string str)
{
    if (root == NULL) return;
    print_struct(root->right, h + 1, "v");

    std::string val = str + std::to_string(root->data) + str;
    int left_space = (VAL_MAX_LEN - val.length()) / 2;
    int right_space = VAL_MAX_LEN - left_space - val.length();
    val = compose_blank(h * VAL_MAX_LEN) + compose_blank(left_space) + val + compose_blank(right_space);
    std::cout << val << std::endl;
    print_struct(root->left, h + 1, "^");
}

// TREE NUM4: print tree leaf
void print_leaf(tree_node *root)
{
    if (root == NULL) return;
    if (root->left == NULL && 
            root->right == NULL) {
        std::cout << root->data << " ";
    }
    print_leaf(root->left);
    print_leaf(root->right);
}

/* just like strlen */
// TREE NUM5: print tree heigh
int get_heigh(tree_node *root, int h)
{
    if (root == NULL) return h;
    return std::max(get_heigh(root->left, h + 1), 
          get_heigh(root->right, h + 1));
}

// TREE NUM6: print special edge
void edge_set_map(tree_node *root, int h, tree_node* arr[][2])
{
    if (root == NULL) return;
    if (!arr[h][0]) {
        arr[h][0] = root;
    }
    arr[h][1] = root;
    edge_set_map(root->left, h + 1, arr);
    edge_set_map(root->right, h + 1, arr);
}

void edge_print_ideal_leaf(tree_node *root, int h, tree_node* arr[][2])
{
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        if (root != arr[h][0] && root != arr[h][1]) {
            std::cout << root->data << " ";
        }
    }
    edge_print_ideal_leaf(root->left, h + 1, arr);
    edge_print_ideal_leaf(root->right, h + 1, arr);
}

void print_edge(tree_node *root)
{
    if (root == NULL) return;
    int heigh = get_heigh(root, 0);
    tree_node* arr[heigh][2] = {{0}};

    // print left edge
    edge_set_map(root, 0, arr);
    for (int i = 0; i < heigh; i++) {
        std::cout << (arr[i][0])->data << " ";
    }

    // print ideal leaf
    edge_print_ideal_leaf(root, 0, arr);

    // print right edge
    for (int i = heigh - 1; i > 0; i--) {
        std::cout << (arr[i][1])->data << " ";
    }
}

// TREE NUM7: serial tree 
std::string serial_tree(tree_node *root)
{
    if (root == NULL) return "#!";
    std::string val = std::to_string(root->data) + "!";
    val += serial_tree(root->left);
    val += serial_tree(root->right);
    return val;
}

void re_serial_tree() {} // TODO

// TREE NUM8: level print
void level_print(tree_node *root)
{
    if (root == NULL) return;
    std::list<tree_node*> l;
    tree_node *tmp;
    l.push_back(root);

    while (!l.empty()) {
        tmp = l.front(); 
        l.pop_front();
        std::cout << tmp->data << " ";
        if (tmp->left) {
            l.push_back(tmp->left);
        }
        if (tmp->right) {
            l.push_back(tmp->right);
        }
    }
}


// TREE NUM9: sum max len tree
#define K 7
int get_max_len(tree_node *root, int pre_sum, int l, int max_len, std::map<int, int> &m)
{
    if (root == NULL) return max_len;
    int cur_sum = pre_sum + root->data;

    auto it = m.find(cur_sum);
    if (it == m.end()) {
        m.insert(std::make_pair(cur_sum, l));
    }
    
    if (cur_sum == K) {
        max_len = l + 1;
    } else if (cur_sum > K) {
        it = m.find(cur_sum - K);
        if (it != m.end()) {
            max_len = max_len > l - it->second ? max_len :
                l - it->second;
        }
    }

    max_len = get_max_len(root->left, cur_sum, l + 1, max_len, m);
    max_len = get_max_len(root->right, cur_sum, l + 1, max_len, m);
    /*
    it = m.find(cur_sum);
    if (it != m.end()) {
        m.erase(cur_sum);
    }
    */
}

void get_k_num(tree_node* root, int pre_sum, std::map<int, int>& m, 
            int sum, int& num) {
    if (root == NULL) return;
    int cur_sum = pre_sum + root->data;
    std::cout << "cur_sum: " << cur_sum << std::endl;
    if (cur_sum == sum) {
        num++;
    } else if (cur_sum != sum) {
        auto it = m.find(cur_sum - sum);
        if (it != m.end()) {
            num += it->second;
        }
    }
    auto it = m.find(cur_sum);
    if (it == m.end()) {
        m.insert(std::make_pair(cur_sum, 1));
    } else {
        it->second++;
    }
    get_k_num(root->left, cur_sum, m, sum, num);
    get_k_num(root->right, cur_sum, m, sum, num);
}

int pathSum(tree_node* root, int sum) {
    std::map<int, int> m;
    int num = 0;
    int pre_sum = 0;
    get_k_num(root, pre_sum, m, sum, num);
    return num;
}

// TREE NUM10: contains
int check(tree_node *root1, tree_node *root2)
{
    if (root2 == NULL) return 1;
    if (root1 == NULL || 
            root1->data != root2->data) {
        return 0;
    }
    return check(root1->left, root2->left) &&
        check(root1->right, root2->right);
}

int contains_tree(tree_node *root, tree_node *child)
{
    return check(root, child) || 
        contains_tree(root->left, child) ||
        contains_tree(root->right, child);
}

// TREE NUM11: is balance
int get_heigh(tree_node* root, int l, int &result)
{
    if (root == NULL) return l;
    int lH = get_heigh(root->left, l + 1, result);
    if (result == 0) {
        return l;
    }
    int rH = get_heigh(root->right, l + 1, result);
    if (result == 0) {
        return l;
    }
    if (abs(lH - rH) > 1) {
        result = 0;
    }
    return lH > rH ? lH : rH;
}

void is_balance(tree_node *root)
{
    if (root == NULL) return;
    int result;
    get_heigh(root, 1, result);
    std::cout << "result: " << result << std::endl;
}

// TREE NUM12: is bst pos
int is_pos(int arr[], int start, int end)
{
    if (start == end) return 1;
    int less = -1;
    int more = end;
    for (int i = 0; i < end; i++) {
        if (arr[i] < arr[end]) {
            less = i;
        } else {
            more = more == end ? i : more;
        }
    }
    if (less == -1 || more == end) {
        return is_pos(arr, start, end - 1);
    }
    if (less != more - 1) {
        return 0;
    }
    return is_pos(arr, start, less) && is_pos(arr, more, end - 1);
}

int is_search_tree_pos(int arr[], int len)
{
    if (arr == NULL || len == 0) return 0;
    return is_pos(arr, 0, len - 1);
}

// TREE NUM13: is complete bt
int is_complete_tree(tree_node *root)
{
    if (root == NULL) return 1;
    std::list<tree_node*> l;
    tree_node *tmp;
    l.push_back(root);
    int leaf = 0;

    while (!l.empty()) {
        tmp = l.front(); 
        l.pop_front();

        tree_node *left = tmp->left;
        tree_node *right = tmp->right;
        if (left == NULL && right != NULL) return 0;
        if (leaf && (left != NULL || right != NULL)) {
            return 0;
        }

        if (left) {
            l.push_back(left);
        }
        if (right) {
            l.push_back(right);
        } else {
            leaf = 1;
        }
    }
    return 1;
}

// TREE NUM14: generate balance search tree
tree_node *generate(int arr[], int start, int end)
{
    if (start > end) return NULL;
    int mid = (start + end) / 2;

    tree_node *head = new tree_node;
    head->data = arr[mid];

    head->left = generate(arr, start, mid - 1);
    head->right = generate(arr, mid + 1, end);
    return head;
}

tree_node *generate_balance_BST(int arr[], int len)
{
    if (arr == NULL || len == 0) return NULL;
    return generate(arr, 0, len - 1);
}

// TREE NUM15: get next
tree_node *get_left_most(tree_node *root)
{
    if (root == NULL) return NULL;
    while (root->left) {
        root = root->left;
    }
    return root;
}

tree_node *get_next(tree_node *root)
{
    if (root == NULL) return NULL;
    if (root->right != NULL) {
        return get_left_most(root->right);
    } else {
        tree_node *parent = root->parent;
        while (parent != NULL && parent->left != root) {
            root = parent;
            parent = root->parent;
        }
        return parent;
    }
}


// TREE NUM16: lowest ancestor
tree_node *lowest_ancestor(tree_node *root, int val1, int val2)
{
    if (root == NULL) return NULL;
    if (root->data == val1 || root->data == val2) return root;
    tree_node * left = lowest_ancestor(root->left, val1, val2);
    tree_node * right = lowest_ancestor(root->right, val1, val2);
    if (left != NULL && right != NULL) {
        return root;
    }
    return left != NULL ? left : right;
}

// TREE NUM17: pre in 2 tree
tree_node *pre_in(int pre[], int pi, int pj, int in[], int ni, int nj, 
      std::map<int, int> &in_map)
{
    if (pi > pj) return NULL;
    tree_node *node = new tree_node;
    node->data = pre[pi];

    auto it = in_map.find(node->data);
    int idx = it->second;

    node->left = pre_in(pre, pi + 1, pi + idx - ni, in, ni, idx - 1, in_map);
    node->right = pre_in(pre, pi + idx - ni + 1, pj, in, idx + 1, nj, in_map);
    return node;
}

tree_node *pre_in_2_tree(int pre[], int in[], int len)
{
    if (pre == NULL || in == NULL || len == 0) return NULL;
    std::map<int, int> in_map;
    for (int i = 0; i < len; i++) {
        in_map.insert(std::make_pair(in[i], i));
    }
    return pre_in(pre, 0, len - 1, in, 0, len - 1, in_map);
}

// TREE NUM18: pre in generate pos tree
int set_pos(int pre[], int pi, int pj, int in[], int ni, int nj,
      int result[], int si, std::map<int, int> &in_map)
{
    if (pi > pj) return si;
    result[si--] = pre[pi];

    auto it = in_map.find(pre[pi]);
    int idx = it->second;

    si = set_pos(pre, pj - nj + idx + 1, pj, in, idx + 1, nj, result, si, in_map);
    return set_pos(pre, pi + 1, pi + idx - ni, in, ni, idx - 1, result, si, in_map);
}

int *get_pos_arr(int pre[], int in[], int len)
{
    if (pre == NULL || in == NULL || len == 0) return NULL;
    int* result = new int[len];
    std::map<int, int> in_map;
    for (int i = 0; i < len; i++) {
        in_map.insert(std::make_pair(in[i], i));
    }
    set_pos(pre, 0, len - 1, in, 0, len - 1, result, len - 1, in_map);
    return result;
}

// TREE NUM19: merge_tree
tree_node *merge_tree(tree_node *root1, tree_node *root2)
{
    if (root1 == NULL && root2 == NULL) return NULL;
    tree_node *new_node = new tree_node;

    if (root1 != NULL && root2 != NULL) {
        new_node->data = root1->data + root2->data;
        new_node->left = merge_tree(root1->left, root2->left);
        new_node->right = merge_tree(root1->right, root2->right);
    } else if (root1 != NULL && root2 == NULL) {
        new_node->data = root1->data;
        new_node->left = merge_tree(root1->left, NULL);
        new_node->right = merge_tree(root1->right, NULL);
    } else if (root1 == NULL && root2 != NULL) {
        new_node->data = root2->data;
        new_node->left = merge_tree(NULL, root2->left);
        new_node->right = merge_tree(NULL, root2->right);
    }
    return new_node;
}

void test(tree_node *root)
{
    pre_order_recur(root);
    std::cout << std::endl;
    in_order_recur(root);
    std::cout << std::endl;
    pos_order_recur(root);
    std::cout << std::endl;

    pre_order(root);
    std::cout << std::endl;
    in_order(root);
    std::cout << std::endl;
    pos_order(root);
    std::cout << std::endl;

    std::cout << "get_heigh: " << get_heigh(root, 0) << std::endl;
    print_leaf(root);
    std::cout << std::endl;

    print_struct(root, 0, "");

    print_edge(root);
    std::cout << std::endl;

    std::cout << serial_tree(root) << std::endl;
    level_print(root);
    std::cout << std::endl;
    std::map<int, int> m;
    std::cout << get_max_len(root, 0, 0, 0, m) << std::endl;

    tree_node node1;
    tree_node node2;
    tree_node node3;
    node1.data = 1; node1.left = &node2; node1.right = &node3;
    node2.data = -2; node2.left = NULL; node2.right = NULL;
    node3.data = -3; node3.left = NULL; node3.right = NULL;

    std::cout << pathSum(&node1, -1) << std::endl;
}

int main()
{
    tree_node  node1, node2, node3, node4, node5, node6, node7, node8;
    node1.data = 1; node1.left = NULL; node1.right = NULL;
    node2.data = 2; node2.left = NULL; node2.right = NULL;
    node3.data = 3; node3.left = NULL; node3.right = NULL;
    node4.data = 4; node4.left = NULL; node4.right = NULL;
    node5.data = 5; node5.left = NULL; node5.right = NULL;
    node6.data = 6; node6.left = NULL; node6.right = NULL;
    node7.data = 7; node7.left = NULL; node7.right = NULL;
    node8.data = 8; node8.left = NULL; node8.right = NULL;

    node1.left = &node2;
    node1.right = &node6;

    node2.left = NULL;
    node2.right = &node3;

    node3.left = &node4;
    node3.right = &node5;

    node6.left = NULL;
    node6.right = &node7;

    node7.left = &node8;
    node7.right = NULL;

    test(&node1);

    return 0;
}
