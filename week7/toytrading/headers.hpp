#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

/*
This is the class that will hold the information regarding a specific pair of stock relationships

*/
class StockPair
{

public:
    std::string pairId;
    std::string firstProduct;
    std::string secondProduct;
    std::int64_t maximumAllowedDifference;
    bool isExceeded{false};

    StockPair(std::string pairId, std::string firstProduct, std::string secondProduct, std::int64_t maximumAllowedDifference) : pairId(pairId), firstProduct(firstProduct), secondProduct(secondProduct), maximumAllowedDifference(maximumAllowedDifference) {}

private:
};

class Prices
{
public:
    // Function to get price of stock by stock name
    int64_t getPrice(const std::string &stockName);

    // Function to get updateNum of stock by stock name
    int64_t getUpdateNum(const std::string &stockName);

    // Function to get StockPair ptr from pairId
    StockPair *getPair(const std::string &pairId);

    // Function to get vector of pairs names involved with a specific stock name
    std::vector<std::string> *getInvolvedPairs(const std::string &stockName);

    void updateRawPrice(
        const std::string &product,
        std::int64_t newPrice,
        std::int64_t updateNumber);

    void addPair(StockPair stock);

    void addInvolvement(std::string stock, std::string pairId);

private:
    // Holds the raw prices (stock name -> (price, update number))
    std::unordered_map<std::string, std::pair<int64_t, int64_t>> priceMap;

    // Holds the pairs (pairId -> StockPair object)
    std::unordered_map<std::string, StockPair> pairMap;

    // Tracks which pair ids are involved with a specific stock name
    std::unordered_map<std::string, std::vector<std::string>> involvedPairs;
};

struct Alert
{
    std::string pairId;
    std::string firstProduct;
    std::string secondProduct;
    std::int64_t difference;

    Alert(std::string pairId, std::string firstProduct, std::string secondProduct, std::int64_t difference) : pairId(pairId), firstProduct(firstProduct), secondProduct(secondProduct), difference(difference) {}
};

class PriceMonitor
{
public:
    void registerPair(
        const std::string &pairId,
        const std::string &firstProduct,
        const std::string &secondProduct,
        std::int64_t maximumAllowedDifference);

    std::vector<Alert> updatePrice(
        const std::string &product,
        std::int64_t newPrice,
        std::int64_t updateNumber);

    PriceMonitor() = default;

private: // Add any private data members or helper functions you need.
    Prices priceObj;
};
