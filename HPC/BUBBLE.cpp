#include<iostream>
#include<omp.h>

using namespace std;

void swapNumbers(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(int arr[], int n)
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

    BubbleSort(arr, n);

    cout << "\nSorted Array:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}
// g++ -fopenmp BUBBLE.cpp -o bubble
// .\bubble.exe