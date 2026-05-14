#include<iostream>
#include<omp.h>

using namespace std;

void merge(int arr[], int low, int mid, int high)
{
    int temp[100];

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

void mergeSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                mergeSort(arr, mid + 1, high);
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

    int arr[n];

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    double start = omp_get_wtime();

    mergeSort(arr, 0, n - 1);

    double end = omp_get_wtime();

    cout << "\nSorted Array:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\nExecution Time: "
         << end - start << " seconds\n";

    return 0;
}



// g++ -fopenmp MERGE.cpp -o merge
// .\merge.exe