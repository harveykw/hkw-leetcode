#include <vector>
#include <iostream>

using namespace std;

vector<int> productExceptSelf(vector<int> &nums)
{
    vector<int> result((int)nums.size(), 1);
    vector<int> prefix((int)nums.size(), 1);

    // Populate prefix
    for (int i = 1; i < nums.size(); ++i)
    {
        prefix[i] = prefix[i - 1] * nums[i - 1];
    }

    // Populate suffix
    vector<int> suffix((int)nums.size(), 1);

    for (int i = nums.size() - 2; i >= 0; --i)
    {
        suffix[i] = suffix[i + 1] * nums[i + 1];
    }

    // Calculate results

    for (int i{0}; i < nums.size(); i++)
    {
        result[i] = prefix[i] * suffix[i];
    }

    return result;
}

int main(int argc, char *argv[])
{
    vector<int> test{-1, 1, 0, -3, 3};
    vector<int> result = productExceptSelf(test);

    for (int i : result)
    {
        cout << i << ", ";
    }
}