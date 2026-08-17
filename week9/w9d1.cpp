#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <queue>

using std::vector, std::queue, std::pair, std::set;

class Solution
{
public:
    bool isOnBoundary(pair<int, int> coord, int m, int n)
    {
        if (coord.first <= 0 || coord.first >= m - 1)
            return true; // Row
        if (coord.second <= 0 || coord.second >= n - 1)
            return true; // Column

        return false;
    }

    void exploreAndFlip(vector<vector<char>> &board, vector<vector<bool>> &visited, int m, int n, int mMax, int nMax)
    {
        // BFS
        queue<pair<int, int>> BFSQueue{};
        vector<pair<int, int>> currentIslandCollection{}; // Collection to flip
        bool shouldFlip{true};

        BFSQueue.push({m, n});
        if (isOnBoundary({m, n}, mMax, nMax))
            shouldFlip = false;

        currentIslandCollection.push_back({m, n});

        // Directional Arrays
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!BFSQueue.empty())
        {

            auto [currentM, currentN] = BFSQueue.front();
            BFSQueue.pop();

            // Add cardinal nodes
            for (int i = 0; i < 4; i++)
            {
                int nr = currentM + dr[i];
                int nc = currentN + dc[i];

                if (nr >= 0 && nr < mMax && nc >= 0 && nc < nMax)
                {
                    if (visited[nr][nc])
                        continue;
                    visited[nr][nc] = true;

                    if (board.at(nr).at(nc) == 'X')
                        continue;
                    BFSQueue.push({nr, nc});

                    if (isOnBoundary({nr, nc}, mMax, nMax))
                        shouldFlip = false;

                    if (shouldFlip)
                        currentIslandCollection.push_back({nr, nc});
                }
            }
        }
        if (shouldFlip)
        {
            for (auto currentPair : currentIslandCollection)
            {
                board.at(currentPair.first).at(currentPair.second) = 'X';
            }
        }
    }

    void solve(vector<vector<char>> &board)
    {
        if (board.empty())
            return;

        size_t mMax{board.size()};
        size_t nMax{board.front().size()};

        vector<vector<bool>> visited(mMax, vector<bool>(nMax, false));

        // Walk through the board
        for (int m{0}; m < mMax; ++m)
        {

            for (int n{0}; n < nMax; ++n)
            {

                // Skip if coord visited before
                if (visited[m][n])
                    continue;

                visited[m][n] = true;

                // Skip X-es
                if (board.at(m).at(n) == 'X')
                    continue;

                exploreAndFlip(board, visited, m, n, mMax, nMax);
            }
        }
    }
};

int main(int argc, char *argv[])
{
    Solution sol{};

    vector<vector<char>> test1{
        {'X', 'O', 'X', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'X', 'X', 'O'},
        {'O', 'X', 'O', 'X'}};

    vector<vector<char>> test2{
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}};

    sol.solve(test1);

    for (auto &row : test1)
    {
        for (auto &column : row)
        {
            std::cout << column << ", ";
        }
        std::cout << "\n";
    }
}