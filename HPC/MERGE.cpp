#include<iostream>
#include<omp.h>

using namespace std;

// Merge Function
void merge(int arr[], int low, int mid, int high)
{
    int temp[1000];

    int i = low;
    int j = mid + 1;
    int k = low;

    while(i <= mid && j <= high)
    {
        if(arr[i] < arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    while(i <= mid)
    {
        temp[k++] = arr[i++];
    }

    while(j <= high)
    {
        temp[k++] = arr[j++];
    }

    for(i = low; i <= high; i++)
    {
        arr[i] = temp[i];
    }
}

// Sequential Merge Sort
void SequentialMergeSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;

        SequentialMergeSort(arr, low, mid);
        SequentialMergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// Parallel Merge Sort
void ParallelMergeSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                ParallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                ParallelMergeSort(arr, mid + 1, high);
            }
        }

        merge(arr, low, mid, high);
    }
}

int main()
{
    omp_set_num_threads(4);

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr1[n], arr2[n];

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> arr1[i];
        arr2[i] = arr1[i];
    }

    // Sequential Merge Sort
    double start1 = omp_get_wtime();

    SequentialMergeSort(arr1, 0, n - 1);

    double end1 = omp_get_wtime();

    cout << "\nSequential Sorted Array:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr1[i] << " ";
    }

    cout << "\nSequential Time: "
         << end1 - start1 << " seconds\n";

    // Parallel Merge Sort
    double start2 = omp_get_wtime();

    ParallelMergeSort(arr2, 0, n - 1);

    double end2 = omp_get_wtime();

    cout << "\nParallel Sorted Array:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr2[i] << " ";
    }

    cout << "\nParallel Time: "
         << end2 - start2 << " seconds\n";

    return 0;
}

/*
Compile:
g++ -fopenmp MERGE.cpp -o merge

Run:
./merge
*/