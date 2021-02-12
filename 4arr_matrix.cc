#include <iostream>
#include <map>
#include <queue>

#define K 6

/*------------------------------------------------------------spiril print*/

void print_edge(int arr[][4], int lux, int luy, int rdx, int rdy)
{
    if (lux == rdx) {
        for (int i = luy; i < rdy + 1; i++) {
            std::cout << arr[lux][i] << " " << std::endl;
        }
    } else if (luy == rdy) {
        for (int i = lux; i < rdx + 1; i++) {
            std::cout << arr[luy][i] << " " << std::endl;
        }
    } else {
        int cur_x = lux;
        int cur_y = luy;

        while (cur_y != rdy) {
            std::cout << arr[lux][cur_y] << " " << std::endl;
            cur_y++;
        }

        while (cur_x != rdx) {
            std::cout << arr[cur_x][rdy] << " " << std::endl;
            cur_x++;
        }

        while (cur_y != luy) {
            std::cout << arr[rdx][cur_y] << " " << std::endl;
            cur_y--;
        }

        while (cur_x != lux) {
            std::cout << arr[cur_x][luy] << " " << std::endl;
            cur_x--;
        }
    }
    return;
}

/*------------------------------------------------------------spiril print*/

/*------------------------------------------------------------clockwise print*/

void process_edge(int arr[][4], int lux, int luy, int rdx, int rdy)
{
    int n = rdx - lux;
    for (int i = 0; i < n; i++) {
        int tmp = arr[lux][luy + i];
        arr[lux][luy + i] = arr[rdx - i][luy];
        arr[rdx - i][luy] = arr[rdx][rdy - i];
        arr[rdx][rdy - i] = arr[lux + i][rdy];
        arr[lux + i][rdy] = tmp;
    }
    return;
}

/*------------------------------------------------------------clockwise print*/

