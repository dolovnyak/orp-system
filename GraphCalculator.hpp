#include "Graph.hpp"
#include <unordered_map>

class GraphCalculator {
 public:
    static void Calculate(Graph& graph);

    static bool IsResourceToOptimize(Resource* resource, Graph& graph) {
        for (auto resources_to_optimize : graph.GetResourcesToOptimize()) {
            if (resources_to_optimize == resource) {
                return true;
            }
        }
        return false;
    }

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


