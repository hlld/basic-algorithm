#include <cstdio>

// 给定一个数组arr，返回子数组的最大累加和
// 例如arr = [1, -2, 3, 5, -2, 6, -1]，所有子数组中
// [3, 5, -2, 6]可以累加出最大的和12，所以返回12
// 题目保证没有全为负数的数据
// 要求时间复杂度为O(n)O(n)，空间复杂度为O(1)O(1)

int maxsum_subarray(int arr[], int len) {
    if (arr == NULL || len < 1) {
        return 0;
    }
    // 动态规划递推初始化
    int sum = arr[0];
    int max = sum;
    for (int k = 1; k < len; k++) {
        // 当累加和为负时与任何数相加都不会增大累加和
        // 且题中至少存在一个正数，因此当累加和为负时
        // 可直接更新累加和为当前值，同时记录累加最大值
        if (sum > 0) {
            sum += arr[k];
        }
        else {
            sum = arr[k];
        }
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

int main(int argc, char* argv[])
{
    int arr[] = {1, -2, 3, 5, -2, 6, -1};
    int len = sizeof(arr) / sizeof(int);
    printf("%d\n", maxsum_subarray(arr, len));
    return 0;
}
