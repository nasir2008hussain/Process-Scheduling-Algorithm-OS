#include <iostream>
#include <utility>
using namespace std;
#define Col 4

float Avg(int arr[], int size)
{
    float sumAvg = 0.0;
    for (int i = 0; i < size; i++)
    {
        sumAvg += arr[i];
    }
    float avg = sumAvg / size;
    return avg;
}

void output(int arr[][Col], float avg, int size = 5)
{
    cout << "----------------------------------------------------------\n";
    cout << "Process No"
         << "\t"
         << "Arrival Time"
         << "\t"
         << "Burst Time"
         << "\t"
         << "Wait Time" << endl;
    cout << "----------------------------------------------------------\n";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << arr[i][j] << "\t\t";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Average Waiting Times : " << avg << endl;
    cout << "----------------------------------------------------------\n";
}

template <size_t row, size_t col>
void SJF(int (&arr)[row][col])
{
    for (int k = 0; k < row; k++)
    {
        for (int j = 2; j < 3; j++)
        {
            for (int i = 0; i < (row - 1); i++)
            {
                if (arr[i][j] > arr[i + 1][j])
                {
                    swap(arr[i][j], arr[i + 1][j]);
                    swap(arr[i][0], arr[i + 1][0]);
                    swap(arr[i][1], arr[i + 1][1]);
                }
            }
        }
    }
}

int main()
{
    int q = 0;
    cout << "----------------------------------------------------------\n";
    cout << "Operating System Process Scheduler" << endl;
    cout << "Nasir Hussain \n04072013040 \nOS-Assignment No 1\n";
    cout << "----------------------------------------------------------\n";
    cout << "Time Quotation For Round Robin : ";
    cin >> q;
    int arr[5][4];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            arr[i][j] = i + 1;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 1; j < 2; j++)
        {
            cout << "Enter Process " << i + 1 << " -> Arrival Time : ";
            cin >> arr[i][j];
            cout << "Enter Process " << i + 1 << " -> Burst Time : ";
            cin >> arr[i][j + 1];
            cout << endl;
        }
    }

    int waitFCFS[5];
    waitFCFS[0] = 0;
    int k = 1;
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 2; j < 3; j++)
        {
            sum += arr[i][j];
            waitFCFS[k] = sum;
        }
        k++;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 3; j < 4; j++)
        {
            arr[i][j] = waitFCFS[i];
        }
    }
    float avgFCFS = Avg(waitFCFS, 5);
    cout << "FIRST COME FIRST SERVE FCFS \n";
    output(arr, avgFCFS, 5);

    cout << endl
         << endl;
    // -----------------------------------------------------

    int BT[5];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 2; j < 3; j++)
        {
            BT[i] = arr[i][j];
        }
    }
    int CT[5];
    int tempBT[5];

    for (int i = 0; i < 5; i++)
    {
        tempBT[i] = BT[i];
    }

    int count = 0;
    int completionTime = 0;
    while (count < 5)
    {
        for (int i = 0; i < 5; i++)
        {
            if (tempBT[i] > 0)
            {
                if (tempBT[i] >= q)
                {
                    tempBT[i] -= q;
                    completionTime += q;
                    if (tempBT[i] == 0)
                    {
                        CT[i] = completionTime;
                        ++count;
                    }
                }
                else if (tempBT[i] > 0 && tempBT[i] < q)
                {
                    int tempq = tempBT[i];
                    tempBT[i] -= tempq;
                    completionTime += tempq;
                    if (tempBT[i] == 0)
                    {
                        CT[i] = completionTime;
                        ++count;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }

    int TAT[5];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 1; j < 2; j++)
        {
            TAT[i] = CT[i] - arr[i][j];
        }
    }
    int waitRR[5];
    for (int i = 0; i < 5; i++)
    {
        waitRR[i] = TAT[i] - BT[i];
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 3; j < 4; j++)
        {
            arr[i][j] = waitRR[i];
        }
    }

    float avgRR = Avg(waitRR, 5);
    cout << "ROUND ROBIN RR\n";
    output(arr, avgRR, 5);

    cout << endl
         << endl;

    //------------------------------------------------------
    SJF(arr);
    int waitSJF[5];
    k = 1;
    sum = 0;

    waitSJF[0] = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 2; j < 3; j++)
        {
            sum += arr[i][j];
            waitSJF[k] = sum;
        }
        k++;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 3; j < 4; j++)
        {
            arr[i][j] = waitSJF[i];
        }
    }
    float avgSJF = Avg(waitSJF, 5);
    cout << "SHORTEST JOB FIRST SJF\n";
    output(arr, avgSJF, 5);

    // -------------------------------------------------------

    float BestAlogrithm[3] = {avgFCFS, avgRR, avgSJF};
    float best = avgFCFS;
    for (int j = 1; j < 3; j++)
    {
        for (int i = 1; i < 3; i++)
        {
            if (BestAlogrithm[i] < best)
            {
                best = BestAlogrithm[i];
            }
        }
    }
    cout << "----------------------------------------------------------\n";
    cout << "Result: " << endl;
    if (best == avgFCFS)
    {
        cout << "The Best Algorithm for this Process is FCFS : " << avgFCFS;
    }
    else if (best == avgSJF)
    {
        cout << "The Best Algorithm for this Process is SHORTEST JOB FIRST : " << avgSJF;
    }
    else
    {
        cout << "The Best Algorithm for this Process is ROUND ROBIN : " << avgRR;
    }
    cout << "\n----------------------------------------------------------\n";
}

