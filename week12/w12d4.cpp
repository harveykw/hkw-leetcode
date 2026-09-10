#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using std::vector, std::string;

class Solution
{
public:
    string reverseWords(string s)
    {

        string returnString{""};

        std::istringstream iss(s);

        string word{};

        vector<string> words{};

        while (iss >> word)
        {
            words.push_back(word);
        }

        std::reverse(words.begin(), words.end());

        for (int i{0}; i < words.size(); ++i)
        {

            if (i != 0)
            {
                returnString += " ";
            }

            returnString += words.at(i);
        }

        return returnString;
    }
};

int main(int argc, char *argv[])
{

    string test1{""};
    Solution sol{};
    std::cout << sol.reverseWords(test1);
}