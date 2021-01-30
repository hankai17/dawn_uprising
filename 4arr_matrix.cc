#include <iostream>
#include <map>


/* disordered; gt 0; arr; get sum is K's max length */
#define K 6
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
}

int main()
{
    int arr[] = { 1, 2, 3, 3 };
    test(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}
