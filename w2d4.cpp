#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int> &prices)
{

    if (prices.empty())
        return 0;
    int maxProfit{0};
    int low{prices[0]};

    for (int i{1}; i < prices.size(); i++)
    {
        int currentPrice{prices[i]};
        if (currentPrice > low)
        {
            maxProfit += (currentPrice - low);
        }

        low = currentPrice;
    }
    return maxProfit;
}

bool canJump(vector<int> &nums)
{

    if (nums.empty())
        return false;

    if (nums.size() == 1)
    {
        return true;
    }

    int farthest{nums[0]};
    int tempFarthest{nums[0]};

    for (int i{0}; i < nums.size(); i++)
    {

        tempFarthest = nums[i] + i;

        if (tempFarthest > farthest)
            farthest = tempFarthest;

        if (farthest >= nums.size() - 1)
            return true;

        if (i >= farthest)
            return false;
    }

    return false;
}

int main(int argc, char *argv[])
{
    vector<int> test{2, 3, 1, 1, 4};

    cout << canJump(test);
}