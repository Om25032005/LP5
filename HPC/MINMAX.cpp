#include<iostream>
#include<omp.h>

using namespace std;

int main()
{
    omp_set_num_threads(4);

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    double arr[n];

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    double min_val = arr[0];
    double max_val = arr[0];
    double sum = 0.0;
    double avg = 0.0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(min:min_val)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }

    #pragma omp parallel for reduction(max:max_val)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    avg = sum / n;

    double end = omp_get_wtime();

    cout << "\nMinimum Value = " << min_val;
    cout << "\nMaximum Value = " << max_val;
    cout << "\nSum = " << sum;
    cout << "\nAverage = " << avg;

    cout << "\nExecution Time = "
         << end - start << " seconds\n";

    return 0;
}


// g++ -fopenmp MINMAX.cpp -o mimnmax
// .\minmax.exe