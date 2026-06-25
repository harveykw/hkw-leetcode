#include <iostream>
#include <vector>
#include <string>

using namespace std;

int jump(vector<int> &nums)
{
    if (nums.empty())
        return 0;

    if (nums.size() == 1)
    {
        return 0;
    }

    int min{1};

    int farthest{nums[0]};
    int tempFarthest{nums[0]};

    for (int i{0}; i < nums.size(); i++)
    {

        if (nums[i] + i > tempFarthest)
        {
            tempFarthest = nums[i] + i;
        }

        if (i >= farthest)
        {
            farthest = tempFarthest;
            min += 1;
        }

        if (farthest >= nums.size() - 1)
            return min;
    }

    return min;
}

int lengthOfLastWord(string s)
{
    if (s.empty())
    {
        return 0;
    }

    int length{0};
    bool hasWord{false};
    string::iterator it = s.end() - 1;
    while (it >= s.begin())
    {
        if (hasWord)
        {
            if (*it == ' ')
            {
                return length;
            }

            length++;
        }
        else
        {
            if (isalnum(*it))
            {
                hasWord = true;
                length++;
            }
        }
        it--;
    }

    return length;
}

int main(int argc, char *argv[])
{
    // vector<int> test{7, 0, 9, 6, 9, 6, 1, 7, 9, 0, 1, 2, 9, 0, 3};
    // vector<int> test{2, 3, 0, 1, 4};

    string test{"hi guys "};

    cout << lengthOfLastWord(test);
}