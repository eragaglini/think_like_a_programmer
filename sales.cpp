#include <iostream>
#include <algorithm>

using namespace std;

double arrayAverage(int intArray[], int ARRAY_SIZE)
{
    double sum = 0;
    int new_size = 0;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (intArray[i] >= 0)
        {
            /* code */

            sum += intArray[i];
            new_size++;
        }
    }
    double average = (sum + 0.5) / new_size;
    return average;
}


double arrayMedian(int intArray[], int ARRAY_SIZE)
{

    int from = 0;
    while (intArray[from] < 0)
    {
        /* code */
        from++;
    }
    int to = ARRAY_SIZE - 1;
    while (intArray[to] < 0)
    {
        /* code */
        to--;
    }
    int NEW_ARRAY_SIZE = to - from + 1;
    int newArray[NEW_ARRAY_SIZE];
    int index = 0;
    for (size_t i = from; i <= to; i++)
    {
        /* code */
        newArray[index] = intArray[i];
        index++;
    }

    sort(newArray, newArray + NEW_ARRAY_SIZE);
    if (NEW_ARRAY_SIZE % 2 != 0)
    {
        return newArray[NEW_ARRAY_SIZE / 2];
    }
    else
    {
        return (newArray[NEW_ARRAY_SIZE / 2] + newArray[(NEW_ARRAY_SIZE / 2) - 1]) / 2.0;
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

    cout << "-----------" << endl;

    int sale2[NUM_AGENTS][NUM_MONTHS] = {
        {-1, -1, 30924, 87478, 328, 2653, 387, 3754, -1, -1, -1, -1},
        {-1, 5456, 3983, 6464, 9957, 4785, 3875, 3838, -1, -1, -1, -1},
        {-1, -1, 67, 99, 265, 376, 232, 223, 4546, 564, 4544, 3434}};

    highestAverage = arrayAverage(sale2[0], 12);
    for (int agent = 1; agent < NUM_AGENTS; agent++)
    {
        int agentAverage = arrayAverage(sale2[agent], 12);
        if (agentAverage > highestAverage)
            highestAverage = agentAverage;
    }
    cout << "Highest monthly average: " << highestAverage << "\n";

    highestMedian = arrayMedian(sale2[0], 12);
    for (size_t i = 0; i < NUM_AGENTS; i++)
    {
        /* code */

        int agentMedian = arrayMedian(sale2[i], 12);
        if (agentMedian > highestMedian)
            highestMedian = agentMedian;
    }
    cout << "Highest monthly median: " << highestMedian << "\n";

    return 0;
}
