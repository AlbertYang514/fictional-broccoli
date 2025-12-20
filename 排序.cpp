#include <iostream>
#include <cstdlib>   // 用于rand()、srand()
#include <ctime>     // 用于时间统计
#include <cstring>   // 用于数组拷贝
using namespace std;

// 全局统计变量（每次排序前重置）
long long swapCount = 0;   // 交换次数
long long compareCount = 0;// 比较次数

// 交换两个整数（同时统计交换次数）
void swapInt(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    swapCount++;
}

// 1. 冒泡排序
void bubbleSort(int arr[], int n) {
    swapCount = 0;
    compareCount = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            compareCount++;  // 每次比较计数+1
            if (arr[j] > arr[j + 1]) {
                swapInt(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. 选择排序
void selectionSort(int arr[], int n) {
    swapCount = 0;
    compareCount = 0;
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        // 找最小元素下标
        for (int j = i + 1; j < n; ++j) {
            compareCount++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // 找到更小元素才交换
        if (minIdx != i) {
            swapInt(arr[i], arr[minIdx]);
        }
    }
}

// 3. 直接插入排序
void insertionSort(int arr[], int n) {
    swapCount = 0;
    compareCount = 0;
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // 向前比较并移动元素
        compareCount++;  // 首次进入while前的比较
        while (j >= 0 && arr[j] > key) {
            compareCount++;
            arr[j + 1] = arr[j];  // 元素后移视为交换
            swapCount++;
            j--;
        }
        arr[j + 1] = key;
        // 若插入位置不是原位置，计数一次交换
        if (j + 1 != i) {
            swapCount++;
        }
    }
}

// 4. 快速排序（递归实现，含分区函数）
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // 基准元素（选最后一个）
    int i = low - 1;        // 小于基准的区域边界

    for (int j = low; j <= high - 1; ++j) {
        compareCount++;
        if (arr[j] <= pivot) {
            i++;
            swapInt(arr[i], arr[j]);
        }
    }
    swapInt(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortRec(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // 分区点
        quickSortRec(arr, low, pi - 1);     // 左半区排序
        quickSortRec(arr, pi + 1, high);    // 右半区排序
    }
}

void quickSort(int arr[], int n) {
    swapCount = 0;
    compareCount = 0;
    quickSortRec(arr, 0, n - 1);
}

// 生成随机数数组（C++98兼容）
void generateRandomArray(int arr[], int n, int min = 0, int max = 1000000) {
    srand((unsigned)time(NULL));  // 初始化随机数种子
    for (int i = 0; i < n; ++i) {
        arr[i] = min + rand() % (max - min + 1);  // 生成[min, max]随机数
    }
}

// 排序性能测试函数
void testSort(void (*sortFunc)(int[], int), const char* sortName, int arr[], int n) {
    // 拷贝原数组（避免排序后影响其他算法）
    int *tempArr = new int[n];
    memcpy(tempArr, arr, n * sizeof(int));

    // 计时开始
    clock_t start = clock();
    // 执行排序
    sortFunc(tempArr, n);
    // 计时结束
    clock_t end = clock();
    double timeCost = (double)(end - start) / CLOCKS_PER_SEC;

    // 输出结果
    cout << "【" << sortName << "】" << endl;
    cout << "数据量：" << n << " 个" << endl;
    cout << "耗时：" << timeCost << " 秒" << endl;
    cout << "比较次数：" << compareCount << endl;
    cout << "交换次数：" << swapCount << endl;
    cout << "-------------------------" << endl;

    // 释放内存
    delete[] tempArr;
}

int main() {
    while (true) {  // 循环输入逻辑
        int n;
        // 输入用户指定的随机数个数
        cout << "请输入要生成的随机数个数（建议：100/1000/10000/100000，输入非正整数退出）：";
        cin >> n;

        // 输入非正整数时退出循环（程序结束）
        if (n <= 0) {
            cout << "程序退出！" << endl;
            break;
        }

        // 生成随机数数组（一次性生成，避免多次生成导致数据不一致）
        int *originalArr = new int[n];
        generateRandomArray(originalArr, n);

        // 测试四种排序算法
        testSort(bubbleSort, "冒泡排序", originalArr, n);
        testSort(selectionSort, "选择排序", originalArr, n);
        testSort(insertionSort, "直接插入排序", originalArr, n);
        testSort(quickSort, "快速排序", originalArr, n);

        // 释放原数组内存
        delete[] originalArr;

    }

    return 0;
}