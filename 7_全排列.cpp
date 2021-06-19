#include <cstdio>

inline void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

// 输出数组中与位置相关的全部数字排列
void full_permutation(int arr[], int index, int len)
{
    if (index >= len) {
        // 打印找到的完整排列
        for (int k = 0; k < len; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
    else {
        for (int k = index; k < len; k++) {
            if (k != index) {
                swap(arr[index], arr[k]);
            }
            full_permutation(arr, index + 1, len);
            // 回溯时还原交换的数值
            if (k != index) {
                swap(arr[index], arr[k]);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int arr[] = {1, 2, 3};
    int len = sizeof(arr) / sizeof(int);
    full_permutation(arr, 0, len);
    return 0;
}
