#include <limits>
#include <cmath>
#include <unordered_map>
#include <queue>
#include "argparse.hpp"
#include "Graph.hpp"
#include "Grammar.yy.hpp"
#include "PriceCalculator.hpp"

int yyparse(Graph* graph);

extern FILE* yyin;

namespace {

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

    int test = 0;
    while (running_process != running_processes.end()) {
        ++test;
        running_process->IncrementCycle();
        if (running_process->ShouldDie()) {
            running_process->CollectResources();
            running_process = running_processes.erase(running_process);
            continue;
        }
        ++running_process;
    }
}


void run_optimize_processes_by_profit(Graph& graph, std::list<Process>& running_processes) {
    std::vector<Process*> combined_processes;

    for (auto& resource_to_optimize: graph.GetResourcesToOptimize()) {
        combined_processes.insert(combined_processes.end(), resource_to_optimize->GetProcesses().begin(),
                                  resource_to_optimize->GetProcesses().end());
    }
    std::sort(combined_processes.begin(), combined_processes.end(), Process::ProfitComparator);

    for (auto process: combined_processes) {
        process->RecursiveRun(running_processes);
    }
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
            .help("specify the cycles number.")
            .action([](const std::string &value) { return static_cast<size_t>(std::stol(value)); });

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

        while (current_cycle < cycles_number) {

            /// increment all processes, stop and collect resources if needed cycles done
            running_processes_processing(running_processes);

            PriceCalculator::CalculateResourcePrice(graph);
            PriceCalculator::CalculateProcessesProfit(graph);

            /// sort processes by profit for each resource
            for (auto& resource: graph.GetResources()) {
                resource.SortProcessesByProfit();
            }

            run_optimize_processes_by_profit(graph, running_processes);

            if (running_processes.empty()) {
                break;
            }

            ++current_cycle;
        }
        graph.Print();
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
    exit(0);
}
