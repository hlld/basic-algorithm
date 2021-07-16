#include <cstdio>

// 题目描述：有若干个集装箱，重量分别为[W1, W2, ...]
// 对应的货物价值分别为[V1, V2, ...], 现要求设计算法
// 实现在最大载重的限制下，所能运输的最大货物价值

void dfs(int index, int weight[], int val[], int visit[], int num, 
    int wcnt, int wmax, int vcnt, int& vmax)
{
    if (!weight || !val || !visit || !num) {
        return;
    }
    // 当索引越界或此位置已访问则返回
    if (index < 0 || index >= num || visit[index] != 0) {
        return;
    }
    // 累加此位置数值，当累加值超过限值则返回
    wcnt += weight[index];
    if (wcnt <= wmax) {
        // 判断是否为累加最大值
        vcnt += val[index];
        if (vcnt > vmax) {
            vmax = vcnt;
        }
        // 标记此位置已访问
        visit[index] = 1;
        for (int k = 0; k < num; k++) {
            // 从任意位置继续递归搜索
            dfs(k, weight, val, visit, num, wcnt, wmax, vcnt, vmax);
        }
        // 回溯时取消此位置标记
        visit[index] = 0;
    }
}

int main(int argc, char* argv[])
{
    int wmax = 5, vmax = -1, num = 3;
    int weight[] = {1, 2, 3};
    int val[] = {6, 10, 12};
    int visit[] = {0, 0, 0};
    // 从任意位置开始搜索
    for (int k = 0; k < num; k++) {
        dfs(k, weight, val, visit, num, 0, wmax, 0, vmax);
    }
    printf("%d\n", vmax);
    return 0;
}
