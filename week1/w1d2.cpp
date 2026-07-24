#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int romanToInt(string s)
{
    // This belongs as a member variable

    unordered_map<char, int> romanTable{
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}};

    // Belongs in function

    int counter{0};
    char prevLetter{};

    for (int i{0}; i < s.size(); ++i)
    {
        char letter = s[i];

        if ((s.size() > 1) && ((prevLetter == 'I' && (letter == 'V' || letter == 'X')) ||
                               (prevLetter == 'X' && (letter == 'L' || letter == 'C')) ||
                               (prevLetter == 'C' && (letter == 'D' || letter == 'M'))))
        {
            counter -= 2 * romanTable[prevLetter];
        }

        counter += romanTable[letter];

        prevLetter = letter;
    }

    return counter;
}

string intToRoman(int num)
{

    unordered_map<int, char> romanTable{
        {1, 'I'},
        {5, 'V'},
        {10, 'X'},
        {50, 'L'},
        {100, 'C'},
        {500, 'D'},
        {1000, 'M'}};

    vector<int> termOrder{1000, 500, 100, 50, 10, 5, 1};

    string returnString{""};
    int remainingNum{num};

    for (int j{0}; j < termOrder.size(); ++j)
    {

        int term = termOrder[j];

        int div = remainingNum / term;
        if (div < 1)
        {
            continue;
        }

        // First digit and Power
        int n = abs(remainingNum); // Ensure the number is positive
        int power = 1;
        while (n >= 10)
        {
            n /= 10;
            power *= 10;
        }

        // Subtractive form
        if (div >= 4 || (n == 9 || n == 4))
        {
            // OOB check
            if (j - 1 < 0)
                break;

            // Add lowest power of ten to the string
            returnString += romanTable[power];
            // Add the previous term to the string
            returnString += romanTable[termOrder[j - 1]];

            // Adjust the remaining balance
            remainingNum -= termOrder[j - 1];
            remainingNum += power;
        }
        else
        {
            for (int i{0}; i < div; ++i)
            {
                returnString += romanTable[term];
            }
            remainingNum -= div * term;
        }
    }
    return returnString;
}

int main(int argc, char *argv[])
{
    string s{"CIV"};
    int i{1994};
    cout << intToRoman(i) << endl;
}