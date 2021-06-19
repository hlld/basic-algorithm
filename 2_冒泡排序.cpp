#include <cstdio>

void bubblesort(int arr[], int len)
{
    // 进行N-1伦冒泡排序
	for (int j = 0; j < len - 1; j++) {
        // 每伦排序从左到右逐步比较，将当前伦最大值放至最右边
        // 首轮将选出数组中最大值，余下伦比较步数依次递减
		for (int k = 0; k < len - 1 - j; k++) {
			if (arr[k] > arr[k + 1]) {
				int tmp = arr[k];
				arr[k] = arr[k + 1];
				arr[k + 1] = tmp;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int arr[] = {2, 4, 1, 9, 3, 56, 23, 534, 4, 65, 23, 6};
    int len = sizeof(arr) / sizeof(int);
    bubblesort(arr, len);
    for (int k = 0; k < len; k++) {
        printf("%d ", arr[k]);
    }
    printf("\n");
    return 0;
}
