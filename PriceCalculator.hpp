#include "Graph.hpp"
#include <unordered_map>

class PriceCalculator {
 public:
    static void CalculateResourcePrice(Graph& graph);

    static void CalculateProcessesProfit(Graph& graph);

 private:
    struct AveragePrice {
        [[nodiscard]] double GetAveragePrice() {
            return price / static_cast<double>(number);
        }

        double price = 0;
        size_t number = 0;
    };

    static void CalculateAveragePrices(Graph& graph, std::unordered_map<Resource*, AveragePrice>& average_prices);

    static void IncreasePriceConsideringUnavailableProcesses(Graph& graph,
                                                             std::unordered_map<Resource*, AveragePrice> average_prices);
};


