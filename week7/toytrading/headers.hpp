#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

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

    StockPair(std::string pairId, std::string firstProduct, std::string secondProduct, std::int64_t maximumAllowedDifference) : pairId(pairId), firstProduct(firstProduct), secondProduct(secondProduct), maximumAllowedDifference(maximumAllowedDifference) {}

private:
};

class Prices
{
public:
    // Function to get price of stock by stock name
    int getPrice(const std::string &stockName);

    // Function to get updateNum of stock by stock name
    int getUpdateNum(const std::string &stockName);

    // Function to get StockPair ptr from pairId
    StockPair *getPair(const std::string &pairId);

    // Function to get vector of pairs names involved with a specific stock name
    std::vector<std::string> *getInvolvedPairs(const std::string &stockName);

    void updateRawPrice(
        const std::string &product,
        std::int64_t newPrice,
        std::int64_t updateNumber);

private:
    // Holds the raw prices (stock name -> price)
    std::unordered_map<std::string, std::pair<int, int>> priceMap;

    // Holds the pairs (pairId -> StockPair obj ptr)
    std::unordered_map<std::string, std::unique_ptr<StockPair>> pairMap;

    // Tracks which pairs are involved with a specific pairId
    std::unordered_map<std::string, std::vector<std::string>> involvedPairs;
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

    // Constructor
    PriceMonitor(std::unique_ptr<Prices> prices) : priceObj(std::move(prices)) {}

private: // Add any private data members or helper functions you need.
    std::unique_ptr<Prices> priceObj;
};

struct Alert
{
    std::string pairId;
    std::string firstProduct;
    std::string secondProduct;
    std::int64_t difference;

    Alert(std::string pairId, std::string firstProduct, std::string secondProduct, std::int64_t difference) : pairId(pairId), firstProduct(firstProduct), secondProduct(secondProduct), difference(difference) {}
};
