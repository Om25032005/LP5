#include<iostream>
#include<omp.h>

using namespace std;

void swapNumbers(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int n)
{
    double start = omp_get_wtime();

    for(int i = 0; i < n; i++)
    {
        #pragma omp parallel for
        for(int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[i])
            {
                swapNumbers(arr[j], arr[i]);
            }
        }
    }

    double end = omp_get_wtime();

    cout << "\nTime taken => "
         << end - start << " seconds\n";
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

    bubbleSort(arr, n);

    cout << "\nSorted Array:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}

// g++ -fopenmp BUBBLE.cpp -o bubbleSort
// .\bubble.exe