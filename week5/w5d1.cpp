#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

string simplifyPath(string path)
{
    vector<string> pathStack{};

    istringstream stream{path};
    string currentWord;

    // Split using / as a delimitter
    while (getline(stream, currentWord, '/'))
    {

        if (currentWord == "." || currentWord.empty())
            continue;
        if (currentWord == "..")
        {
            if (!pathStack.empty())
                pathStack.pop_back();

            continue;
        }
        pathStack.push_back(currentWord);
    }

    if (pathStack.empty())
        return "/";

    string returnString{""};
    for (const string s : pathStack)
    {
        returnString += "/";
        returnString += s;
    }

    return returnString;
}

int main(int argc, char *argv[])
{
    string test{"///"};
    cout << simplifyPath(test);
}