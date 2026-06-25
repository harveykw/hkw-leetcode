#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{

    if (nums2.empty() || nums1.empty())
    {
        return;
    }

    vector<int> temp;
    // temp.reserve(n + m);

    int nIndex{0};
    int mIndex{0};

    for (mIndex; mIndex < m;)
    {

        if (nIndex >= n)
        {
            break;
        }

        int currentN1{nums1[mIndex]};
        int currentN2{nums2[nIndex]};

        // cout << currentN1 << " , " << currentN2 << "/ " << mIndex << endl;

        if (currentN1 < currentN2)
        {
            temp.push_back(currentN1);
            mIndex++;
        }
        else
        {

            temp.push_back(currentN2);
            nIndex += 1;
        }
    }

    while (nIndex < n)
    {
        temp.push_back(nums2[nIndex]);
        nIndex += 1;
    }

    while (mIndex < m)
    {
        temp.push_back(nums1[mIndex]);
        mIndex += 1;
    }

    nums1 = temp;
}

int main(int argc, char *argv[])
{
    vector<int> nums1{2, 0};
    vector<int> nums2{1};
    int m{1};
    int n{1};

    merge(nums1, m, nums2, n);

    for (const int i : nums1)
    {
        cout << i << " ,";
    }
}