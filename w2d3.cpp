#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void rotate(vector<int> &nums, int k)
{
    int size = nums.size();

    if (size == 0)
    {
        return;
    }

    k %= size;

    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

// If i sold today, what is the best time for when i bought it?
int maxProfit(vector<int> &prices)
{
    if (prices.empty())
    {
        return 0;
    }

    int cheapest{prices[0]};
    int maxProfit{0};

    for (const int price : prices)
    {
        int profit = price - cheapest;
        if (profit > maxProfit)
            maxProfit = profit;
        if (price < cheapest)
            cheapest = price;
    }

    return maxProfit;
}

int main(int argc, char *argv[])
{
    vector<int> test{7, 1, 5, 3, 6, 4};
    cout << maxProfit(test);
}