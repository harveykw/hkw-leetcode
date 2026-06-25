#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

class RandomizedSet
{
public:
    unordered_map<int, int> indexMap;
    vector<int> vec;
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<int> distribution;

    RandomizedSet()
    {
        gen = mt19937(rd());
    }

    bool insert(int val)
    {

        auto it = indexMap.find(val);
        if (it != indexMap.end())
            return false;

        vec.push_back(val);

        indexMap[val] = vec.size() - 1;

        return true;
    }

    bool remove(int val)
    {

        auto it = indexMap.find(val);
        if (it == indexMap.end())
            return false;

        int indexInVec{indexMap[val]};
        // Remove from vector
        vec[indexInVec] = vec.back();
        indexMap[vec[indexInVec]] = indexInVec;
        vec.pop_back();

        // Remove from maps (Not necessary if runtime constraints)
        indexMap.erase(val);
        cout << endl;

        return true;
    }

    int getRandom()
    {

        distribution = uniform_int_distribution<int>(0, vec.size() - 1);
        int random_num = distribution(gen);

        return vec[random_num];
    }
};

int main(int argc, char *argv[])
{
    RandomizedSet set{};

    set.insert(0);
    set.insert(1);
    /*



    */

    set.remove(0);
    set.insert(2);
    set.remove(1);

    for (const int i : set.vec)
    {
        cout << i;
    }

    set.getRandom();
    set.getRandom();
}