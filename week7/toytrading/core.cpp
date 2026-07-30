
#include "headers.hpp"
#include <iostream>
#include <cmath>

/*
Price functions

*/

// Returns -1 if price does not exist
int Prices::getPrice(const std::string &stockName)
{
    auto it = this->priceMap.find(stockName);
    if (it != this->priceMap.end())
        return this->priceMap[stockName].first;

    return -1;
}

// Returns -1 if updateNum does not exist
int Prices::getPrice(const std::string &stockName)
{
    auto it = this->priceMap.find(stockName);
    if (it != this->priceMap.end())
        return this->priceMap[stockName].second;

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

    return nullptr;
}

// Note, this overwrites and has default behavior
void Prices::updateRawPrice(
    const std::string &product,
    std::int64_t newPrice,
    std::int64_t updateNumber)
{
    this->priceMap[product] = {newPrice, updateNumber};
}

/*
Price monitor functions

*/

std::vector<Alert> PriceMonitor::updatePrice(
    const std::string &product,
    std::int64_t newPrice,
    std::int64_t updateNumber)
{
    std::vector<Alert> alerts{};

    Prices *priceObj = this->priceObj.get();
    int curUpdate{priceObj->getUpdateNum(product)};

    // Consider case where not init or update number supercedes current
    if (curUpdate < updateNumber)
        priceObj->updateRawPrice(product, newPrice, updateNumber);

    // Now scan through paired relationships and send an alert if needed
    std::vector<std::string> *involvedPairs = priceObj->getInvolvedPairs(product);
    if (involvedPairs == nullptr)
        return {}; // No paired relationships involving this specific stock

    for (std::string pairId : *involvedPairs) // Looping though all the pairId that need tolerance checking
    {
        StockPair *stock = priceObj->getPair(pairId);
        int price1{priceObj->getPrice(stock->firstProduct)};
        int price2{priceObj->getPrice(stock->secondProduct)};

        if (abs(price1 - price2) > stock->maximumAllowedDifference)
        { // Distance exceeds limit - Send alert! (by adding to alerts vector)
        }
    }

    return alerts;
}

void PriceMonitor::registerPair(
    const std::string &pairId,
    const std::string &firstProduct,
    const std::string &secondProduct,
    std::int64_t maximumAllowedDifference)
{
}

int main(int argc, char *argv[])
{
}