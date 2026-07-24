#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int majorityElement(vector<int> &nums)
{
    unordered_map<int, int> map;
    int mostFrequent;
    int frequency;
    bool updated{false};

    for (const int number : nums)
    {

        if (map.find(number) != map.end())
        {
            map[number]++;
        }
        else
        {
            map[number] = 1;
        }

        if (!updated)
        {
            mostFrequent = number;
            frequency = 1;
            updated = true;
        }
        else
        {
            if (map[number] > frequency)
            {
                mostFrequent = number;
                frequency = map[number];
            }
        }
    }

    return mostFrequent;
}

int removeDuplicates(vector<int> &nums)
{
    if (nums.empty())
        return 0;
    vector<int>::iterator readIT = nums.begin();
    vector<int>::iterator writeIT = nums.begin();

    int size{1};
    int prev = *readIT;
    readIT++;
    writeIT++;
    int currentCount{1};
    while (readIT < nums.end())
    {

        int curr = *readIT;
        if (curr == prev)
        {
            currentCount++;
        }
        else
        {
            currentCount = 1;
        }

        if (currentCount <= 2)
        {

            *writeIT = *readIT;
            writeIT++;

            size++;
        }

        prev = *readIT;
        readIT++;
    }
    return size;
}

int main(int argc, char *argv[])
{
    vector<int> test{0, 0, 1, 1, 1, 1, 2, 3, 3};

    int k = removeDuplicates(test);

    cout << k << endl;

    for (const int i : test)
    {
        cout << i << ", ";
    }
}