#include <stdio.h>
#include <stdlib.h>

int normal_partition(int);
int partition_odd_only(int);
int partition_inceasing_order(int n, int min);
int partition_alternate(int, char);
int* merge(int* arr1, int* arr2, int len1, int len2);
int* mergeSort(int*, int, int);
void swap(int *arr, int idx1, int idx2);
void qsort_me(int* arr, int low, int high);

int main(void)
{
    int n = 6;
    // different method of partitioning. 

    // test merge
    // int arr1[1] = {1};
    // int arr2[1] = {2};
    // int* arr = merge(arr1, arr2, 1, 1);
    // for (int i = 0; i < 2; i++)
    // {
    //     printf("%d\n", arr[i]);
    // }
    // free(arr);

    // int arr3[6] = {1, 3, 2, 4, 65, 4};
    // int* sorted_arr = mergeSort(arr3, 0, 5);
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("%d\n", sorted_arr[i]);
    // }
    // free(sorted_arr);

    int arr[8] = {19, 7, 12, 19, 28, 31, 19, 42};
    qsort_me(arr, 0, 7);
    for (int i = 0; i < 8; i++)
    {
        printf("%d\n", arr[i]);
    }


    return 0;
}

int normal_partition(int n)
{
    int total = 0;
    // base case
    if (n == 0)
    {
        return 1;
    }

    int lead_val;
    for (lead_val = 1; lead_val <= n; lead_val++)
    {
        total += normal_partition(n - lead_val);
    }

    return total;
}

int partition_odd_only(int n)
{
    int sum = 0;
    // base cases
    if (n == 1)
    {
        return 1;
    }

    if (n == 0)
    {
        return 1;
    }

    int leading_val;
    for (leading_val = 1; leading_val <= n; leading_val+=2)
    {
        sum += partition_odd_only(n - leading_val);
    }

    return sum;
}

int partition_inceasing_order(int n, int min)
{
    int sum = 0;
    // base cases
    if (n == 0)
    {
        return 1;
    }

    if (min > n)
    {
        return 0;
    }

    int leading_val;
    for (leading_val = min; leading_val <= n; leading_val++)
    {
        sum += partition_inceasing_order(n - leading_val, leading_val + 1);
    }

    return sum;
}

int partition_alternate(int n, char isOdd)
{
    int sum = 0;
    //base case
    if (n < 0)
    {
        return 0;
    }
    if (n == 0)
    {
        return 1;
    }

    int leading_val;
    if (isOdd)
    {
        for (leading_val = 1; leading_val <= n; leading_val += 2)
        {
            sum += partition_alternate(n - leading_val, !isOdd);
        }
    } else
    {
        for (leading_val = 2; leading_val <= n; leading_val += 2)
        {
            sum += partition_alternate(n - leading_val, !isOdd);
        }
    }

    return sum;
}

//for merge sort practice
int* merge(int* arr1, int* arr2, int len1, int len2)
{
    int pos1 = 0;
    int pos2 = 0;
    int* arr = malloc((len1 + len2) * sizeof(int)); // use heap memory because stack will disappear
    int pos = 0;
    while (pos1 <= len1-1 && pos2 <= len2-1)
    {
        if (arr1[pos1] <= arr2[pos2])
        {
            arr[pos] = arr1[pos1];
            pos++;
            pos1++;
        } else
        {
            arr[pos] = arr2[pos2];
            pos++;
            pos2++;
        }
    }

    if (pos1 > len1-1)
    {
        for (int i = pos2; i < len2; i++)
        {
            arr[pos++] = arr2[i];
        }
    } else
    {
        for (int i = pos1; i < len1; i++)
        {
            arr[pos++] = arr1[i];
        }
    }

    return arr;
}

int* mergeSort(int* arr, int low, int high)
{
    int len = high - low + 1;
    if (len <= 1)
    {
        int* arr1 = malloc(sizeof(int) * len);
        arr1[0] = arr[low]; // use low
        return arr1;
    } else
    {
        int mid = low + (high - low + 1) / 2; // low + difference
        int* left_arr = mergeSort(arr, low, mid-1);
        int* right_arr = mergeSort(arr, mid, high);
        int* sorted_arr = merge(left_arr, right_arr, mid - low, high - mid + 1);
        free(left_arr);
        free(right_arr);
        return sorted_arr;
    }    
}

// for quick sort practise
void swap(int *arr, int idx1, int idx2)
{
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

void qsort_me(int* arr, int first_idx, int last_idx)
{
    if (first_idx >= last_idx)
    {
        return;
    }
    int low = first_idx + 1;
    int high = last_idx;
    int pivot = first_idx;

    while (low < high)
    {
        while (arr[low] <= arr[pivot] && low < last_idx)
        {
            low++;
        }

        while (arr[high] > arr[pivot] && high > first_idx)
        {
            high--;
        }
        if (high > low)
        {
            swap(arr, low, high);
        }
    }

    if (arr[pivot] > arr[high])
    {
        swap(arr, pivot, high);
        
    }
    qsort_me(arr, first_idx, high - 1);
    qsort_me(arr, low, last_idx);

}