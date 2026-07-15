#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
#include <cctype>

using namespace std;

/*
Reverse polish notation

5 + 6 = 5 6 +
4 + 2 - 3 = 4 2 + 3 -
*/

int evalRPN(vector<string> &tokens)
{
    int current{};
    stack<int> intStack{};
    for (const string &s : tokens)
    {
        if (s == "+" || s == "-" || s == "/" || s == "*")
        {
            if (intStack.size() < 2)
            {
                throw runtime_error("Not enough operands");
                return -1;
            }

            int op1, op2;
            op1 = (intStack.top());
            intStack.pop();
            op2 = (intStack.top());
            intStack.pop();

            char oper = s.at(0);
            switch (oper)
            {
            case '+':
                intStack.push(op1 + op2);
                break;

            case '-':
                intStack.push(op2 - op1);
                break;

            case '*':
                intStack.push(op1 * op2);
                break;

            case '/':
                intStack.push(op2 / op1);
                break;
            }
        }
        else
        {
            intStack.push(stoi(s));
        }
    }
    return (intStack.top());
}

/*
Minstack

This works by packaging the current minimum value along with the elements in a stack. The elements themselves are responsible
for remembering the minimum element. This simplifies things as we dont need to calculate minimums, and instead retrieve it.

The key hint is that the problem asks for constant time. Something that should indicate that this is a retrieval of a stored
value.
*/

class MinStack
{
private:
    vector<tuple<int, int>> stackVec{};

public:
    MinStack()
    {
    }

    void push(int value)
    {
        // Initial behaviour
        int minValue;
        stackVec.empty() ? minValue = value : minValue = getMin();

        if (value < minValue)
            minValue = value;

        stackVec.push_back(make_tuple(value, minValue));
    }

    void pop()
    {
        stackVec.pop_back();
    }

    int top()
    {
        // return the first element of the tuple at the top position
        return (get<0>(stackVec.back()));
    }

    int getMin()
    {
        // return the second element of the tuple at the top position
        return (get<1>(stackVec.back()));
    }
};

int main(int argc, char *argv[])
{
    // MinStack stackTest{};
    // stackTest.push(-2);
    // stackTest.push(0);
    // stackTest.push(-3);
    // cout << stackTest.getMin() << endl;
    // stackTest.pop();
    // cout << stackTest.top() << endl;
    // cout << stackTest.getMin() << endl;

    vector<string> test{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    cout << evalRPN(test);
}