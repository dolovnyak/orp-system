#include "Graph.hpp"
#include <unordered_map>

class PriceCoefficientCalculator {
 public:
    static void Calculate(Graph& graph);

 private:
    struct AveragePrice {
        [[nodiscard]] double GetAveragePrice() {
            return price / static_cast<double>(number);
        }

        double price = 0;
        size_t number = 0;
    };

    static void CalculateAverageCoefficients(Graph& graph, std::unordered_map<Resource*, AveragePrice>& average_prices);
};


