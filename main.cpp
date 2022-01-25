#include <limits>
#include <cmath>
#include <unordered_map>
#include "argparse.hpp"
#include "Graph.hpp"
#include "Grammar.yy.hpp"

int yyparse(Graph* graph);

extern FILE* yyin;

namespace {

struct AveragePrice {

    [[nodiscard]] double GetAveragePrice() {
        return price / static_cast<double>(number);
    }

    double price = 0;
    size_t number = 0;
};

Graph parse_graph(FILE* file) {
    yyin = file;

    Graph graph;
    yyparse(&graph);
    fclose(file);

    return graph;
}

FILE* open_file(const std::string& file_name) {
    FILE* file = fopen(file_name.c_str(), "r");
    if (!file) {
        throw std::runtime_error("Error on opening file : " + file_name);
    }
    return file;
}

void running_processes_processing(std::list<Process>& running_processes) {
    auto running_process = running_processes.begin();

    while (running_process != running_processes.end()) {
        running_process->IncrementCycle();
        if (running_process->ShouldDie()) {
            running_process->CollectResources();
            running_processes.erase(running_process);
        }
        ++running_process;
    }
}

void calculate_resource_price(Graph& graph) {
    std::unordered_map<Resource*, AveragePrice> final_prices;

    for (auto& a: graph.GetResources()) {
        for (auto& b: graph.GetResources()) {
            double resource_a_calculated_from_b = graph.CalculateAFromB(&a, &b);
            if (!std::isnan(resource_a_calculated_from_b)) {
                /// increase average A price
                if (final_prices.count(&a) == 0) {
                    final_prices[&a] = AveragePrice{resource_a_calculated_from_b, 1};
                } else {
                    final_prices[&a].price += resource_a_calculated_from_b;
                    final_prices[&a].number += 1;
                }
            }
        }
    }

    for (auto& resource: graph.GetResources()) {
        if (final_prices.count(&resource) != 0) {
            resource.SetCurrentPrice(final_prices[&resource].GetAveragePrice());
        } else {
            /// If it's impossible to get resource from other resources we set him min price (spend him first)
            resource.SetCurrentPrice(std::numeric_limits<double>::lowest());
        }
    }
}

void run_processes_by_lower_price(const Graph& graph, std::list<Process>& running_processes) {

}

}

int main(int argc, char** argv) {
    argparse::ArgumentParser argparse("orp-system");

    argparse.add_argument("input_file")
            .required()
            .help("specify the input file.");

//    argparse.add_argument("time")
//            .default_value()
//            .help("specify the work time.");

    argparse.add_argument("-c", "--cycles")
            .default_value(std::numeric_limits<size_t>::max())
            .help("specify the cycles number.");

    try {
        argparse.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << std::endl;
        std::cout << argparse;
        exit(0);
    }

    try {
        Graph graph = parse_graph(open_file(argparse.get<std::string>("input_file")));
        std::list<Process> running_processes;
        size_t cycles_number = argparse.get<size_t>("--cycles");
        size_t current_cycle = 0;

        graph.Print();
        while (current_cycle < cycles_number) {
            running_processes_processing(running_processes);
            calculate_resource_price(graph);
            graph.Print();
            exit(0);
            run_processes_by_lower_price(graph, running_processes);
            ++current_cycle;
        }

    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
    exit(0);
}
