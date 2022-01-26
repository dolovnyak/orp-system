#include "PriceCoefficientCalculator.hpp"

void PriceCoefficientCalculator::CalculateAverageCoefficients(Graph& graph,
                                                              std::unordered_map<Resource*, AveragePrice>& average_prices) {
}

void PriceCoefficientCalculator::Calculate(Graph& graph) {
    std::unordered_map<Resource*, AveragePrice> average_prices;

    /// calculate average coefficient
    for (auto& a: graph.GetResources()) {
        for (auto& b: graph.GetResources()) {
            double resource_a_calculated_from_b = graph.CalculateAFromB(&a, &b);
            if (!std::isnan(resource_a_calculated_from_b)) {
                /// increase average A price
                if (average_prices.count(&a) == 0) {
                    average_prices[&a] = AveragePrice{resource_a_calculated_from_b, 1};
                } else {
                    average_prices[&a].price += resource_a_calculated_from_b;
                    average_prices[&a].number += 1;
                }
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
