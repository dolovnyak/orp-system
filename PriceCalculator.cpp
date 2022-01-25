#include "PriceCalculator.hpp"


void PriceCalculator::IncreasePriceConsideringUnavailableProcesses(Graph& graph,
                                                                   std::unordered_map<Resource*, AveragePrice> average_prices) {
//    for (auto& resource : graph.GetResources()) {
//        double processes_all_income = 0;
//        double processes_possible_income = 0;
//        for (auto process : resource.GetProcesses()) {
//            if (process->CanStart()) {
//                processes_possible_income += process->GetProducedResourceMultiplier(&resource);
//            }
//            processes_all_income += process->GetProducedResourceMultiplier(&resource);
//        }
//        average_prices[&resource] *= (p)
//    }
}

void PriceCalculator::CalculateAveragePrices(Graph& graph,
                                             std::unordered_map<Resource*, AveragePrice>& average_prices) {
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
}

void PriceCalculator::CalculateResourcePrice(Graph& graph) {
    std::unordered_map<Resource*, AveragePrice> average_prices;

    CalculateAveragePrices(graph, average_prices);
//    IncreasePriceConsideringUnavailableProcesses(graph);

    for (auto& resource: graph.GetResources()) {
        if (average_prices.count(&resource) != 0) {
            resource.SetCurrentPrice(average_prices[&resource].GetAveragePrice());
        } else {
            resource.SetCurrentPrice(std::numeric_limits<double>::max());
        }
    }

}

void PriceCalculator::CalculateProcessesProfit(Graph& graph) {
    for (auto& process : graph.GetProcesses()) {
        process.CalculateProfit();
    }
}