// clockwise
void spiril_print(int **arr1, int n, int m)
{
    std::cout << "------------------" << std::endl;
    int arr[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, 
            {9, 10, 11, 12}, {13, 14, 15, 16}};
    m = 4, n = 4;
    int lux = 0;
    int luy = 0;

    int rdx = m - 1;
    int rdy = n - 1;

    while (lux <= rdx && luy <= rdy) {
        //print_edge(arr, lux, luy, rdx, rdy);
        process_edge(arr, lux, luy, rdx, rdy);
        lux++;
        luy++;
        rdx--;
        rdy--;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return;
}


/*------------------------------------------------------------min K */
// see heap.c
/*------------------------------------------------------------min K*/

/*--------------------------------------------disordered; get min reorder len*/

void get_min_reorder_len(int arr[], int len)
{
    if (arr == NULL || len == 0 ) return; 

    // <--- 
    int min_target_idx = -1;
    int min = arr[len - 1];
    for (int i = len - 2; i >= 0; i--) {
        if (arr[i] > min) {
            min_target_idx = i; 
        } else {
            min = arr[i];
        }
    }
    if (min_target_idx == -1) return;

    int max = arr[0];
    int max_target_idx = -1;
    for (int i = 1; i < len - 1; i++) {
        if (arr[i] < max) {
            max_target_idx = i;
        } else {
            max = arr[i];
        }
    }
    std::cout << max_target_idx - min_target_idx + 1 << std::endl;
}

/*--------------------------------------------disordered; get min reorder len*/

/*--------------------------------------------ordered matrix; is value in it */

bool is_vale_in_ordered_matrix(int arr[][4], int val)
{
    int row = 0;
    int col = 3;
    while (row < 4 && col >= 0) {
        if (arr[row][col] > val) {
            col--;
        } else if (arr[row][col] < val) {
            row++;
        } else {
            return true;
        }
    }
    return false; 
}

/*--------------------------------------------ordered matrix; is value in it */

/*-------------------------------------------------------------------------- */
// 5 5 3 2 6 4 3   return len(5 3 2 6 4)

int getLIL(int arr[], int len)
{
    if (arr == NULL || len == 0) return 0;
    int rlen = 0;
    std::map<int, int> m;

    for (int i = 0; i < len; i++) {
        int min = 0x7fffffff;
        int max = 0x80000000;
        for (int j = i; j < len; j++) {
            if (m.find(arr[j]) != m.end()) {
                break;
            }
            m.insert(std::make_pair(arr[j], 1));
            max = std::max(max, arr[j]);
            min = std::min(min, arr[j]);
            if (max - min == j - i) {
                rlen = std::max(rlen, j - i + 1);
            }
        }
        m.clear();
    }
    return rlen;
}

/*-------------------------------------------------------------------------- */

/*--------------------------disordered; gt 0; arr; get sum is K's max length */
int get_max_length(int arr[], int len)
{
    if (arr == NULL || len == 0 || K <= 0) return 0; 
    int left_idx = 0;
    int right_idx = 0;
    int sum = arr[0];
    int l = 0;

    while (right_idx < len) {
        if (sum == K) {
            l = l > right_idx - left_idx + 1 ? l : 
                    right_idx - left_idx + 1;
            //right++;
            std::cout << "sum: " << sum << ", left " << left_idx << " ,right " << right_idx << std::endl;

            sum -= arr[left_idx++];
        } else if (sum < K) {
            right_idx++;
            if (right_idx == len) break;
            sum += arr[right_idx];
        } else if (sum > K) {
            sum -= arr[left_idx++];
        }
    }
    return l; 
}

int get_max_length1(int arr[], int len)
{
    if (arr == NULL || len == 0 || K <= 0) return 0; 
    std::map<int, int> sum_idx_map; // <sum, idx>
    int sum = 0;;
    int l = 0;

    for (int i = 0; i < len; i++) {
        sum += arr[i]; 
        auto it = sum_idx_map.find(sum);
        if (it == sum_idx_map.end()) {
            sum_idx_map.insert(std::make_pair(sum, i));
        }
        if (sum == K) {
            l = i + 1; 
        } else if (sum > K) {
            int target = sum - K;
            auto it = sum_idx_map.find(target);
            if (it != sum_idx_map.end()) {
                int target_idx = it->second;
                std::cout << "target_idx: " << target_idx << ", i: " << i << std::endl;
                l = l > i - target_idx ? l : 
                    i - target_idx;
            }
        }
    }
    return l;
}
/*--------------------------disordered; gt 0; arr; get sum is K's max length */


/*--------------------------------------------------------------------ordered*/
// -8 -4 -3 0 1 2 4 5 8 9     // fun1: K = 10 return <1 9> <2 8>

void print_uniq_pair(int arr[], int len, int k)
{
    if (arr == NULL || len == 0 || len == 1) return; 
    int l = 0;
    int r = len - 1;
    while (l < r) {
        if (arr[l] + arr[r] == k) {
            if (l == 0 || arr[l] != arr[l - 1]) {
                std::cout << arr[l] << " " << arr[r] << std::endl;
            }
            l++; r--;
        } else if (arr[l] + arr[r] < k) {
            l++;
        } else {
            r--;
        }
    }
    return;
}

/*--------------------------------------------------------------------ordered*/

/*-----------------------------------------------------------------disordered*/
// 1 2 5 3 4 --> 1 2 3 4 5
void sort_nature(int arr[], int len)
{
    if (arr == NULL || len == 0 || len == 1) return; 
    int next;
    for (int i = 0; i < len - 1; i++) {
        int tmp = arr[i];
        while (arr[i] != i + 1) {
            next = arr[tmp - 1];
            arr[tmp - 1] = tmp;
            tmp = next;
        }
    }
    return;
}

/*-----------------------------------------------------------------disordered*/

/*-----------------------------------------------------------------disordered*/
// odd_idx is odd val OR even_idx is even val

void my_swap(int arr[], int x, int y)
{
    int tmp = arr[x];
    arr[x] = arr[y];
    arr[y] = tmp;
}

void odd_even_sort(int arr[], int len)
{
    if (arr == NULL || len == 0 || len == 1) return; 
    int even_idx = 0;
    int odd_idx = 1;

    while (even_idx <= len - 1 && odd_idx <= len - 1) {
        if (arr[len - 1] & 1) {
            my_swap(arr, len - 1, odd_idx);
            odd_idx += 2;
        } else {
            my_swap(arr, len - 1, even_idx);
            even_idx += 2;
        }
    }
}

/*-----------------------------------------------------------------disordered*/

/*---------------------------------------------------------disordered max_sum*/

int max_sum(int arr[], int len)
{
    if (arr == NULL || len == 0 || len == 1) return 0;
    int max = 0x80000000;
    int cur = 0;
    for (int i = 0; i < len - 1; i++) {
        cur += arr[i];
        max = std::max(max, cur);
        cur = cur < 0 ? 0 : cur;
    }
    return max; 
}

int child_matrix_max_sum(int arr[][4], int len)
{
    if (arr == NULL || len == 0) return 0;
    int max = 0x80000000;
    int *sum_arr = (int*) malloc (sizeof(int) * 4);
    int cur;

    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            cur = 0; 
            for (int k = 0; i < len; k++) {
                sum_arr[k] += arr[j][k];
                cur += sum_arr[k];
                max = std::max(max, cur);
                cur = cur < 0 ? 0 : cur;
            }
        }
    }
    return max;
}

/*---------------------------------------------------------disordered max_sum*/

/*--------------------------------------------------------------partional min*/
// see 1.6bs
/*--------------------------------------------------------------partional min*/

/*------------------------------------------------------------------max multi*/

int max_multi(int arr[], int len)
{
    if (arr == NULL || len == 0) return 0;
    int max = arr[0]; 
    int min = arr[0]; 
    int res = arr[0]; 
    int max_end = 0;
    int min_end = 0;

    for (int i = 1; i < len; i++) {
        max_end = max * arr[i];
        min_end = min * arr[i];
        max = std::max(std::max(max_end, min_end),
              arr[i]);
        min = std::min(std::min(max_end, min_end),
              arr[i]);
        res = std::max(res, max);
    }
    return res;
}

