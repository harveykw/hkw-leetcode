#include <iostream>
#include <vector>

using std::vector;

class Solution {
 public:
  int climbStairs(int n) {
    // We start by building a prefix table of the number of ways

    vector<int> prefix{0, 1};  // Number of steps is 1 or 2

    if (n == 0) return -1;  // Handle error

    while (prefix.size() - 1 <= n) {
      prefix.push_back(prefix.at(prefix.size() - 2) +
                       prefix.at(prefix.size() - 1));
    }

    return prefix.back();
  }
};

int main(int argc, char* argv[]) {
  Solution sol{};

  std::cout << sol.climbStairs(3) << "\n"
            << sol.climbStairs(5) << "\n"
            << sol.climbStairs(0) << std::endl;
}