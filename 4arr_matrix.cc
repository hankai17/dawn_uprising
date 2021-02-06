#include <iostream>
#include <map>

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

/*--------------------------------------------ordered matrix; is value in it */

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

/*--------------------------------------------ordered matrix; is value in it */

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

void test(int arr[], int len)
{
    //std::cout << get_max_length(arr, len) << std::endl;
    //std::cout << get_max_length1(arr, len) << std::endl;
    //spiril_print(NULL, 0, 0);
    std::cout << getLIL(arr, len) << std::endl;
}

int main()
{
    int arr[] = { 1, 9, 3, 4 };
    test(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}
