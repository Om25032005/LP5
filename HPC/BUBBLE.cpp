#include<iostream>
#include<omp.h>

using namespace std;

// Swap function
void swapNumbers(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Sequential Bubble Sort
void SequentialBubbleSort(int arr[], int n)
{
    double start = omp_get_wtime();

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swapNumbers(arr[j], arr[j + 1]);
            }
        }
    }

    double end = omp_get_wtime();

    cout << "\nSequential Bubble Sort Time: "
         << end - start << " seconds\n";
}

// Parallel Bubble Sort
void ParallelBubbleSort(int arr[], int n)
{
    double start = omp_get_wtime();

    for(int i = 0; i < n - 1; i++)
    {
        #pragma omp parallel for
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swapNumbers(arr[j], arr[j + 1]);
            }
        }
    }

    double end = omp_get_wtime();

    cout << "Parallel Bubble Sort Time: "
         << end - start << " seconds\n";
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

    // Sequential
    SequentialBubbleSort(arr1, n);

    cout << "\nSequential Sorted Array:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr1[i] << " ";
    }

    cout << endl;

    // Parallel
    ParallelBubbleSort(arr2, n);

    cout << "\nParallel Sorted Array:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr2[i] << " ";
    }

    return 0;
}

/*
Compile:
g++ -fopenmp bubble.cpp -o bubble

Run:
./bubble
*/