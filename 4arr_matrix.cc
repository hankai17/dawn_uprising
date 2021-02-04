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
        print_edge(arr, lux, luy, rdx, rdy);
        lux++;
        luy++;
        rdx--;
        rdy--;
    }
    return;
}

/*------------------------------------------------------------spiril print*/

/* disordered; gt 0; arr; get sum is K's max length */
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

/* disordered; arr; get sum is K's max length */
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

void test(int arr[], int len)
{
    std::cout << get_max_length(arr, len) << std::endl;
    std::cout << get_max_length1(arr, len) << std::endl;
    spiril_print(NULL, 0, 0);
}

int main()
{
    int arr[] = { 1, 2, 3, 3 };
    test(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}
