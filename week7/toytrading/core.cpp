
#include "headers.hpp"
#include <iostream>

/*
Price functions

*/

// Returns -1 if price does not exist
int Prices::getPrice(const std::string &stockName)
{
    auto it = this->priceMap.find(stockName);
    if (it != this->priceMap.end())
        return this->priceMap[stockName];

    return -1;
}

// Returns null if pair does not exist
StockPair *Prices::getPair(const std::string &pairId)
{
    auto it = this->pairMap.find(pairId);
    if (it != this->pairMap.end())
        return this->pairMap[pairId].get(); // Recall that unique pointers use get to get raw pointer

    return nullptr;
}

std::vector<std::string> *Prices::getInvolvedPairs(const std::string &stockName)
{
    auto it = this->involvedPairs.find(stockName);
    if (it != this->involvedPairs.end())
        return &(this->involvedPairs[stockName]);
}

int main(int argc, char *argv[])
{
}