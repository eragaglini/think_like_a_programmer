#include <iostream>
#include <algorithm>

using namespace std;

double arrayAverage(int intArray[], int ARRAY_SIZE)
{
    double sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        sum += intArray[i];
    }
    double average = (sum + 0.5) / ARRAY_SIZE;
    return average;
}

double arrayMedian(int intArray[], int ARRAY_SIZE)
{
    sort(intArray, intArray + ARRAY_SIZE);
    if (ARRAY_SIZE % 2 != 0)
    {
        return intArray[ARRAY_SIZE / 2];
    }
    else
    {
        return (intArray[ARRAY_SIZE / 2] + intArray[(ARRAY_SIZE / 2) - 1]) / 2;
    }
}

int main()
{
    const int NUM_AGENTS = 3;
    const int NUM_MONTHS = 12;
    int sales[NUM_AGENTS][NUM_MONTHS] = {
        {1856, 498, 30924, 87478, 328, 2653, 387, 3754, 387587, 2873, 276, 32},
        {5865, 5456, 3983, 6464, 9957, 4785, 3875, 3838, 4959, 1122, 7766, 2534},
        {23, 55, 67, 99, 265, 376, 232, 223, 4546, 564, 4544, 3434}};

    int highestAverage = arrayAverage(sales[0], 12);
    for (int agent = 1; agent < NUM_AGENTS; agent++)
    {
        int agentAverage = arrayAverage(sales[agent], 12);
        if (agentAverage > highestAverage)
            highestAverage = agentAverage;
    }
    cout << "Highest monthly average: " << highestAverage << "\n";

    int highestMedian = arrayMedian(sales[0], 12);
    for (size_t i = 0; i < NUM_AGENTS; i++)
    {
        /* code */

        int agentMedian = arrayMedian(sales[i], 12);
        if (agentMedian > highestMedian)
            highestMedian = agentMedian;
    }
    cout << "Highest monthly median: " << highestMedian << "\n";

    return 0;
}
