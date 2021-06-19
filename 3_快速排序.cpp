#include <cstdio>

inline void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

// 以x为基准，将数组中小于等于x的数移动到x左边
// 将大于x的数移动到x右边
int partition(int arr[], int p, int r) {
    int x = arr[r];
    int q = p;
    for(int k = p; k < r; k++) {
        if (arr[k] <= x) {
            // 当q等于k时，q指向小于等于x的数
            // 当q不等于k时，q指向大于x的数
            if (k != q) {
                // 交换前面大于x的数与后面小于等于x的数
                swap(arr[k], arr[q]);
            }
            q++;
        }
    }
    // 最后交换q指向的大于x的数与x
    // 实现x左边的数小于等于x，x右边的数大于x
    swap(arr[q], arr[r]);
    return q;
}

void quicksort(int arr[], int p, int r) {
    if (p < r) {
        // 以r指向的值为基准，将数组分隔为左右两段
        int q = partition(arr, p, r);
        // 分别递归处理左右两段，直至段中q等于r
        quicksort(arr, p, q - 1);
        quicksort(arr, q + 1, r);
    }
}

// 快速排序算法复杂度O(nlog(n))
int main(int argc, char* argv[])
{
    int arr[] = {5, 1, 7, 234, 3, 5, 0, 23, 4, 12, 4, 11};
    int len = sizeof(arr) / sizeof(int);
    quicksort(arr, 0, len - 1);
    for (int k = 0; k < len; k++) {
        printf("%d ", arr[k]);
    }
    printf("\n");
    return 0;
}
