#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int longestConsecutive(vector<int> &nums)
{

    if (nums.size() == 0)
        return 0;

    sort(nums.begin(), nums.end());

    int maxLength{1};
    int currentLength{1};
    vector<int>::iterator it = nums.begin();
    while (it < nums.end())
    {

        if (it + 1 != nums.end())
        {
            if (((*it) + 1 == *(it + 1)))
            {
                ++currentLength;
                if (currentLength > maxLength)
                {
                    maxLength = currentLength;
                }
            }
            else
            {
                if ((*it) != *(it + 1))
                {
                    currentLength = 1;
                }
            }
        }

        it++;
    }
    return maxLength;
}

int main(int argc, char *argv[])
{
    vector<int> test{-10, -11, 4};

    cout << longestConsecutive(test);
}