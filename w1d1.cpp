#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <map>

using namespace std;

vector<int> twoSum(vector<int> &nums, int target)
{

    vector<int> result{};
    unordered_map<int, int> map{};

    for (int i{0}; i < nums.size(); ++i)
    {
        int number = nums[i];
        int needed = target - number;

        // Searching for a key in a map is with find. It points to end if not found.
        if (map.find(needed) != map.end())
        {
            result.push_back(i);
            result.push_back(map[needed]);
            break;
        }

        map[number] = i;
    }

    return result;
}

/*
Longest Common Prefix.

We use a vertical scan method. No hash table needed. Very simple look forward and check method. Note that
i used to use c++ substr to check the entire prefix but that was slower. Instead, im doing it char by char.
This works because the previous chars in the prefix doesnt change and i only need to check the next char.
*/

string longestCommonPrefix(vector<string> &strs)
{

    char check{};

    // First we walk through the first word
    for (int j{0}; j <= strs[0].size(); ++j)
    {
        // We extract the letters in order. For each letter
        check = strs[0][j];

        // We check it against the other words at the same index
        for (int i{1}; i < strs.size(); ++i)
        {

            // We make sure the same index isnt out of bounds in the other words, and perform the check
            if (j >= strs[i].size() || strs[i][j] != check)
            {
                // If invalid, we return a substring. NOTE that substr operates on number of values, not index.
                // This is j values from position 0, not index j. This would be up to index j-1
                return strs[0].substr(0, j);
            }
        }
    }
    // Reaching this condition means that the entire first word is a prefix
    return strs[0];
}

/*
Remove duplicates from sorted Array.

IN PLACE


*/

int removeDuplicates(vector<int> &nums)
{

    map<int, int> map{};

    int numUniques{0};
    int indexToWrite{0};
    int currentValue;
    // Walk through array one by one
    for (int i{0}; i < nums.size(); ++i)
    {

        // Get current and next
        currentValue = nums[i];

        // if the next number is the same, map the index to be written to the value of the number. Then skip until the next number
        // The case where its the first time we are seeing the current value
        if (map.find(currentValue) == map.end())
        {
            map[currentValue] = indexToWrite;
            indexToWrite++;
            numUniques++;
        }
    }

    // Write to the array. Ordered maps keep an ascending order by default. Recall that the value is the index to be written to

    for (const auto &[key, value] : map)
    {
        nums[value] = key;
    }

    return numUniques;
}

int main(int argc, char *argv[])
{

    vector<int> test{1, 1, 2, 15};
    int target{9};

    cout << removeDuplicates(test) << endl;

    for (const int &i : test)
    {
        cout << i << endl;
    }

    return 0;
}