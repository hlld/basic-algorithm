#include <cstdio>
#include <string>
#include <vector>

using namespace std;

// 给定一个数组arr，返回子数组的最大累加和
// 例如arr = [1, -2, 3, 5, -2, 6, -1]，所有子数组中
// [3, 5, -2, 6]可以累加出最大的和12，所以返回12
// 题目保证没有全为负数的数据

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

// 给定数组arr，arr中所有的值都为正整数且不重复
// 每个值代表一种面值的货币，每种面值的货币可以使用任意张
// 再给定一个aim，代表要找的钱数，求组成aim的最少货币数
// 如果无解，请返回-1

int minimum_money(vector<int>& arr, int aim) {
    if (arr.size() < 1 || aim < 1) {
        return -1;
    }
    // dp[0,...,aim]存储arr面值中找货币值[0,...,aim]的最小张数
    // 初始化dp[0]=0; 其余为正无穷, 表示无解
    vector<int> dp(aim + 1, INT32_MAX - 1);
    dp[0] = 0;
    // 逐个遍历现有面值, 逐步更新dp数组 (递推求解最优值)
    for (int j = 0; j < arr.size(); j++) {
        // 仅需遍历>=arr[j]的待找货币, 其余货币值无解
        for (int k = arr[j]; k <= aim; k++) {
            // 当k-arr[j]的货币有解时, 可加上1张当前面值完成换钱
            // 换钱的面值张数取现有最优解dp[k]和可行解dp[k - arr[j]] + 1的最小值
            dp[k] = dp[k] > dp[k - arr[j]] + 1 ? dp[k - arr[j]] + 1 : dp[k];
        }
    }
    if (dp[aim] == INT32_MAX - 1) {
        return -1;
    }
    return dp[aim];
}

int main(int argc, char* argv[])
{
    int arr1[] = {1, -2, 3, 5, -2, 6, -1};
    int len = sizeof(arr1) / sizeof(int);
    printf("%d\n", maxsum_subarray(arr1, len));
    vector<int> arr2 = {5, 2, 3};
    int aim = 20;
    printf("%d\n", minimum_money(arr2, aim));
    return 0;
}
