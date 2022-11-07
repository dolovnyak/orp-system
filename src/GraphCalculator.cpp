#include "GraphCalculator.hpp"

void GraphCalculator::Calculate(Graph& graph) {
    std::unordered_map<Resource*, AveragePrice> average_prices;

    /// calculate average coefficient
    for (auto resource_to_optimize : graph.GetResourcesToOptimize()) {
        resource_to_optimize->UpdateMaxNumber(std::numeric_limits<double>::max());
        for (auto& resource : graph.GetResources()) {

            graph.CalculateProcessesCyclesToGoal(resource_to_optimize, &resource, 0);

            auto resource_a_calculated_from_b = graph.CalculateAFromB(resource_to_optimize, &resource);
            if (resource_a_calculated_from_b.has_value()) {
                /// increase average resource price
                if (average_prices.count(&resource) == 0) {
                    average_prices[&resource] = AveragePrice{resource_a_calculated_from_b->min, 1};
                } else {
                    average_prices[&resource].price += resource_a_calculated_from_b->min;
                    average_prices[&resource].number += 1;
                }
                if (!IsResourceToOptimize(&resource, graph)) {
                    resource.UpdateMaxNumber(resource_a_calculated_from_b->max);
                }
            }

        }
    }

    for (auto& resource : graph.GetResources()) {
        if (average_prices.count(&resource) != 0) {
            resource.SetPriceCoefficient(average_prices[&resource].GetAveragePrice());
        } else {
            resource.SetPriceCoefficient(0);
        }
    }
}
