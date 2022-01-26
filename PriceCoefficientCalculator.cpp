#include "PriceCoefficientCalculator.hpp"

void PriceCoefficientCalculator::CalculateAverageCoefficients(Graph& graph,
                                                              std::unordered_map<Resource*, AveragePrice>& average_prices) {
}

bool is_resource_to_optimize(Resource* resource, Graph& graph) {
    for (auto resources_to_optimize : graph.GetResourcesToOptimize()) {
        if (resources_to_optimize == resource) {
            return true;
        }
    }
    return false;
}

void PriceCoefficientCalculator::Calculate(Graph& graph) {
    std::unordered_map<Resource*, AveragePrice> average_prices;

    /// calculate average coefficient
    for (auto resource_to_optimize : graph.GetResourcesToOptimize()) {
        resource_to_optimize->UpdateMaxNumber(std::numeric_limits<double>::max());
        for (auto& resource : graph.GetResources()) {

            auto resource_a_calculated_from_b = graph.CalculateAFromB(&resource, resource_to_optimize);
            if (resource_a_calculated_from_b.has_value()) {
                /// increase average resource price
                if (average_prices.count(&resource) == 0) {
                    average_prices[&resource] = AveragePrice{resource_a_calculated_from_b->min, 1};
                } else {
                    average_prices[&resource].price += resource_a_calculated_from_b->min;
                    average_prices[&resource].number += 1;
                }
            }

            if (!is_resource_to_optimize(&resource, graph)) {
                resource.UpdateMaxNumber(resource_a_calculated_from_b->max);
            }
        }
    }

    for (auto& resource: graph.GetResources()) {
        if (average_prices.count(&resource) != 0) {
            resource.SetPriceCoefficient(1 / average_prices[&resource].GetAveragePrice());
        } else {
            resource.SetPriceCoefficient(1);
        }
    }

}
