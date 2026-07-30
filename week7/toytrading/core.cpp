
#include "headers.hpp"
#include <cmath>
#include <stdexcept>

/*
Price functions

*/

// Returns -1 if price does not exist
int64_t Prices::getPrice(const std::string &stockName)
{
    auto it = this->priceMap.find(stockName);
    if (it != this->priceMap.end())
        return this->priceMap[stockName].first;

    return -1;
}

// Returns -1 if updateNum does not exist
int64_t Prices::getUpdateNum(const std::string &stockName)
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
        return &it->second;

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

// Unique pair ID is guaranteed
void Prices::addPair(StockPair stock)
{
    const std::string pairId = stock.pairId;
    this->pairMap.emplace(pairId, std::move(stock));
}

void Prices::addInvolvement(std::string stock, std::string pairId)
{
    this->involvedPairs[stock].push_back(pairId);
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

    int64_t curUpdate{priceObj.getUpdateNum(product)};

    // Consider case where updateNumber is older than the current. Also cover the case where update number is equal, but should not happen
    if (curUpdate >= updateNumber)
        return alerts;

    priceObj.updateRawPrice(product, newPrice, updateNumber);

    // Now scan through paired relationships and send an alert if needed
    std::vector<std::string> *involvedPairs = priceObj.getInvolvedPairs(product);
    if (involvedPairs == nullptr)
        return {}; // No paired relationships involving this specific stock

    for (std::string pairId : *involvedPairs) // Looping though all the pairId that need tolerance checking
    {
        StockPair *stock = priceObj.getPair(pairId);
        int64_t price1{priceObj.getPrice(stock->firstProduct)};
        int64_t price2{priceObj.getPrice(stock->secondProduct)};

        if (price1 == -1 || price2 == -1)
            continue; // Covers case where prices are in a registered pair before prices are available

        std::int64_t absoluteDiff{std::abs(price1 - price2)};
        if (absoluteDiff > stock->maximumAllowedDifference)
        { // Distance exceeds limit - Send alert! (by adding to alerts vector)

            if (!stock->isExceeded) // Flag has not been raised yet
            {
                // Add alert here
                alerts.push_back(Alert{stock->pairId, stock->firstProduct, stock->secondProduct, absoluteDiff});
            }

            // Set exceeded to true
            stock->isExceeded = true;
        }
        else
        {
            stock->isExceeded = false;
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

    if (priceObj.getPair(pairId) != nullptr)
    {
        throw std::runtime_error("Attempted registration on duplicate pairId");
    }
    StockPair stock{pairId, firstProduct, secondProduct, maximumAllowedDifference};

    int64_t price1{priceObj.getPrice(stock.firstProduct)};
    int64_t price2{priceObj.getPrice(stock.secondProduct)};

    // Exceed flag ensures that both prices are available before doing exceed calculation
    if (!(price1 == -1 || price2 == -1))
    {
        if (std::abs(price1 - price2) > maximumAllowedDifference)
            stock.isExceeded = true;
    }

    // Check initially to see if the price has exceeded maxAllowedDifference

    priceObj.addInvolvement(firstProduct, pairId);
    priceObj.addInvolvement(secondProduct, pairId);
    priceObj.addPair(stock);
}