/*------------------------------------------------------------------max multi*/

/*-----------------------------------------------------------------max matrix*/

void set_pre_right_down_matrix(int arr[4][4], int right[][4], int down[][4])
{
    int r = 4;
    int c = 4;
    if (arr[4 -1][4 - 1] == 1) {
        right[r - 1][c - 1] = 1;
        down[r - 1][c - 1] = 1;
    }
    for (int i = r - 2; i >= 0; i--) {
        if (arr[i][c - 1] == 1) {
            right[i][c - 1] = 1;
            down[i][c - 1] = down[i + 1][c - 1] + 1;
        }
    }
    for (int i = c - 2; i >= 0; i--) {
        if (arr[r - 1][i] == 1) {
            down[r - 1][i] = 1;
            right[r - 1][i] = right[r - 1][i + 1] + 1;
        }
    }
    for (int i = r - 2; i >= 0; i--) {
        for (int j = c - 2; j >= 0; j--) {
            if (arr[i][j] == 1) {
                right[i][j] = right[i][j + 1] + 1;
                down[i][j] = down[i + 1][j] + 1;
            } 
        }
    }
}

int has_boder(int size, int right[][4], int down[][4])
{
    for (int i = 0; i < 4 - size + 1; i++) {
        for (int j = 0; j > 4 - size + 1; j++) {
            if (right[i][j] >= size && down[i][j] >= size &&
                    down[i][j + size - 1] >= size &&
                    right[i + size - 1][j] >= size) {
                return 1;
            }
        }
    }
    return 0;
}

int get_max_square(int arr[4][4])
{
    int right[4][4];
    int down[4][4];
    set_pre_right_down_matrix(arr, right, down);
    for (int size = 3; size >= 1; size--) {
        if (has_boder(size, right, down) == 1)
            return size;
    }
}

/*-----------------------------------------------------------------max matrix*/

/*-------------------------------------------------multi arr not contain self*/

void multi_arr(int arr[], int len)
{
    if (arr == NULL || len == 0 || len == 1) return;
    int *multi_arr = (int*) malloc (sizeof(int) * len);
    multi_arr[0] = arr[0];

    for (int i = 1; i < len; i++) { // do not touch first arr
        multi_arr[i] = multi_arr[i - 1] * arr[i];
    }

    int tmp = 1;
    for (int i = len - 1; i > 0; i--) { // do not touch first arr
        multi_arr[i] = multi_arr[i - 1] * tmp;
        tmp *= arr[i];
    }
    multi_arr[0] = tmp;
}

/*-------------------------------------------------multi arr not contain self*/

/*----------------------------------------------------------------arr partion*/

void arr_partion(int arr[], int len)
{
    if (arr == NULL || len == 0 || len == 1) return;
    int u = 0;
    int i = 1;
    while (i < len) {
        if (arr[i++] != arr[u]) { // arr[1] != arr[0]
            my_swap(arr, ++u, i - 1); // 1 1
        }
    }

    for (int i = 0; i < len; i++) {
        std::cout << arr[i] << " ";
    }
}

/*----------------------------------------------------------------arr partion*/

/*---------------------------------------------------------------min path val*/

void walk_to(int pre, int r, int c, int arr[4][4], int map[4][4], 
        std::queue<int> &rq, std::queue<int> &cq) {
    if (r < 0 || r == 4 || c < 0 || c == 4 ||
            map[r][c] != 0 || arr[r][c] != 1) {
        return;
    }
    map[r][c] = pre + 1;
    rq.push(r);
    cq.push(c);
}

void min_path_val(int arr[4][4])
{
    if (arr == NULL) return;
    int map[4][4];
    map[0][0] = 1;
    std::queue<int> rq;
    std::queue<int> cq;
    rq.push(0);
    cq.push(0);

    int r = 0;
    int c = 0;
    while (!rq.empty()) {
        r = rq.front();
        rq.pop();
        c = cq.front();
        cq.pop();

        if (r == 3 && c == 3) {
            std::cout << map[r][c];
            return;
        }

        walk_to(map[r][c], r - 1, c, arr, map, rq, cq);
        walk_to(map[r][c], r + 1, c, arr, map, rq, cq);
        walk_to(map[r][c], r, c - 1, arr, map, rq, cq);
        walk_to(map[r][c], r, c + 1, arr, map, rq, cq);
    }
}

/*---------------------------------------------------------------min path val*/

void test(int arr[], int len)
{
    //std::cout << get_max_length(arr, len) << std::endl;
    //std::cout << get_max_length1(arr, len) << std::endl;
    //spiril_print(NULL, 0, 0);
    //std::cout << getLIL(arr, len) << std::endl;
    arr_partion(arr, len);
}

int main()
{
    //int arr[] = { 1, 9, 3, 4 };
    int arr[] = { 1, 2, 2, 2, 3, 3, 4, 5, 6, 6, 7, 7, 8, 8, 8, 9 };
    test(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}
