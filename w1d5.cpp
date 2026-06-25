#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isPalindrome(string s)
{
    // Remove all non-alpha numerics

    /*
        Remove_if takes an iterator range, then a lambda function for determining what to remove.

        In this case, we are returning everything that is not alphanumeric. IE we are removing
        anything that is not alphanumeric.

        The reason we need erase as well is because removeif does not modify container length. It just
        reorders the container and provides a pointer to the end. Therefore, we remove the section from the
        pointer returned to the end of the original string.
    */

    s.erase(remove_if(s.begin(), s.end(), [](char c)
                      { return !isalnum(c); }),
            s.end());

    if (s.empty())
    {
        return true;
    }

    // Now set all characters to lower
    transform(s.begin(), s.end(), s.begin(), [](char c)
              { return tolower(c); });

    // Set up two pointers and iterate at the same time
    string::iterator it1{s.begin()};
    // Keep in mind that .end() returns an iterator that points to one position after the last element
    string::iterator it2{s.end() - 1};

    while (it1 < it2)
    {

        if (*it1 != *it2)
        {
            cout << *it1 << ", " << *it2 << endl;
            return false;
        }
        it1++;
        it2--;
    }
    return true;
}
// Two sum sorted array

vector<int> twoSum(vector<int> &numbers, int target)
{
    vector<int>::iterator it1{numbers.begin()};
    vector<int>::iterator it2{numbers.end() - 1};

    vector<int> result{};

    while (it1 < it2)
    {
        int check{*it1 + *it2};
        // cout << "Check: " << check << endl;
        if (check < target)
        {
            it1++;
        }
        else if (check > target)
        {
            it2--;
        }
        else
        {
            // Found target
            result.push_back((int)distance(numbers.begin(), it1) + 1);
            result.push_back((int)distance(numbers.begin(), it2) + 1);
            break;
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    vector<int> test{0, 1, 2, 3, 6, 1000};
    vector<int> result{twoSum(test, 5)};

    cout << result[0] << ", " << result[1];
}